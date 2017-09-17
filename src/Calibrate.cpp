/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

#include "unistd.h"
#include "time.h"
#include "stdio.h"

#include <iostream>
#include <unistd.h> //for usleep
#include <csignal>
#include <cstdlib> // for exit

#include <sys/time.h> // for timestamp

#include"PWM.h"
#include"GPIO.h"
#include"Sampler.h"

using namespace exploringBB;
using namespace std;

#define PWM_OUT P9_21 // pin for PWM output

//#define GPO_OUT P9_23 // pin for GPIO output
#define GPIO_OUT 49 // GPIO output P9_23


static PWM           _pwm("pwm_test_P9_21.12");  // P9_21 MUST be loaded as a slot before use
static float         pwm_freq = 5000;
static unsigned int  pwm_duration = 50000;  // in ns. 5 ms
static GPIO          _outGPIO(GPIO_OUT);
static Sampler       sampler;

static uint32        startChrgIdx=0, stopChrgIdx=0, startDischrgIdx=0, stopDischrgIdx=0;

void startCharge()
{
    if(_pwm.isRunning())
        _pwm.stop();


    _pwm.setPolarity(PWM::ACTIVE_HIGH);  // using active high PWM
    _pwm.setFrequency(pwm_freq);      // Set the period as a frequency
    _pwm.setDutyCycle(pwm_duration);

    sampler.reset();

    usleep(10000);       // 10 ms 
    startChrgIdx = sampler.lastIdx();

    _pwm.run();
}

void stopCharge()
{
    //      if (pruio_pwm_setValue(io, PWM_OUT, freq, 0.0)) { // stop charging
    //                printf("failed stoping @PWM (%s)\n", io->Errr); break;}

    if(_pwm.isRunning())
        _pwm.stop();

    usleep(10000);       // 10 ms 
    stopChrgIdx = sampler.lastIdx();
}

void startDischarge()
{
    startDischrgIdx = sampler.lastIdx();
    usleep(10000);       // 10 ms 

    _outGPIO.setDirection(OUTPUT);
    _outGPIO.setValue(HIGH);
}

void stopDischarge()
{
    //if (pruio_gpio_setValue(io, GPO_OUT, 0)) { //     stop discharging
    //printf("failed discharging stop (%s)\n", io->Errr); break;}
    
    _outGPIO.setValue(LOW);

    usleep(10000);       // 10 ms 
    stopDischrgIdx = sampler.lastIdx();
}


void cleanUp()
{
    stopCharge();
    stopDischarge();
    sampler.cleanUp();
}


void signalHandler( int signum ) {
    cout << "Interrupt signal (" << signum << ") received.\n";

    cleanUp();

    exit(signum);
}

unsigned long timeStamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}


#include <iostream>
#include <string>
#include <math.h>

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

    StdDeviation( bool current=true)
        : max( sampler.nrSamples() )
        , value( new double[max])
    {
        for( uint32 idx=0; idx<max; idx++)
        {
            if( current) 
                value[idx]=sampler.getCurrent(idx);
            // else:  TODO
        }
    }

    ~StdDeviation() { delete value; }
 

    double CalculateMean()
    {
        double sum = 0;

        for(uint32 i = 0; i < max; i++)
            sum += value[i];

        return (sum / max);
    }
 

    double CalculateVariane()
    {
        mean = CalculateMean();

        double temp = 0;

        for(uint32 i = 0; i < max; i++)
            { temp += (value[i] - mean) * (value[i] - mean) ; }

        return temp / max;
    }


    double CalculateSampleVariane()
    {
        mean = CalculateMean();

        double temp = 0;

        for(uint32 i = 0; i < max; i++)
            { temp += (value[i] - mean) * (value[i] - mean) ; }

        return temp / (max - 1);
    }

    double GetStandardDeviation()
        { return sqrt(CalculateVariane()); }

    double GetSampleStandardDeviation()
        { return sqrt(CalculateSampleVariane()); }
};

 
//! The main function.
int main(int argc, char **argv)
{
    // register signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    printf("Entered main\n");
    if( !sampler.ok() ) { cleanUp(); return 1; }
    printf("Sampler ok.\n");

    _outGPIO.setDirection(OUTPUT);
    printf("Start discharging.\n");
    startDischarge();
    usleep( 1000000 );
    stopDischarge();
    printf("Discharging done.\n");

    sampler.reset();

    unsigned long startTime=timeStamp();

    int n;
    for(n = 0; n < 50000; n++)
    {
        if( !sampler.getSamples() )
        {
            if( ! sampler.ok() )
                { printf("Sampler error (%s)\n", sampler.errMsg()); break;}
            else
                printf("No samples fetched....\n");
        }

        usleep(50); // At 50 us, we will fetch about 10 samples 
    }

    unsigned long stopTime=timeStamp();

    float elapsed = (stopTime-startTime)/1e6;
    printf("Sampling took %f sec.\n", elapsed);


    printf("Loops done: %d\n",n);

/*
    uint32 nrSamples = sampler.nrSamples();

    for( uint32 idx=0; idx<sampler.lastIdx(); idx++)
    {
        float volt = sampler.volt(idx);
        float curr = sampler.curr(idx);

        float dPow = curr * volt * sampler.period();
        Joules += dPow;
    }
*/

    StdDeviation sd;
 
    double mean = sd.CalculateMean();

    double variance = sd.CalculateVariane();

    double samplevariance = sd.CalculateSampleVariane();

    double sampledevi = sd.GetSampleStandardDeviation();

    double devi = sd.GetStandardDeviation();

 

    char buf[1024];

    sprintf(buf, "Total Numbers\t\t\t: %10d\n", sampler.nrSamples());

    std::cout << buf;

    sprintf(buf, "Mean\t\t\t\t: %10.5lf\nPopulation Variance\t\t: %10.4lf\n", mean, variance);

    std::cout << buf;

    sprintf(buf, "Sample variance\t\t\t: %10.4lf\n", samplevariance);

    std::cout << buf;

    sprintf(buf, "Population Standard Deviation\t: %10.4lf\n", devi);

    std::cout << buf;

    sprintf(buf, "Sample Standard Deviation\t: %10.4lf\n", sampledevi);

    std::cout << buf;


    cleanUp();
    return 0;
}
