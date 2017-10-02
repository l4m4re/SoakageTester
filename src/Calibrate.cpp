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

//#include <sys/time.h> // for timestamp

#include"Sampler.h"
#include"StdDeviation.h"

using namespace std;

static Sampler       sampler;

void cleanUp()
{
//    sampler.cleanUp();
}


void signalHandler( int signum ) {
    cout << "Interrupt signal (" << signum << ") received.\n";

    cleanUp();

    exit(signum);
}


void computeStatistics( bool current = true)
{
    StdDeviation sd( sampler, 0, sampler.lastIdx(), current );
 
    double mean = sd.CalculateMean();

//    double variance = sd.CalculateVariane();

//    double samplevariance = sd.CalculateSampleVariane();

//    double sampledevi = sd.GetSampleStandardDeviation();

    double devi = sd.GetStandardDeviation();

    if( current )
        printf("--- Current ---\n");
    else
        printf("--- Voltage ---\n");

//    printf("Total Numbers\t\t\t: %10d\n", sampler.nrSamples());

    printf("Mean\t\t\t: %10.5lf\n", mean);
            
//    printf"Population Variance\t\t: %10.4lf\n", variance);

//    printf("Sample variance\t\t\t: %10.4lf\n", samplevariance);

    printf("Standard Deviation\t: %10.4lf\n", devi);

//    printf("Sample Standard Deviation\t: %10.4lf\n", sampledevi);
}

 
//! The main function.
int main(int argc, char **argv)
{
    // register signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    unsigned long startTime=timeStamp();

    if( !sampler.ok() ) { cleanUp(); return 1; }
    sampler.reset();

    long sample_time_usecs = 10000000;  // 10 sec
    //long sample_time_usecs = 1000000;  // 1 sec
    //long sample_time_usecs = 500000;  // 0.5 sec
    usleep( sample_time_usecs );

    if( ! sampler.ok() )
        printf("Sampler error (%s)\n", sampler.errMsg()); 

    sampler.stop();

    unsigned long stopTime=timeStamp();

    uint32 nsamples = 2*sampler.nrSamples(); // 2 channels

    double elapsed = (stopTime-startTime)/1e6;
    printf("Sampling took %f sec.\n", elapsed);

    double rate = nsamples/(1000.0 * elapsed); // in kS/s
    printf("Sampling rate %f kS/s (%f kS/s per chan).\n", rate, rate/2);

    computeStatistics(true); // current
    computeStatistics(false); // voltage

    cleanUp();
    return 0;
}
