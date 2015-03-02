//-----------------------------------------------------------------------------
// Settings.h
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

#ifndef _ADC_H
#define _ADC_H


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "defines.h" 

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
extern volatile uint16_t ADCCounter;
extern volatile uint16_t ADCLastIdxRead; // Last finished sample index
extern volatile  uint8_t ADCChannel;
extern volatile  int16_t ADCBuffer[ADCBUFFERSIZE+5][ADC_NR_CHANNELS];


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void initADC();
void startADCCycle();

// Hard-coded Callback from ADC ISR. Implemented in chargedischarge.cpp.
void ADCFinished(); 


//-----------------------------------------------------------------------------
// Inline Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// initialize ADC Channel
//-----------------------------------------------------------------------------
inline void initADCChannel()
{
    // The value of these bits selects which analog inputs are connected to
    // the ADC. If these bits are changed during a conversion, the change
    // will not go in effect until this conversion is complete (ADIF in
    // ADCSRA is set).

    // Clear MUX3..0 in ADMUX (0x7C) in preparation for setting the analog
    // input
    ADMUX &= B11110000;

    // Set MUX3..0 in ADMUX (0x7C) to read from AdcPin
    // Do not set above 15! You will overrun other parts of ADMUX. A full
    // list of possible inputs is available in Table 24-4 of the ATMega328
    // datasheet
    ADMUX |= ( ADCChannel & 0x07 );
}


inline void enableADC()
{
    // Enable ADC
    sbi(ADCSRA,ADEN);
}

inline void startADConv()
{
    initADCChannel();
    enableADC();
    // Start conversion
    sbi(ADCSRA,ADSC);
#if DEBUG == 1
    digitalWrite(12, !digitalRead(12));
#endif
}

inline void stopADC()
{
    // Disable ADC
    cbi(ADCSRA,ADEN);
}


#endif // _ADC_H
