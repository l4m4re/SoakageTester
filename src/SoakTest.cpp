/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: `g++ -Wall -o CapTest CapTest.c -lpruio -lprussdrv`

*/

#include "unistd.h"
#include "time.h"
#include "stdio.h"
#include "pruio.h"
#include "pruio_pins.h"

#include<iostream>
#include<unistd.h> //for usleep
#include <csignal>
#include <cstdlib> // for exit
#include"PWM.h"
#include"GPIO.h"

using namespace exploringBB;
using namespace std;

#define PWM_OUT P9_21 // pin for PWM output

//#define GPO_OUT P9_23 // pin for GPIO output
#define GPIO_OUT 49 // GPIO output P9_23


static PWM           _pwm("pwm_test_P9_21.12");  // P9_21 MUST be loaded as a slot before use
static float         pwm_freq = 5000;
static unsigned int  pwm_duration = 50000;  // in ns. 5 ms
static GPIO          _outGPIO(GPIO_OUT);
static pruIo         *io = 0;


// pruio ADC parameters
static const uint32 tmr = 5000; //!< The sampling rate in ns (5000 ns -> 200 kHz).
static const uint32 NoStep = 2; //!< The number of active ADC steps (must match setStep calls and mask).
static const uint32 mask = 3 << 9; //!< The active steps bitmaks (9 and 10).
static uint32 samp   = 0;    //!< The number of samples, use all ERam
static uint32 maxInd = 0;    //!< The maximum index in the ring buffer.


void startCharge()
{
    if(_pwm.isRunning())
        _pwm.stop();

    _pwm.setPolarity(PWM::ACTIVE_HIGH);  // using active high PWM
    _pwm.setFrequency(pwm_freq);      // Set the period as a frequency
    _pwm.setDutyCycle(pwm_duration);
    _pwm.run();
}

void stopCharge()
{
    //      if (pruio_pwm_setValue(io, PWM_OUT, freq, 0.0)) { // stop charging
    //                printf("failed stoping @PWM (%s)\n", io->Errr); break;}

    if(_pwm.isRunning())
        _pwm.stop();
}

void startDischarge()
{
    _outGPIO.setDirection(OUTPUT);
    _outGPIO.setValue(HIGH);
}

void stopDischarge()
{
    //if (pruio_gpio_setValue(io, GPO_OUT, 0)) { //     stop discharging
    //printf("failed discharging stop (%s)\n", io->Errr); break;}
    
    _outGPIO.setValue(LOW);
}


void cleanUp()
{
    stopCharge();
    stopDischarge();
    if( io ) pruio_destroy(io);
}

int initADC()
{
    if (pruio_adc_setStep(io,  9, 0, 0, 0, 0)){ //         step 9, AIN-0 -> voltage
        printf("ADC step 9 init failed: (%s)\n", io->Errr); return 0;}
    if (pruio_adc_setStep(io, 10, 1, 0, 0, 1)){ //        step 10, AIN-1 -> current
        printf("ADC step 10 init failed: (%s)\n", io->Errr); return 0;}

    // initialize global parameters
    samp =  (io->ESize >> 1) / NoStep;  //!< The number of samples, use all ERam
    maxInd = samp * NoStep;  //!< The maximum index in the ring buffer.

    if (pruio_config(io, samp, mask, tmr, 4)){ //       configure driver
    printf("config failed (%s)\n", io->Errr); return 0;}

    if (pruio_rb_start(io)){ //                                start ADC
    printf("rb_start failed (%s)\n", io->Errr); return 0;}

    return 1;
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

    io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0); //! create new driver
    if (io->Errr){
        printf("constructor failed (%s)\n", io->Errr); return 1;}

    if( !initADC() ) { cleanUp(); return 1; }



    uint32 a, e; //!< index of start and end of related ring buffer area
    uint32 n;    //!< tests counter
    uint16 volt_1 = 1800; //!< stop charging (= Volt * 65520 / 1.8)
    uint16 volt_2 = 10; //!< stop discharging

    uint16 v_max = 0;
    uint16 v_val = 0;

    _outGPIO.setDirection(OUTPUT);
    startDischarge();
    usleep( 1000000 );
    stopDischarge();

    //pwm_duty = 5;
    startCharge();

    for(n = 0; n < 100; n++)
    {
        v_max = 0;

        do { //                               wait for end of charge cycle
            a = io->DRam[0] & 0xfffe; // only even indexes from AIN0
            v_val = io->Adc->Value[a];
            if( v_val > v_max)
            {
                v_max = v_val;
//                printf("%d\n",v_val);
            }
        } while(v_val < volt_1);

        printf("V_max: %d\n",v_val);

        stopCharge();
        startDischarge();

        do { //                            wait for end of discharge cycle
            e = io->DRam[0] & 0xfffe; // only even indexes from AIN0
        } while(io->Adc->Value[e] > volt_2);

        stopDischarge();


        //                     compute buffer (in case of overflow: e < a)
        float dPow = 0, inJoules = 0, outJoules = 0;
        uint32 c;
        for(c = (e > a ? e - a : maxInd - a + e); c > 0; c--)
        {
            float Volt = io->Adc->Value[a];     // scale and offset here
            float Curr = io->Adc->Value[a + 1]; // scale and offset here

            dPow = Curr * Volt * tmr * 1e-9;
            if ( dPow >= 0 ) inJoules += dPow;
            else            outJoules += dPow;

            a += io->Adc->ChAz;
            if (a >= maxInd) a -= maxInd;
        };

        printf("Joules in : %f\n",inJoules);
        printf("Joules out: %f\n",outJoules);

        pwm_freq += 100; //                                   set new frequency
        usleep( 1000000 );
        startCharge();
    }

    cleanUp();
    return 0;
}
