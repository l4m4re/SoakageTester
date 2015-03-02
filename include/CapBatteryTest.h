//-----------------------------------------------------------------------------
// CapBatteryTest.h
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

#ifndef _CAPBATTERYTEST_H
#define _CAPBATTERYTEST_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "defines.h" 

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern uint32_t      PWMPeriod;     // the PWM period in microseconds
extern uint32_t      PWMPulseWidth; // PWM pulsewidth in microseconds

extern uint32_t      CDPauseTime;   // Pause time charge/discharge cycle in msec
extern volatile bool charging;
extern volatile bool discharging;

extern uint32_t      runnr;
extern uint32_t      testnr;
extern float         max_eff;

extern float         ampOffset;




//-----------------------------------------------------------------------------
// Global Function Prototypes
//-----------------------------------------------------------------------------

// inits.cpp
void initPins();

// settings.cpp
void setADCPrescaler( uint8_t prescaler );
void setVoltageReference( uint8_t reference );

// PWM.cpp
void initPWM();
bool startPWM(); // Starts PWM with PWMPeriod and PWMPulseWidth on pwmOutPin
void stopPWM();
void show();

// serial.cpp
void initSerial();
void processSerial();

//chargedischarge.cpp
void setFullyChargedVoltage( float voltage );
void setFullyDischargedVoltage( float voltage );
bool chargeDischargeCycle();
void processBuffer();

// interface.cpp
void error (void);
// Fills the given buffer with bufferSize chars from a Serial object
void fillBuffer( \
    char *buffer, \
    byte bufferSize, \
    HardwareSerial* serial = &Serial );
void printStatus(void);

// ADC.{h,cpp}
void initADC();


#endif _CAPBATTERYTEST_H

