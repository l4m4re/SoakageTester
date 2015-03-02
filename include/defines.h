//-----------------------------------------------------------------------------
// defines.h
//-----------------------------------------------------------------------------
// Copyright 2015 Marvin Sinister, 2016 Arend Lammertink
//
// This file is part of CapBatteryTest.
//
//    CapBatteryTest is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    CapBatteryTest is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with CapBatteryTest.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------
// Multi-include protection
//-----------------------------------------------------------------------------

#ifndef _DEFINES_H
#define _DEFINES_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <Arduino.h>

//-----------------------------------------------------------------------------
// Defines and Typedefs
//-----------------------------------------------------------------------------

#define DEBUG            1


//-----------------------------------------------------------------------------
// The Arduino has 3 Timers and 6 PWM output pins. The relation between
// timers and PWM outputs is:
// 
// Pins 5 and 6:  controlled by timer0
// Pins 9 and 10: controlled by timer1
// Pins 11 and 3: controlled by timer2
//-----------------------------------------------------------------------------
#define pwmRegister  OCR1A    // the logical pin, can be set to OCR1B
#define pwmOutPin        9    // the physical pin

#define dischargePin     8    // controls discharging of the EUT

#define errorPin        13

#define BAUDRATE    115200    // Baud rate of UART in bps
#define COMMANDDELAY     2    // ms to wait for the filling of Serial buffer
#define COMBUFFERSIZE    4    // Size of buffer for incoming numbers

#define ADCBUFFERSIZE    6
#define ADCFIRSTCHANNEL  1
#define ADCLASTCHANNEL   2
#define ADC_NR_CHANNELS  2
#define ADC_VOLT_CHANNEL 1
#define ADC_AMP_CHANNEL  2

#define SAMPLEPERIOD     1    // In millisecs. 4 msec = 250 Hz.


//-----------------------------------------------------------------------------
// Debug helpers
//-----------------------------------------------------------------------------
#if DEBUG == 1
    #define dprint(expression) Serial.print(F("# ")); Serial.print( F(#expression) ); Serial.print( F(": ") ); Serial.println( expression )
    #define dshow(expression) Serial.println( expression )
#else
    #define dprint(expression) 
    #define dshow(expression)
#endif

//-----------------------------------------------------------------------------
// Defines for setting and clearing register bits
//-----------------------------------------------------------------------------
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


//-----------------------------------------------------------------------------
// `scr' macros for static coroutines.
// Adapted from:
//   http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
//-----------------------------------------------------------------------------
#define scrBegin         static int scrLine = 0; switch(scrLine) { case 0:;
//
//Original:
//
// #define scrFinish(z)     } return (z)
// #define scrFinishV       } return
//
//Adapted to re-initialize state variable for next round:
#define scrFinish(z)     } scrLine = 0; return (z)
#define scrFinishV       } scrLine = 0; return

#define scrFinishOT(z)   } return (z)
#define scrFinishOTV     } return


//
#define scrReturn(z)     \
        do {\
            scrLine=__LINE__;\
            return (z); case __LINE__:;\
        } while (0)
//
#define scrReturnV       \
        do {\
            scrLine=__LINE__;\
            return; case __LINE__:;\
        } while (0)




#endif // _DEFINES_H

