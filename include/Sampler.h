/** \file Sampler.h
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

//#include "unistd.h"
//#include "time.h"
//#include "stdio.h"
//#include "pruio.h"
//#include "pruio_pins.h"

typedef signed char int8;      //!< 8 bit signed integer data type.
typedef short int16;           //!< 16 bit signed integer data type.
typedef int int32;             //!< 32 bit signed integer data type.
typedef unsigned char uint8;   //!< 8 bit unsigned integer data type.
typedef unsigned short uint16; //!< 16 bit unsigned integer data type.
typedef unsigned int uint32;   //!< 32 bit unsigned integer data type.
typedef float float_t;         //!< float data type.


#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
     //! forward declaration
     typedef struct pruIo pruIo;
#ifdef __cplusplus
 }
#endif /* __cplusplus */

#define SamplerBufSize 10*200000  // about 10 seconds

class Sampler {
  public:

                    Sampler();
                    ~Sampler();

    int             getSamples();
    void            cleanUp();
    void            reset();

    inline bool     ok()            { return _ok; }
    inline uint32   nrSamples()     { return _nrSamples; }
    inline uint32   lastIdx()       
                        { return _nrSamples>0 ? _nrSamples-1 :_nrSamples; }

    inline uint32   getSamplesNGetLastIdx()
                    {
                        getSamples();
                        return lastIdx();
                    }       

    inline float    period()        { return io_tmr * 1e-9; }

//    float           getVolt( uint32 idx );
    float           getCurrent( uint32 idx );

    inline uint32   volt( uint32 idx )
                    { 
                        if( idx < _nrSamples ) return _volt[idx];
                        return 0;
                    }
    inline uint32   curr( uint32 idx )
                    { 
                        if( idx < _nrSamples ) return _curr[idx];
                        return 0;
                    }

    const char*     errMsg()       { return _errMsg; }


  private:

    pruIo*          io;
    bool            _ok;

    uint32          _nrSamples;
    uint32          _volt[SamplerBufSize];
    uint32          _curr[SamplerBufSize];

    // pruio ADC parameters
    const uint32    io_tmr;    //!< The sampling rate in ns (5000 ns -> 200 kHz).
    const uint32    io_nrSteps; //!< The number of active ADC steps
                            // (must match setStep calls and mask).
    const uint32    io_mask;   //!< The active steps bitmaks (9 and 10).
    const uint32    io_bufSize; //!< The number of samples, use all ERam
    const uint32    maxInd; //!< The maximum index in the ring buffer.

    char            _errMsg[256];
};
