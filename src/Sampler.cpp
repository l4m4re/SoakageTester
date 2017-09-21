/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

//#include "time.h"
#include "Sampler.h"
#include "pruio.h"
#include "pruio_pins.h"
#include "stdio.h"
#include <string.h>
#include <math.h>
#include <unistd.h>   // for usleep
#include <sys/time.h> // for timestamp
//#include <iostream>
//#include <string>

using namespace std;


static uint32 io_head=0, io_tail=0;

#include <iostream>
#include <bitset>
void printBinary( uint16 i )
{
    std::cout << std::bitset<16>(i);
    std::cout << std::endl;
}

//#define HIGH_SPEED

Sampler::Sampler() 
    : io( pruio_new(PRUIO_ACT_ADC, 0, 0, 0) ) //! create new driver
      // Only ADC active. For all subsystems use PRUIO_DEF_ACTIVE
    , _nrSamples(0)
    , _ok(false)
#ifdef HIGH_SPEED
//    , io_tmr(2500)     //!< The sampling rate in ns (2500 ns -> 400 kHz).
//    , io_tmr(3333)     //!< The sampling rate in ns (3333 ns -> 300 kHz).
//    , io_tmr(1000)     //!< The sampling rate in ns (2500 ns -> 400 kHz).
//    , io_tmr(2222)     //!< The sampling rate in ns (2000 ns -> 500 kHz).
    , io_tmr(5000)   //!< The sampling rate in ns (5000 ns -> 200 kHz).
#else
    , io_tmr(5000)   //!< The sampling rate in ns (5000 ns -> 200 kHz).
                     // This is independent of the number of channels.
#endif
    , io_nrSteps(2)    //!< The number of active ADC steps 
                       // (must match setStep calls and io_mask).
    , io_mask(3 << 9)  //!< The active steps bitmaks (9 and 10).
    , io_bufSize((io->ESize >> 1) / io_nrSteps) //!< Max number of samples,
                                                     //   use all ERam
    , maxInd(io_bufSize * io_nrSteps) //!< The maximum index in the ring buffer.
//    , current_mean(2035.8f)
    , current_mean(1.0f)
{
    if (io->Errr){
        printf("constructor failed (%s)\n", io->Errr); return;}

// pruio_adc_setStep documentation:
//
// http://users.freebasic-portal.de/tjf/Projekte/libpruio/doc/html/class_adc_udt.html#a243d91f0b7b7a29ada9bc14364c3284f
//
// This function is used to adapt a step configuration. In the constructor,
// steps 1 to 8 get configured for AIN-0 to AIN-7 (other steps stay
// un-configured). By this function you can customize the default settings and
// / or configure further steps (input channel number, avaraging and delay
// values).
//
// Parameters
//     Stp  Step index (0 = step 0 => charge step, 1 = step 1 (=> AIN-0 by
//          default), ..., 17 = idle step)-
//     ChN  Channel number to scan (0 = AIN-0, 1 = AIN-1, ...)-
//     Av   New value for avaraging (defaults to 4)-
//     SaD  New value for sample delay (defaults to 0)-
//     OpD  New value for open delay (defaults to 0x98)-

//#define USE_AIN_0

#ifdef HIGH_SPEED
# define Av  0
#else
# define Av  3
#endif
#define SaD 0
#define OpD 1

#ifdef USE_AIN_0
    printf("Sampler: Using AIN-0 for Voltage\n");
    if (pruio_adc_setStep(io, 9, 0, Av, SaD, OpD)){
        // step 9, AIN-0 -> voltage
        printf("ADC step 1 init failed: (%s)\n", io->Errr); return;}
#else
    printf("Sampler: Using AIN-2 for Voltage\n");
    if (pruio_adc_setStep(io, 9, 2, Av, SaD, OpD)){
        // step 9, AIN-2 -> voltage
        printf("ADC step 3 init failed: (%s)\n", io->Errr); return;}
#endif

    if (pruio_adc_setStep(io, 10, 1, Av, SaD, OpD)){
        // step 10, AIN-1 -> current
        printf("ADC step 2 init failed: (%s)\n", io->Errr); return;}

#define mMDS 0 // Bit encoding == shift value
    if (pruio_config(io, io_bufSize, io_mask, io_tmr, mMDS))
    { //  configure driver
        printf("config failed (%s)\n", io->Errr); return;
    }
#undef mMDS

//    printf("Io_mask:\t"); printBinary( io_mask );

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

//#define current_mean     1997.7f    // When probe connected to AIN !!
#define current_gain     1.0f/165.0625f
float Sampler::getCurrent( uint32 idx )
{
    float ret = current_gain*(((float)curr(idx))-current_mean);
//    if( fabs(ret) < 0.02 ) return 0.0f;
    return ret;
}

//#define voltage_div     74.15f
#define voltage_div     73.9f
float Sampler::getVoltage( uint32 idx )
{
    float ret = ((float)volt(idx))/voltage_div;
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

        _volt[_nrSamples] = io->Adc->Value[io_tail];
        _curr[_nrSamples] = io->Adc->Value[io_tail + 1];

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


unsigned long timeStamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}


/*  Arduino:
 
    Use of millis() and rollover

    http://forum.arduino.cc/index.php?topic=122413

    if all your time calculations are done as:
    
        if  ((later_time - earlier_time ) >=duration ) {action}

    then the rollover does generally not come into play.

    Q: Are there instances where the rollover does come into play?
    A: When duration is >= the rollover period.  
       (Or if you use signed comparison, >= 1/2 the rollover period).
       
       
    https://www.baldengineer.com/arduino-how-do-you-reset-millis.html
    
    Avoiding rollover and checking how much time as passed is done in a single line:
    
      if ((unsigned long)(millis() - previousMillis) >= interval)

    That single line of code is all that is really needed, to avoid rollover! 
    
*/



void Sampler::sleepNSample(unsigned long usecs)
{   
    const __useconds_t period=100; // At 500 us, we will fetch about 20 samples 

    unsigned long start_time = timeStamp();
    unsigned long elapsed = 0;

    getSamples();

    elapsed = timeStamp() - start_time;
    while( elapsed <= usecs )
    {
        usleep(period);
        getSamples();
        elapsed = timeStamp() - start_time;
    }

    getSamples();
}


class StdDeviation
{
// 
// Adapted from: 
//
//    http://www.softwareandfinance.com/CPP/MeanVarianceStdDevi.html
//
// There is no explicit license information on the site, but it is intended
// for educational purposes and contains many tutorials. It is therefore
// assumed the original author has no objection against re-use and/or
// re-licensing of this class.
//
private:

    uint32   max;
    double*  value;
    double   mean;

public:

    StdDeviation(Sampler& sampler, uint32 startidx, uint32 stopidx)
        : max( stopidx-startidx+1 )
        , value( new double[max])
    {
        uint32 validx=0;
        for( uint32 idx=startidx; idx<=stopidx; idx++)
        {
            value[validx++]= (double)sampler.curr(idx);
        }
    }

    StdDeviation(double* values, uint32 nrvals)
        : max( nrvals )
        , value( new double[max])
    {
        for( uint32 idx=0; idx<nrvals; idx++)
        {
            value[idx]= values[idx];
        }
    }


    ~StdDeviation() { delete value; }
 

    double CalculateMean()
    {
        double sum = 0;

        for(uint32 i = 0; i < max; i++)
        {
            sum += value[i];
        }

        return (sum / max);
    }

    double CalculateVariane(double mean)
    {
        double temp = 0;

        for(uint32 i = 0; i < max; i++) 
            { temp += (value[i] - mean) * (value[i] - mean) ; }

        return temp / max;
    }

    double GetStandardDeviation(double mean)
        { return sqrt(CalculateVariane(mean)); }

};

#define maxMeans 256
void Sampler::calibrateCurrent()
{
    static double means[maxMeans];
    static uint32 meansidx    = 0;
    static bool   meansfilled = false;

//    long sample_time_usecs = 500000; // 0.5 sec
//    long sample_time_usecs = 5000;  // 5 msec
    long sample_time_usecs = 10000;  // 10 msec

    getSamples();
    uint32 startidx = lastIdx();
    sleepNSample( sample_time_usecs );
    uint32 stopidx = lastIdx();

    StdDeviation sd(*this, startidx, stopidx);

    means[meansidx++] = sd.CalculateMean();
    if( meansidx > maxMeans ) { meansidx=0; meansfilled=true;}
 
    if( meansfilled )
    {
        StdDeviation sd2(means, maxMeans);
        current_mean = sd2.CalculateMean();
    }
    else
    {
        StdDeviation sd2(means, meansidx);
        current_mean = sd2.CalculateMean();
    }
}
