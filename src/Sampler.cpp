/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

//#include "time.h"
#include "Sampler.h"
#include "StdDeviation.h"

#include <math.h>
#include <unistd.h>   // for usleep
#include <sys/time.h> // for timestamp
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
//#include <signal.h>
#include <sys/time.h>
//#include <fcntl.h>
//#include <sys/mman.h>
//#include <sndfile.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>

#define PRU_NUM 0

#ifndef START_ADDR
#error "START_ADDR must be defined"
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////
// Globals
//

uint32* shared_ram = NULL;
pthread_t thread   = 0;

volatile uint32 Sampler::_nrSamples = 0;
volatile uint16 Sampler::_volt[SamplerBufSize];
volatile uint16 Sampler::_curr[SamplerBufSize];
volatile bool   Sampler::_ok;
volatile bool   Sampler::_active;
volatile char   Sampler::_errMsg[256];
         

Sampler::Sampler() 
    : current_mean(1.0f)
{
    strcpy( const_cast<char*>(_errMsg), "");
    _ok = true;
    _active = true;

    // Load device tree overlay to enable PRU hardware.
    load_device_tree_overlay();

    // Load and run binary into pru0
    init_pru_program();

    _nrSamples = 0;

    start_thread();
}

Sampler::~Sampler() 
{
    cleanUp();
    stop_thread();
    prussdrv_exit();
}


void Sampler::cleanUp()
{
    prussdrv_pru_disable(PRU_NUM);
}

void Sampler::reset()
{
    _nrSamples = 0;
    _active    = true;
}

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

#define channels 2
void* Sampler::samplingThread(void* param)
{
    printf("Started Sampling thread\n");

    uint32 nrsamp2get = 0;
    uint32 buffer_position;

//    int count = 0;
    while(1)
    {
        // Wait for interrupt from PRU
        prussdrv_pru_wait_event(PRU_EVTOUT_0);
        prussdrv_pru_clear_event(PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);

        if( _active )
        {
            // Read number of samples available
            nrsamp2get = shared_ram[1];

            // Read position in RAM
            buffer_position = shared_ram[0];

/*
            // Original: Use memcopy to copy samples to single buffer
            //
            memcpy(&(buffer[buffer_count]), &(shared_ram[buffer_position]),
                                buffer_size*sizeof(uint32));
            buffer_count += nrsamp2get;
*/

            if( _nrSamples + nrsamp2get > SamplerBufSize )
            {
                //strcpy( _errMsg, "Sampler buffer overflow.");
                sprintf( const_cast<char*>(_errMsg),
                         "Buffer will overflow when adding %d samples. \n Buffer Size now: %d.",
                         nrsamp2get,_nrSamples
                       );

                _ok = false;
                return NULL;
            }


            for(uint32 cnt = 0; cnt < nrsamp2get;)
            { 
                //  & 0xFFFF : mask out channel ID, etc.
                _volt[_nrSamples] = shared_ram[buffer_position+cnt++]   & 0x0FFF;
                _curr[_nrSamples] = shared_ram[buffer_position+cnt++] & 0x0FFF;
                _nrSamples++;
            }
/*
            if(count%10000 == 0){
                // Print info

                uint32 val1 = shared_ram[buffer_position];
                val1 &= 0xFFF;
                uint32 val2 = shared_ram[buffer_position+1];
                val2 &= 0xFFF;

                printf("Values: %u %u\n", val1, val2);
                printf("In my buf: %u %u\n", _volt[_nrSamples-1],_curr[_nrSamples-1]);

                printf("Buffer addr: %u \n", shared_ram[0]);
                printf("buffer  cnt: %u \n", shared_ram[1]);
            }
            count++;
*/
        }
    }

    return NULL;
}


unsigned long timeStamp()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}

#define maxMeans 256
void Sampler::calibrateCurrent()
{
    static double means[maxMeans];
    static uint32 meansidx    = 0;
    static bool   meansfilled = false;

//    long sample_time_usecs = 500000; // 0.5 sec
//    long sample_time_usecs = 5000;  // 5 msec
    long sample_time_usecs = 10000;  // 10 msec

    uint32 startidx = lastIdx();
    usleep( sample_time_usecs );
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

#define OVERLAY "PRUSSDRV"
void Sampler::load_device_tree_overlay()
{
   // Check if device tree overlay is loaded, load if needed.
   int device_tree_overlay_loaded = 0; 
   FILE* f;
   f = fopen("/sys/devices/bone_capemgr.9/slots","rt");
   if(f==NULL){
      printf("Initialisation failed (fopen rt)");
      exit(1);
   }
   char line[256];
   while(fgets(line, 256, f) != NULL){
      if(strstr(line, OVERLAY ) != NULL){
         device_tree_overlay_loaded = 1; 
      }
   }
   fclose(f);

   if(!device_tree_overlay_loaded){
      f = fopen("/sys/devices/bone_capemgr.9/slots","w");
      if(f==NULL){
         printf("Initialisation failed (fopen)");
         exit(1);
      }
      fprintf(f, OVERLAY );
      fclose(f);
      usleep(100000);
   }
}

void Sampler::init_pru_program()
{
   tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
   prussdrv_init();
   prussdrv_open(PRU_EVTOUT_0);
   prussdrv_pruintc_init(&pruss_intc_initdata);

   // Get pointer to shared ram
   void* p;
   prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &p);
   shared_ram = (uint32*)p;

   prussdrv_load_datafile(PRU_NUM, "../src/data.bin");
   prussdrv_exec_program_at(PRU_NUM, "../src/text.bin", START_ADDR);
}



void Sampler::start_thread()
{
    pthread_attr_t attr;
    if(pthread_attr_init(&attr)){
        printf("Cannot start a new thread.\n");
        exit(1);
    }
    if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)){
        printf("Cannot start a new thread.");
        exit(1);
    }
    if(pthread_create(&thread, &attr, &Sampler::samplingThread, NULL)){
        printf("Cannot start a new thread.");
        exit(1);
    }
}

void Sampler::stop_thread()
{   int print = 10;
    if( !thread) return;
    while(pthread_cancel(thread) && print--)
    {
        printf("Stopping thread\n");
    }
    thread = 0;
    printf("Stopped thread\n");
}

