#ifndef SAMPLER_H
#define SAMPLER_H

#include "Types.h"
#include "stdio.h"

#define SampleRate     800000
//#define SamplerBufSize 10*SampleRate  // about 10 seconds
#define SamplerBufSize 100*SampleRate  // about 100 seconds

unsigned long timeStamp();

class Sampler {
  public:
                    Sampler();
                    ~Sampler();

    void            cleanUp();
    void            reset();

    inline bool     ok()            { return _ok; }
    inline uint32   nrSamples()     { return _nrSamples; }
    inline float    period()        { return  1.25e-6;   } // 800 kS/s

    inline uint32   lastIdx()       
                        { return _nrSamples>0 ? _nrSamples-1 :_nrSamples; }

    float           getVoltage( uint32 idx );
    float           getCurrent( uint32 idx );

    inline uint16   volt( uint32 idx )
                    { 
                        if( idx < _nrSamples ) return _volt[idx];

                        sprintf( const_cast<char*>(_errMsg),
                                        "Out of range error.\n");
                        _ok = false;
                        return 0;
                    }
    inline uint16   curr( uint32 idx )
                    { 
                        if( idx < _nrSamples ) return _curr[idx];

                        sprintf( const_cast<char*>(_errMsg),
                                        "Out of range error.\n");
                        _ok = false;
                        return 0;
                    }


    const char*     errMsg()       { return const_cast<char*>(_errMsg); }

    inline float    currentMean()  { return current_mean; }
    void            calibrateCurrent();

    void            stop()         { _active = false; }

  private:

    volatile static uint32   _nrSamples;
    volatile static uint16   _volt[];
    volatile static uint16   _curr[];
    volatile static bool     _ok;
    volatile static bool     _active;
    volatile static char     _errMsg[];

    float           current_mean;

    static void*    samplingThread(void* param);
    void            load_device_tree_overlay();
    void            init_pru_program();
    void            start_thread();
    void            stop_thread();

};

#endif
