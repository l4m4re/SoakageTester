#include "StdDeviation.h"
#include "Sampler.h"

#include <iostream>
#include <string>
#include <math.h>


StdDeviation::StdDeviation( Sampler& sampler, uint32 startidx, uint32 stopidx, bool current)
    : max( stopidx-startidx+1 )
    , value( new double[max])
{
    int idx=0;
    for( uint32 smpidx=startidx; smpidx<=stopidx; smpidx++)
    {
        if( current) 
            value[idx++]= (double)sampler.curr(smpidx);
            //value[idx]= (double)sampler.getCurrent(idx);
        else
            //value[idx]= (double)sampler.volt(idx);
            value[idx++]= (double)sampler.getVoltage(smpidx);
    }
}


StdDeviation::StdDeviation(double* values, uint32 nrvals)
    : max( nrvals )
    , value( new double[max])
{
    for( uint32 idx=0; idx<nrvals; idx++)
    {
        value[idx]= values[idx];
    }
}


StdDeviation::~StdDeviation() { delete value; }
 

double StdDeviation::CalculateMean()
{
    double sum = 0;

    for(uint32 i = 0; i < max; i++)
    {
        sum += value[i];
//      printf("%10.5lf\n", value[i]);
    }

    return (sum / max);
}
 

double StdDeviation::CalculateVariane()
{
    mean = CalculateMean();

    double temp = 0;

    for(uint32 i = 0; i < max; i++)
        { temp += (value[i] - mean) * (value[i] - mean) ; }

    return temp / max;
}


double StdDeviation::CalculateSampleVariane()
{
    mean = CalculateMean();

    double temp = 0;

    for(uint32 i = 0; i < max; i++)
        { temp += (value[i] - mean) * (value[i] - mean) ; }

    return temp / (max - 1);
}

double StdDeviation::GetStandardDeviation()
    { return sqrt(CalculateVariane()); }

double StdDeviation::GetSampleStandardDeviation()
    { return sqrt(CalculateSampleVariane()); }


