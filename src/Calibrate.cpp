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

using namespace std;

static Sampler       sampler;

void cleanUp()
{
    sampler.cleanUp();
}


void signalHandler( int signum ) {
    cout << "Interrupt signal (" << signum << ") received.\n";

    cleanUp();

    exit(signum);
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
                value[idx]= (double)sampler.curr(idx);
                //value[idx]= (double)sampler.getCurrent(idx);
            else
                //value[idx]= (double)sampler.volt(idx);
                value[idx]= (double)sampler.getVoltage(idx);
        }
    }

    ~StdDeviation() { delete value; }
 

    double CalculateMean()
    {
        double sum = 0;

        for(uint32 i = 0; i < max; i++)
        {
            sum += value[i];
//            printf("%10.5lf\n", value[i]);
        }

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

void computeStatistics( bool current = true)
{
    StdDeviation sd( current );
 
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

    //long sample_time_usecs = 10000000;  // 10 sec
    //long sample_time_usecs = 1000000;  // 1 sec
    long sample_time_usecs = 500000;  // 0.5 sec
    sampler.sleepNSample( sample_time_usecs );

    if( ! sampler.ok() )
        printf("Sampler error (%s)\n", sampler.errMsg()); 

    unsigned long stopTime=timeStamp();

    uint32 nsamples = 2 * sampler.nrSamples(); // 2 channels

    double elapsed = (stopTime-startTime)/1e6;
    printf("Sampling took %f sec.\n", elapsed);

    double rate = nsamples/(1000.0 * elapsed); // in kS/s
    printf("Sampling rate %f kS/s (%f kS/s per chan).\n", rate, rate/2);

    computeStatistics(true); // current
    computeStatistics(false); // voltage

    cleanUp();
    return 0;
}
