#include <Butterworth.h>


Butterworth::Butterworth()
{
    for( int idx=0; idx<NZEROS+1; idx++ )
        xv[idx]=0;
    for( int idx=0; idx<NPOLES+1; idx++ )
        yv[idx]=0;
}




/*

http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.html

You specified the following parameters:

    filtertype  =   Butterworth
    passtype    =   Lowpass
    ripple      =   
    order       =   8
    samplerate  =   800000
    corner1     =   50000
    corner2     =   
    adzero      =   

*/
/*
 
#define GAIN   1.125873410e+06

double Butterworth::process( double in)
{ 
    xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3];
    xv[3] = xv[4]; xv[4] = xv[5]; xv[5] = xv[6];
    xv[6] = xv[7]; xv[7] = xv[8]; 

    xv[8] = in / GAIN;

    yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3];
    yv[3] = yv[4]; yv[4] = yv[5]; yv[5] = yv[6];
    yv[6] = yv[7]; yv[7] = yv[8]; 

    yv[8] =   (xv[0] + xv[8]) + 8 * (xv[1] + xv[7]) + 28 * (xv[2] + xv[6])
                 + 56 * (xv[3] + xv[5]) + 70 * xv[4]
                 + ( -0.1313506708 * yv[0]) + (  1.3150271205 * yv[1])
                 + ( -5.8001901436 * yv[2]) + ( 14.7293833420 * yv[3])
                 + (-23.5703793650 * yv[4]) + ( 24.3572374240 * yv[5])
                 + (-15.8883798700 * yv[6]) + (  5.9884247836 * yv[7]);
    return yv[8];
}
*/


/*
You specified the following parameters:

    filtertype  =   Butterworth
    passtype    =   Lowpass
    ripple  =   
    order   =   8
    samplerate  =   800000
    corner1     =   200000
    corner2     =   
    adzero  =   
*/

#define GAIN   1.079064620e+02
double Butterworth::process( double in)
{ 
    xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3];
    xv[3] = xv[4]; xv[4] = xv[5]; xv[5] = xv[6];
    xv[6] = xv[7]; xv[7] = xv[8]; 

    xv[8] = in / GAIN;

    yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3];
    yv[3] = yv[4]; yv[4] = yv[5]; yv[5] = yv[6];
    yv[6] = yv[7]; yv[7] = yv[8]; 


    yv[8] =   (xv[0] + xv[8]) + 8 * (xv[1] + xv[7]) + 28 * (xv[2] + xv[6])
                 + 56 * (xv[3] + xv[5]) + 70 * xv[4]
                 + ( -0.0001717652 * yv[0]) + (  0.0000000000 * yv[1])
                 + ( -0.0204295879 * yv[2]) + (  0.0000000000 * yv[3])
                 + ( -0.2908881573 * yv[4]) + (  0.0000000000 * yv[5])
                 + ( -1.0609355992 * yv[6]) + (  0.0000000000 * yv[7]);

    return yv[8];
}
