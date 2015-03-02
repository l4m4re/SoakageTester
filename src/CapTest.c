/** \file CapTest.c
\brief Example: libpruio version of Arends CapTest.cpp.

Licence: GPLv3

Copyright 2016 by Thomas{ doT ]Freiherr[ At ]gmx[ DoT }net

Compile by: `gcc -Wall -o CapTest CapTest.c -lpruio -lprussdrv`

*/

#include "unistd.h"
#include "time.h"
#include "stdio.h"
#include "pruio.h"
#include "pruio_pins.h"

#define PWM_OUT P9_42 // pin for PWM output
#define GPO_OUT P8_07 // pin for GPIO output

//! The main function.
int main(int argc, char **argv)
{
  pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0, 0, 0); //! create new driver
  if (io->Errr){
               printf("constructor failed (%s)\n", io->Errr); return 1;}

  do {
    if (pruio_adc_setStep(io,  9, 0, 0, 0, 0)){ //         step 9, AIN-0 -> voltage
             printf("ADC step 9 init failed: (%s)\n", io->Errr); break;}
    if (pruio_adc_setStep(io, 10, 1, 0, 0, 0)){ //        step 10, AIN-1 -> current
            printf("ADC step 10 init failed: (%s)\n", io->Errr); break;}

    if (pruio_gpio_setValue(io, GPO_OUT, 0)) { //         configure GPIO
             printf("setValue @GPO_OUT error (%s)\n", io->Errr); break;}

    float_t freq = 100; //                           The start frequency.
    if (pruio_pwm_setValue(io, PWM_OUT, freq, 0.5)) { //   configure PWM
      printf("failed setting output @PWM_OUT (%s)\n", io->Errr); break;}

    const uint32 tmr = 5000;     //!< The sampling rate in ns (5000 ns -> 200 kHz).
    const uint32 NoStep = 2;     //!< The number of active ADC steps (must match setStep calls and mask).
    const uint32 mask = 3 << 9;  //!< The active steps bitmaks (9 and 10).
    const uint32 samp = (io->ESize >> 1) / NoStep;  //!< The number of samples, use all ERam
    const uint32 maxInd = samp * NoStep;  //!< The maximum index in the ring buffer.

    if (pruio_config(io, samp, mask, tmr, 4)){ //       configure driver
                       printf("config failed (%s)\n", io->Errr); break;}

    if (pruio_rb_start(io)){ //                                start ADC
                     printf("rb_start failed (%s)\n", io->Errr); break;}

    uint32 a, e; //!< index of start and end of related ring buffer area
    uint32 n;    //!< tests counter
    uint16 volt_1 = 12345; //!< stop charging (= Volt * 65520 / 1.8)
    uint16 volt_2 = 11111; //!< stop discharging
    for(n = 0; n < 10; n++){
      do { //                               wait for end of charge cycle
        a = io->DRam[0] & 0xfffe; // only even indexes from AIN0
      } while(io->Adc->Value[a] < volt_1);

      if (pruio_pwm_setValue(io, PWM_OUT, freq, 0.0)) { // stop charging
                 printf("failed stoping @PWM (%s)\n", io->Errr); break;}
      if (pruio_gpio_setValue(io, GPO_OUT, 1)) { //      start discharge
            printf("failed discharging start (%s)\n", io->Errr); break;}

      do { //                            wait for end of discharge cycle
        e = io->DRam[0] & 0xfffe; // only even indexes from AIN0
      } while(io->Adc->Value[e] > volt_2);

      if (pruio_gpio_setValue(io, GPO_OUT, 0)) { //     stop discharging
             printf("failed discharging stop (%s)\n", io->Errr); break;}

      //                     compute buffer (in case of overflow: e < a)
      float dPow, inJoules = 0, outJoules = 0;
      uint32 c;
      for(c = (e > a ? e - a : maxInd - a + e); c > 0; c--){
        float Volt = io->Adc->Value[a];     // scale and offset here
        float Curr = io->Adc->Value[a + 1]; // scale and offset here

        dPow = Curr * Volt * tmr * 1e-9;
        if ( dPow >= 0 ) inJoules += dPow;
        else            outJoules += dPow;

        a += io->Adc->ChAz;
        if (a >= maxInd) a -= maxInd;
      };

      freq += 10; //                                   set new frequency
      if (pruio_pwm_setValue(io, PWM_OUT, freq, 0.5)) { //     start PWM
           printf("failed changing @PWM freq (%s)\n", io->Errr); break;}
    }
  } while(0);
  pruio_destroy(io);
  return 0;
}
