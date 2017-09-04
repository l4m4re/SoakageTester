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

#include<iostream>
#include<unistd.h> //for usleep
#include <csignal>
#include <cstdlib> // for exit
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


//! The main function.
int main(int argc, char **argv)
{
    // register signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

//    printf("Entered main\n");
    if( !sampler.ok() ) { cleanUp(); return 1; }
//    printf("Sampler ok.\n");

    //uint32 a, e; //!< index of start and end of related ring buffer area
    uint16 volt_1 = 1800; //!< stop charging (= Volt * 65520 / 1.8)
    uint16 volt_2 = 10; //!< stop discharging

    uint16 v_max = 0;
    uint16 v_val = 0;

    _outGPIO.setDirection(OUTPUT);
    startDischarge();
    usleep( 1000000 );
    stopDischarge();

    printf("run, injoules, outjoules, perc\n");


    for(int n = 0; n < 100; n++)
    {
//        printf("Start charging.\n");

        startCharge();

        v_max = 0;
        do { //                               wait for end of charge cycle
            if( sampler.getSamples() )
            {
                v_val = sampler.volt( sampler.lastIdx() );
                if( v_val > v_max)
                {
                    v_max = v_val;
//                    printf("%d\n",v_val);
                }
            }
            else
            {
                if( ! sampler.ok() )
                    { printf("Sampler error (%s)\n", sampler.errMsg()); return 1;}
                else
                    printf("No samples fetched....\n");
            }

            usleep(50); // At 50 us, we will fetch about 10 samples 
        } while(v_val < volt_1);

//        printf("V_max: %d\n",v_val);

        stopCharge();
        startDischarge();

        do { //                               wait for end of charge cycle
            if( sampler.getSamples() )
            {
                v_val = sampler.volt( sampler.nrSamples() );
                if( v_val > v_max)
                {
                    v_max = v_val;
                //                printf("%d\n",v_val);
                }
            }
            usleep(50); // At 50 us, we will fetch about 10 samples 
        } while(v_val > volt_2);

        stopDischarge();

        // Compute in/out Joules from buffer
        
        float inJoules = 0, outJoules = 0;

        for( uint32 idx=startChrgIdx; idx<stopChrgIdx; idx++)
        {
            float volt = ((float)sampler.volt(idx))/60.0f;
            float curr = sampler.getCurrent(idx);

            float dPow = curr * volt * sampler.period();
            inJoules += dPow;
        }

        for( uint32 idx=startDischrgIdx; idx<stopDischrgIdx; idx++)
        {
            float volt = ((float)sampler.volt(idx))/60.0f;
            float curr = sampler.getCurrent(idx);

            float dPow = curr * volt * sampler.period();
            outJoules += dPow;
        }
        outJoules *= -1.0f;

//        printf("Joules in  : %f\n",inJoules);
//        printf("Joules out : %f\n",outJoules);
//        printf("Perc out/in: %f\n",100.0f*outJoules/inJoules);

        printf("%d, %f, %f, %f\n",n,inJoules,outJoules,100.0f*outJoules/inJoules);

//        pwm_freq += 100; //                                   set new frequency
        usleep( 1000000 );
        startCharge();
    }

    cleanUp();
    return 0;
}
