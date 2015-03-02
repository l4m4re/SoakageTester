//-----------------------------------------------------------------------------
// PWM.cpp
//-----------------------------------------------------------------------------
// Copyright 2016 Arend Lammertink
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
//    auint32_t with CapBatteryTest.  If not, see <http://www.gnu.org/licenses/>.
//
// Based on: "The Generating clock signal KHz script"
//           http://domoticx.com/arduino-library-timerone/
//
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <TimerOne.h>
#include "defines.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

//uint16_t prescale[] = {0,1,8,64,256,1024}; // the range of prescale values
uint32_t          PWMPeriod;     // the PWM period in microseconds
uint32_t          PWMPulseWidth; // PWM pulsewidth in microseconds

//-----------------------------------------------------------------------------
// Internal Globals
//-----------------------------------------------------------------------------
uint16_t          PWMDuty;       // duty as a range from 0 to 1024, 
                                 // 512 is 50% duty cycle
//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
bool setPulseWidth(uint32_t microseconds);


//-----------------------------------------------------------------------------
// Main functions
//-----------------------------------------------------------------------------


void initPWM()
{
//    PWMPeriod     = 1000;    // the PWM period in microseconds
//    PWMPulseWidth =  120;    // PWM pulsewidth in microseconds
    
    Timer1.initialize(PWMPeriod);        // initialize timer1
}



//-----------------------------------------------------------------------------
// Starts PWM with PWMPeriod and PWMPulseWidth. Returns false if
// pulsewidth out of range.
//-----------------------------------------------------------------------------
bool startPWM()
{
    // TCCR1A = 0;                 // clear control register A    // attempt to solve spurious spikes

    if (!setPulseWidth(PWMPulseWidth)) return false;

    Timer1.pwm(pwmOutPin, PWMDuty, PWMPeriod);

    return true;
}

//-----------------------------------------------------------------------------
// Stops PWM
//-----------------------------------------------------------------------------
void stopPWM()
{
    //Timer1.stop();  // TODO : check if this helps to get rid of the spurious spikes
    Timer1.disablePwm(pwmOutPin);
}



/*
    http://www.arduino.cc/en/Reference/Map

    map(value, fromLow, fromHigh, toLow, toHigh)

    Re-maps a number from one range to another. That is, a value of fromLow
    would get mapped to toLow, a value of fromHigh to toHigh, values
    in-between to values in-between, etc.

    Does not constrain values to within the range, because out-of-range
    values are sometimes intended and useful. 
*/

bool setPulseWidth(uint32_t microseconds)
{
  // uint16_t prescaleValue = prescale[Timer1.clockSelectBits];

  // calculate time per tick in ns
  // uint32_t    precision = (F_CPU / 128000) * prescaleValue;   
  // PWMPeriod = precision * ICR1 / 1000; // Period in microseconds

  if( microseconds < PWMPeriod)
  {
    PWMDuty = map(microseconds, 0,PWMPeriod, 0,1024);
    if( PWMDuty < 1)
      PWMDuty = 1;

    // RESOLUTION = 65536 for 16 bits timer 1
    if(microseconds > 0 && PWMDuty < RESOLUTION) 
    {
//       Timer1.pwm(pwmOutPin, PWMDuty);
       return true;
    }
  }
  return false;
}


void show()
{
   Serial.print("The PWMPeriod is ");
   Serial.println(PWMPeriod);
   Serial.print("PWMDuty cycle is ");
   // pwmRegister is ICR1A or ICR1B
   Serial.print( map( pwmRegister, 0,ICR1, 1,99));      
   Serial.println("%");
   Serial.println();
}
      
    
