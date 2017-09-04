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



Sampler::Sampler() 
    : io( pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0) ) //! create new driver
    , _ok(false)
    , _nrSamples(0)
    , io_tmr(5000)     //!< The sampling rate in ns (5000 ns -> 200 kHz).
    , io_nrSteps(2)    //!< The number of active ADC steps 
                       // (must match setStep calls and io_mask).
    , io_mask(3 << 9)  //!< The active steps bitmaks (9 and 10).
    , io_bufSize((io->ESize >> 1) / io_nrSteps) //!< Max number of samples,
                                                     //   use all ERam
//    , maxInd(io_bufSize / io_nrSteps) //!< The maximum index in the ring buffer.
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
    if( idx < _nrSamples ) 
    {
       float ret = current_gain*((float)_curr[idx]-current_mean);
//       if( fabs(ret) < 0.05 ) return 0.0f;
       return ret;
    }
    return 0.0f;
}

//#define __DEBUG__
#define nrAdcSteps (io->Adc->ChAz)
int Sampler::getSamples()
{

#ifdef __DEBUG__
    static uint32 _nsamples[1024];
    static uint32 _ioheads[1024];
    static uint32 _iotails[1024];
    static uint32 _iotails2[1024];
    static uint32 _iotails3[1024];
    static uint32 _sidx=0;
#endif    

    static uint32 io_head=0, io_tail=0;

    uint32 lastsample = io->DRam[0];
    io_head = lastsample & 0xfffe; // only even indexes from AIN0 == voltage

//    uint32 nrSamples = ( io_head>io_tail ? (io_head-io_tail)/2
//                                         : (maxInd-io_tail+io_head)/2 );

    uint32 nrSamples = ( io_head>io_tail ? (io_head-io_tail)/2
                                         : (io_bufSize-io_tail+io_head)/2 );

#ifdef __DEBUG__
    if( _sidx<1024)
    {
        _ioheads[_sidx] = io_head;
        _iotails[_sidx] = io_tail;
        _iotails2[_sidx] = 1234;
        _iotails3[_sidx] = 5678;
        _nsamples[_sidx++]=nrSamples;
    }
#endif

    if( _nrSamples + nrSamples > SamplerBufSize )
    {
        //strcpy( _errMsg, "Sampler buffer overflow.");
        sprintf( _errMsg,
                 "Buffer will overflow when adding %d samples. \n Buffer Size now: %d.",
                 nrSamples,_nrSamples
               );
#ifdef __DEBUG__
//        printf("maxInd: %d \n", maxInd);
        printf("io_bufSize  : %d \n", io_bufSize);
        printf("nrAdcSteps: %d \n", nrAdcSteps);
        printf("Samples taken:\n");
        for( uint32 idx=0; idx<_sidx; idx++)
            printf(" %d: %d, %d, %d, %d, %d\n",
                    idx, _nsamples[idx], _ioheads[idx],
                    _iotails[idx],_iotails2[idx], _iotails3[idx]);
#endif        
        _ok = false;
        return 0;
    }

    if( io_head == lastsample ) // last sample misses current measurement
    {
       if( nrSamples <= 1
           || io_head < nrAdcSteps // Don't bother handling overflow here. 
         ) return 0;

       io_head -= nrAdcSteps; 
       nrSamples--;
    }
#ifdef __DEBUG__
    if( _sidx<1024) { _iotails2[_sidx-1] = io_tail; }
#endif
    for(uint32 cnt = nrSamples; cnt > 0; cnt--)
    {
        _volt[_nrSamples] = io->Adc->Value[io_tail];   
        _curr[_nrSamples] = io->Adc->Value[io_tail + 1];

        io_tail += nrAdcSteps;
//        if (io_tail >= maxInd) { io_tail -= maxInd; }
        if (io_tail >= io_bufSize) { io_tail -= io_bufSize; }

        _nrSamples++;
    }
#ifdef __DEBUG__
    if( _sidx<1024) { _iotails3[_sidx-1] = io_tail; }
#endif
    return nrSamples;
}
