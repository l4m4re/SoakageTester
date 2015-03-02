//-----------------------------------------------------------------------------
// ADC.cpp
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
// Includes
//-----------------------------------------------------------------------------

//#include "CapBatteryTest.h"
#include "ADC.h"
#include <MsTimer2.h>

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

volatile uint16_t ADCCounter;
volatile uint16_t ADCLastIdxRead;
volatile  uint8_t ADCChannel;
volatile  int16_t ADCBuffer[ADCBUFFERSIZE+5][ADC_NR_CHANNELS];



/*
// http://www.gammon.com.au/interrupts example
void loop ()
{
  // if last reading finished, process it
  if (ADCDone)
    {
    adcStarted = false;

    // do something with the reading, for example, print it
    Serial.println (adcReading);
    delay (500);

    ADCDone = false;
    }
    
  // if we aren't taking a reading, start a new one
  if (!adcStarted)
    {
    adcStarted = true;
    // start the conversion
    ADCSRA |= bit (ADSC) | bit (ADIE);
    }    
  
  // do other stuff here

}  // end of loop
*/




//-----------------------------------------------------------------------------
// ADC Conversion Complete Interrupt
//-----------------------------------------------------------------------------
// Based on: http://www.gammon.com.au/interrupts example
ISR(ADC_vect)
{
    // When ADCL is read, the ADC Data Register is not updated until ADCH
    // is read. Consequently, if the result is left adjusted and no more
    // than 8-bit precision is required, it is sufficient to read ADCH.
    // Otherwise, ADCL must be read first, then ADCH.
    //
    // We have to read ADCL first; doing so locks both ADCL
    // and ADCH until ADCH is read. Reading ADCL second would
    // cause the results of each conversion to be discarded,
    // as ADCL and ADCH would be locked when it completed.
    ADCBuffer[ADCCounter][ADCChannel-ADCFIRSTCHANNEL] = ADCL | (ADCH << 8);

#if DEBUG == 1
    digitalWrite(13, !digitalRead(13));
#endif

    if (++ADCChannel > ADCLASTCHANNEL )
    {  
	// We've done all channels

	// Disable ADC
	//cbi( ADCSRA, ADEN );
	stopADC();


        ADCLastIdxRead = ADCCounter;

	// Update counter for next set of samples
	if (++ADCCounter >= ADCBUFFERSIZE) ADCCounter = 0;

        ADCChannel = ADCFIRSTCHANNEL;
        
        ADCFinished();

	return;
    } //  else

    // Setup ADC to sample next channel. ADCChannel already updated.
    startADConv();
}
// end of ADC_vect


//-----------------------------------------------------------------------------
// Start sample cycle. Called by MsTimer2 Interrupt
//-----------------------------------------------------------------------------
void startADCCycle()
{    
    ADCChannel = ADCFIRSTCHANNEL;
    startADConv();
}

