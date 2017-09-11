/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

//#include "unistd.h"
//#include "time.h"
#include "Sampler.h"
#include "pruio.h"
#include "pruio_pins.h"
#include "stdio.h"
#include <string.h>
#include <math.h>

using namespace std;


static uint32 io_head=0, io_tail=0;

Sampler::Sampler() 
    : io( pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0) ) //! create new driver
    , _nrSamples(0)
    , _ok(false)
    , io_tmr(5000)     //!< The sampling rate in ns (5000 ns -> 200 kHz).
    , io_nrSteps(2)    //!< The number of active ADC steps 
                       // (must match setStep calls and io_mask).
    , io_mask(3 << 9)  //!< The active steps bitmaks (9 and 10).
    , io_bufSize((io->ESize >> 1) / io_nrSteps) //!< Max number of samples,
                                                     //   use all ERam
    , maxInd(io_bufSize * io_nrSteps) //!< The maximum index in the ring buffer.
{
    if (io->Errr){
        printf("constructor failed (%s)\n", io->Errr); return;}

    if (pruio_adc_setStep(io,  9, 0, 0, 0, 0)){ //        step 9, AIN-0 -> voltage
        printf("ADC step 9 init failed: (%s)\n", io->Errr); return;}

    if (pruio_adc_setStep(io, 10, 1, 0, 0, 1)){ //        step 10, AIN-1 -> current
        printf("ADC step 10 init failed: (%s)\n", io->Errr); return;}

    if (pruio_config(io, io_bufSize, io_mask, io_tmr, 4)){ //         configure driver
        printf("config failed (%s)\n", io->Errr); return;}

    if (pruio_rb_start(io)){ //                           start ADC
        printf("rb_start failed (%s)\n", io->Errr); return;}

    strcpy( _errMsg, "");

    io_head=0;
    io_tail=0;

    _ok = true;
}

Sampler::~Sampler() 
{
    cleanUp();
}


void Sampler::cleanUp()
{
    if( io ) pruio_destroy(io);
    io = 0;
}

//#define __DEBUG__

#ifdef __DEBUG__
#define DEBUGBUFSIZE 10000
    static uint32 _totNrSamp[DEBUGBUFSIZE];
    static uint32 _nsamples[DEBUGBUFSIZE];
    static uint32 _ioheads[DEBUGBUFSIZE];
    static uint32 _iotails[DEBUGBUFSIZE];
    static uint32 _iotails2[DEBUGBUFSIZE];
    static uint32 _iotails3[DEBUGBUFSIZE];
    static uint32 _sidx=0;

void printDebugInfo()
{
    printf("---Sampler debug begin ----\n");
    printf("TotNrSamp, nsamples, ioheads, iotails, iotails2, iotails3\n");
    for( uint32 idx=0; idx<_sidx; idx++)
        printf("%d, %d, %d, %d, %d, %d\n"
            ,_totNrSamp[idx], _nsamples[idx], _ioheads[idx], _iotails[idx]
            , _iotails2[idx], _iotails3[idx]);

    printf("---Sampler debug end   ----\n");
}    
#endif  // __DEBUG__


void Sampler::reset()
{
    _nrSamples = 0;
    io_tail=io_head;

#ifdef __DEBUG__
    _sidx=0;
#endif
}

/* Typical zero current calibration result:

    Mean                            : 32529.3
    Population Variance             :   941.1
    Sample variance                 :   941.1
    Population Standard Deviation   :    30.6
    Sample Standard Deviation       :    30.6
*/

/* Typical 1.0A current calibration result:

    Mean                            : 2641.0
    Population Variance             :  7900.4
    Sample variance                 :  7900.4
    Population Standard Deviation   :    88.9
    Sample Standard Deviation       :    88.9

*/

/* Typical 0.0A current after calibration:
 
    Mean                            :   -0.00088
    Population Variance             :     0.0001
    Sample variance                 :     0.0001
    Population Standard Deviation   :     0.0119
    Sample Standard Deviation       :     0.0119
*/

#define current_mean     32529.3f
#define current_gain     1.0f/2641.0f
float Sampler::getCurrent( uint32 idx )
{
    float ret = current_gain*(((float)curr(idx))-current_mean);
//       if( fabs(ret) < 0.05 ) return 0.0f;
    return ret;
}

#define nrAdcSteps (io->Adc->ChAz)

int Sampler::getSamples()
{

    uint32 lastsample = io->DRam[0];
//    io_head = lastsample & 0xfffe; // only even indexes from AIN0 == voltage

    if(((lastsample >> 1) << 1) == lastsample)
        //even
        io_head = lastsample;
    else
        //odd
        io_head = lastsample>=1 ? lastsample-1 : 0;


//    uint32 nrSamples = ( io_head>io_tail ? (io_head-io_tail)/2
//                                         : (maxInd-io_tail+io_head)/2 );

    uint32 nrsamp2get = ( io_head>io_tail ? (io_head-io_tail)/2
                                         : (maxInd-io_tail+io_head)/2 );

#ifdef __DEBUG__
    if( _sidx<DEBUGBUFSIZE)
    {
        _ioheads[_sidx] = io_head;
        _iotails[_sidx] = io_tail;
        _iotails2[_sidx] = 1234;
        _iotails3[_sidx] = 5678;
        _nsamples[_sidx]=nrsamp2get;
        _totNrSamp[_sidx++]=_nrSamples;
    }
#endif

    if( _nrSamples + nrsamp2get > SamplerBufSize )
    {
        //strcpy( _errMsg, "Sampler buffer overflow.");
        sprintf( _errMsg,
                 "Buffer will overflow when adding %d samples. \n Buffer Size now: %d.",
                 nrsamp2get,_nrSamples
               );

        _ok = false;
        return 0;
    }
/*
    if( io_head == lastsample ) // last sample misses current measurement
    {
       if( nrsamp2get <= 1
           || io_head < nrAdcSteps // Don't bother handling overflow here. 
         ) return 0;

       //io_head -= nrAdcSteps; 
       nrsamp2get--;
    }
*/


// just leave out the last few samples. Will get those next time.
    if (nrsamp2get <= 10) return 0;
    nrsamp2get-=8;


#ifdef __DEBUG__
    if( _sidx<DEBUGBUFSIZE) { _iotails2[_sidx-1] = io_tail; }
#endif
    for(uint32 cnt = 0; cnt < nrsamp2get; cnt++)
    {
#ifdef __DEBUG__
        if( _volt[_nrSamples] != 234 || _curr[_nrSamples] != 234 )
            { sprintf( _errMsg, "Error: overwriting sample!"); _ok=false; }

        uint16 vlt = io->Adc->Value[io_tail];
        uint16 cur = io->Adc->Value[io_tail+1];

        _volt[_nrSamples] = vlt;
        _curr[_nrSamples] = cur;

        if( _volt[_nrSamples] == 0 && _curr[_nrSamples] == 0 )
            { sprintf( _errMsg, "Error: curr&volt both 0."); _ok=false; }
#else
        _volt[_nrSamples] = io->Adc->Value[io_tail];   
        _curr[_nrSamples] = io->Adc->Value[io_tail + 1];
#endif

        io_tail += nrAdcSteps;
        if (io_tail >= maxInd) { io_tail -= maxInd; }
//        if (io_tail >= io_bufSize) { io_tail -= io_bufSize; }

        _nrSamples++;
    }
#ifdef __DEBUG__
    if( _sidx<DEBUGBUFSIZE) { _iotails3[_sidx-1] = io_tail; }
#endif
    return nrsamp2get;
}
