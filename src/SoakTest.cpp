/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: 
  `g++ -Wall -o SoakTest.cpp PWM.cpp GPIO.cpp util.cpp -lpruio -lprussdrv -lpthread`

*/

//#include "unistd.h"
#include "time.h"
#include "stdio.h"

#include<iostream>
#include <csignal>
#include <cstdlib>  // for exit
#include <unistd.h> // for usleep

#include"PWM.h"
#include"GPIO.h"
#include"Sampler.h"

#include"Biquad.h"

using namespace exploringBB;
using namespace std;

//#define PWM_OUT P9_21 // pin for PWM output
//#define GPO_OUT P9_23 // pin for GPIO output
#define GPIO_OUT 49 // GPIO output P9_23

#define PWM_START_FREQ 500
#define PWM_STOP_FREQ  35000
// P9_21 MUST be loaded as a slot before use
static PWM           charge_pwm("pwm_test_P9_21.12"); 
static float         charge_pwm_freq     = PWM_START_FREQ;
//static float         charge_pwm_freq     = 500;
//static unsigned int  charge_pwm_duration = 1600;  // in ns. About the minimum
//static unsigned int  charge_pwm_duration = 1750;  // in ns. 
static unsigned int  charge_pwm_duration = 5000;  // in ns. 5 us

// The switch-off time of the circuitry driving the gate of the MOSFET is in
// the order of 300 usec, which means we could maximally drive the circuit at
// about 2 kHz, which is way to slow. 
//
// The opto-driver appears to switch off pretty fast, but the MPSA42's don't.
// Perhaps a base-discharge resistor over these could improve the situation.

static GPIO          _outGPIO(GPIO_OUT);

static Sampler       sampler;


static uint32        startChrgIdx=0, stopChrgIdx=0,
                     startDischrgIdx=0, stopDischrgIdx=0;

void startCharge()
{
    if(charge_pwm.isRunning())
        charge_pwm.stop();

    charge_pwm.setFrequency(charge_pwm_freq);      // Set the period as a frequency
    charge_pwm.setDutyCycle(charge_pwm_duration);

    startChrgIdx = sampler.getSamplesNGetLastIdx();
    charge_pwm.run();

}

void stopCharge()
{
    //      if (pruiocharge_pwm_setValue(io, PWM_OUT, freq, 0.0)) { // stop charging
    //                printf("failed stoping @PWM (%s)\n", io->Errr); break;}

    if(charge_pwm.isRunning())
        charge_pwm.stop();

    stopChrgIdx = sampler.getSamplesNGetLastIdx();
}

void startDischarge()
{
//    if (pruio_gpio_setValue(sampler.io, GPO_OUT, 1)) { //     stop discharging
//        printf("failed discharging stop (%s)\n", sampler.io->Errr); return;}

    startDischrgIdx = sampler.getSamplesNGetLastIdx();

//    _outGPIO.setDirection(OUTPUT);
    _outGPIO.setValue(HIGH);
}

void stopDischarge()
{
//   if (pruio_gpio_setValue(sampler.io, GPO_OUT, 0)) { //     stop discharging
//       printf("failed discharging stop (%s)\n", sampler.io->Errr); return;}
    
    _outGPIO.setValue(LOW);

    stopDischrgIdx = sampler.getSamplesNGetLastIdx();
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


void buf2file(const char* fname, double* voltage, double* current)
{
    FILE * pFile;

    pFile = fopen (fname,"w");

    for( uint32 idx=0; idx<sampler.nrSamples(); idx++)
    {
        double volt = voltage[idx];
        double curr = current[idx];
        fprintf(pFile, "%f, %f\n",volt,curr);
        //fprintf(pFile, "%d, %d\n",sampler.volt(idx),sampler.curr(idx));
    }

    fclose (pFile);
}


int main(int argc, char **argv)
{
    // register signal handlers
    signal(SIGINT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);

    if( !sampler.ok() ) { cleanUp(); return 1; }

    charge_pwm.stop();
    charge_pwm.setPolarity(PWM::ACTIVE_HIGH);  // using active high PWM

    _outGPIO.setDirection(OUTPUT);


    float fully_charged_voltage = 27.0f;   //!< stop charging 
    //float fully_charged_voltage = 7.5f;   //!< stop charging 
    float fully_discharged_voltage = 0.01f; //!< stop discharging

    float v_val = 0.0f;
    float max_perc = 0.0f;

//    if (pruio_gpio_setValue(sampler.io, GPO_OUT, 0)) { //         configure GPIO
//         printf("setValue @GPO_OUT error (%s)\n", sampler.io->Errr); return 1;}
             
    sampler.calibrateCurrent();

    startDischarge();

    sampler.sleepNSample( 1000000 ); // 1 sec

    stopDischarge();

//    sampler.calibrateCurrent();


    printf("run, freq, injoules, outjoules, perc, sampler_current_mean\n");

    uint32 n=1;
    for(;;)
    {
//        float v_max = 0;
//        float v_min = 65000;

//        printf("Start charging.\n");
        sampler.reset();
        sampler.sleepNSample( 100 ); // 100 usec
//        sampler.calibrateCurrent();

        startCharge();

        const uint32 n_smp=32;

        bool done=false;
        do { //                               wait for end of charge cycle
            if( sampler.getSamples() )
            {
                done = true;

                for( uint32 cnt=0; cnt < n_smp; cnt++ )
                {
                    v_val = sampler.getVoltage( sampler.lastIdx()-cnt );
/*
                    if( v_val > v_max)
                    {
                        v_max = v_val;
                        printf("Max voltage: %d\n", v_max);
                    }
*/

                    if (v_val <= fully_charged_voltage) { done=false; break;}
                }
            }
            else
            {
                if( ! sampler.ok() )
                    { printf("Sampler error (%s)\n", sampler.errMsg()); return 1;}
                else
                    printf("No samples fetched....\n");
            }

            usleep(500); // At 500 us, we will fetch about 100 samples 
        } while( !done );

//        printf("V_max: %d\n",v_max);

        stopCharge();

//        sampler.sleepNSample( 1000 ); // 1 msec
        sampler.sleepNSample( 50000 ); // 50 msec
//        sampler.calibrateCurrent();

//        printf("Start discharging.\n");

        startDischarge();

        done=false;
        do { //                               wait for end of discharge cycle
            if( sampler.getSamples() )
            {
                done = true;

                for( uint32 cnt=0; cnt < n_smp; cnt++ )
                {
                    v_val = sampler.getVoltage( sampler.lastIdx()-cnt );
/*
                    if( v_val < v_min)
                    {
                        v_min = v_val;
                        printf("Min voltage: %d\n", v_min);
                    }
*/

                    if (v_val >= fully_discharged_voltage) { done=false; break;}
                }
            }
            else
            {
                if( ! sampler.ok() )
                    { printf("Sampler error (%s)\n", sampler.errMsg()); return 1;}
                else
                    printf("No samples fetched....\n");
            }

            usleep(500); // At 500 us, we will fetch about 100 samples 
        } while( !done );



//        sampler.sleepNSample( 10000 ); // 10 msec

        stopDischarge();

        sampler.sleepNSample( 10000 ); // 10 msec
        sampler.calibrateCurrent();


        // Compute in/out Joules from buffer
        
        double inJoules = 0, outJoules = 0;
//        int stage=0;



        uint32 nsamples = sampler.nrSamples();
        double* voltage = new double[nsamples];
        double* current = new double[nsamples];

        for( uint32 idx=0; idx<nsamples; idx++)
        {
            voltage[idx] = sampler.getVoltage(idx);
            current[idx] = sampler.getCurrent(idx);
        }


        Biquad* volt_lpFilter = new Biquad();    // create a Biquad, lpFilter;
        Biquad* curr_lpFilter = new Biquad();    // create a Biquad, lpFilter;

#define Fc           30000.0
#define sampleRate  200000.0 

        volt_lpFilter->setBiquad(bq_type_lowpass, Fc / sampleRate, 0.707, 0);
        curr_lpFilter->setBiquad(bq_type_lowpass, Fc / sampleRate, 0.707, 0);

        // filter a buffer of input samples, in-place
        for (uint32 idx = 0; idx < nsamples; idx++) 
        {
            voltage[idx] = volt_lpFilter->process(voltage[idx]);
            current[idx] = curr_lpFilter->process(current[idx]);
        }

        delete volt_lpFilter;
        delete curr_lpFilter;


//define PRINT_OUTPUT

#ifdef PRINT_OUTPUT        
        printf("-- start  --\n");
        for( uint32 idx=0; idx<startChrgIdx; idx++)
        {
            double volt = voltage[idx];
            double curr = current[idx];
            printf("%f, %f, %d\n",volt,curr,stage);
        }

        stage++;
        printf("-- charge --\n");
#endif
        for( uint32 idx=startChrgIdx; idx<stopChrgIdx; idx++)
        {
            double volt = voltage[idx];
            double curr = current[idx];
#ifdef PRINT_OUTPUT        
            printf("%f, %f, %d\n",volt,curr,stage);
#endif

//            double dPow = curr * volt * sampler.period();
            double dPow = curr * volt / sampleRate;
            inJoules += dPow;
        }

#ifdef PRINT_OUTPUT        
        stage++;
        printf("-- pause --\n");
        for( uint32 idx=stopChrgIdx; idx<startDischrgIdx; idx++)
        {
            double volt = voltage[idx];
            double curr = current[idx];
            printf("%f, %f, %d\n",volt,curr,stage);
        }

        stage++;
        printf("-- discharge --\n");
#endif
        for( uint32 idx=startDischrgIdx; idx<stopDischrgIdx; idx++)
        {
            double volt = voltage[idx];
            double curr = current[idx];
#ifdef PRINT_OUTPUT        
            printf("%f, %f, %d\n",volt,curr,stage);
#endif

//            double dPow = curr * volt * sampler.period();
            double dPow = curr * volt / sampleRate;
            outJoules += dPow;
        }
        outJoules *= -1.0f;

#ifdef PRINT_OUTPUT        
        stage++;
        printf("-- lead out --\n");
        for( uint32 idx=stopDischrgIdx; idx<sampler.nrSamples(); idx++)
        {
            double volt = voltage[idx];
            double curr = current[idx];
            printf("%f, %f, %d\n",volt,curr,stage);
        }
#endif

/*
        sampler.sleepNSample( 10000 );

        printf("-- done --\n");

        printf("Indexes: %d, %d, %d, %d, %d \n", startChrgIdx, stopChrgIdx, startDischrgIdx, stopDischrgIdx, sampler.nrSamples());
        printf("Joules in  : %f\n",inJoules);
        printf("Joules out : %f\n",outJoules);
        printf("Perc out/in: %f\n",100.0f*outJoules/inJoules);
*/


        float perc = 100.0f*outJoules/inJoules;


        printf("%d, %5.2f, %d, %5.4f, %5.4f, %3.4f, %5.4f\n",
                n, charge_pwm_freq, charge_pwm_duration,
                inJoules, outJoules, perc,
                sampler.currentMean());

        if( perc > max_perc && n>10 )
        {
            max_perc = perc;
            printf("Saving best result\n");

            buf2file( "/data/arend/work/SoakageTester/bin/buf.log",
                      voltage, current);
        }

        charge_pwm_freq *= 1.01; 
        //charge_pwm_freq += 10;

        float duty = charge_pwm_duration/(1e9/charge_pwm_freq);

        if( charge_pwm_freq  > PWM_STOP_FREQ || duty > 0.9 )
        { 
            charge_pwm_freq = PWM_START_FREQ;
            charge_pwm_duration += 100;
        }


        if( ! sampler.ok() )
        { 
            printf("Sampler error (%s)\n", sampler.errMsg());
            cleanUp(); 
            return 1;
        }

        sampler.calibrateCurrent();

        delete[] voltage;
        delete[] current;

        n++;
    }

    cleanUp();

//    printDebugInfo();
    return 0;
}
