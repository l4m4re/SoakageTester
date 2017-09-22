#ifndef STDEVIATION_H
#define STDEVIATION_H

#include "Types.h"

class Sampler;

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

    StdDeviation( Sampler& sampler, uint32 startidx, uint32 stopidx, bool current=true);
    StdDeviation(double* values, uint32 nrvals);
    ~StdDeviation();

    double CalculateMean();
    double CalculateVariane();
    double CalculateSampleVariane();
    double GetStandardDeviation();
    double GetSampleStandardDeviation();
};

#endif
