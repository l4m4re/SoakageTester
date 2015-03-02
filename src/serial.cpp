//-----------------------------------------------------------------------------
// serial.cpp
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

#include "CapBatteryTest.h"
//#include "ADC.h"


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

char commandBuffer[COMBUFFERSIZE+1];


//-----------------------------------------------------------------------------
// Main routines
//-----------------------------------------------------------------------------


void initSerial()
{
    // Open serial port with a baud rate of BAUDRATE b/s
    Serial.begin(BAUDRATE);
    
  
    // Clear buffer
    memset( (void *)commandBuffer, 0, sizeof(commandBuffer) );
}

void processSerial()
{

// TODO: implement interface with laptop
/*  from Blockwave.ino
 static uint32_t val = 0;

  if ( Serial.available())
  {
    char ch = Serial.read();

    if(ch >= '0' && ch <= '9')              // is ch a number?
    {
       val = val * 10 + ch - '0';           // yes, accumulate the value
    }
    else if(ch == SET_PWMPeriod_HEADER)
    {
      PWMPeriod = val;
      Serial.print("Setting PWMPeriod to ");
      Serial.println(PWMPeriod);
      Timer1.setPWMPeriod(PWMPeriod);
      Timer1.setPwmPWMDuty(pwmOutPin, PWMDuty);  // don't change the PWMDuty cycle
      show();
      val = 0;
    }
    else if(ch == SET_FREQUENCY_HEADER)
    {
      if(val > 0)
      {
        Serial.print("Setting frequency to ");
        Serial.println(val);
        PWMPeriod = 1000000 / val;
        Timer1.setPWMPeriod(PWMPeriod);
        Timer1.setPwmPWMDuty(pwmOutPin, PWMDuty);  // don't change the PWMDuty cycle
      }
      show();
      val = 0;
    }
    else if(ch ==  SET_PULSE_WIDTH_HEADER)
    {
      if( setPulseWidth(val) ) {
         Serial.print("Setting Pulse width to ");
         Serial.println(val);
      }
      else
         Serial.println("Pulse width too uint32_t for current PWMPeriod");
      show();
      val = 0;
    }
    else if(ch == SET_PWMDuty_CYCLE_HEADER)
    {
     if( val >0 && val < 100)
     {
        Serial.print("Setting PWMDuty Cycle to ");
        Serial.println(val);
        PWMDuty = map(val,1,99, 1, ICR1);
        pwmRegister = PWMDuty;
        show();
     }
     val = 0;
    }
  }
*/
    if ( Serial.available() > 0 ) {
/*

Options to consider:

- Change sample freq : 100 Hz - 1 kHz
- Set EUT identifier
- Set V_input
- Set L
- Set C and/or Battery capacity of EUT
- Set duration cycle
- Set pulse frequency
- Set min/max charge/discharge voltage
- Set maximum amperage allowed

*/

        // Read the incoming byte
        char theChar = Serial.read();
            // Parse character
        switch (theChar) {
            case 's':            // 's' for starting ADC conversions

                // Clear buffer
 //               memset( (void *)ADCBuffer, 0, sizeof(ADCBuffer) );

 //               startADCCycle();
//                startAnalogComparator();
                break;
            case 'S':            // 'S' for stopping ADC conversions
//                stopAnalogComparator();
//                stopADC();
                break;

            case 'r':            // 'r' for new voltage reference setting
            case 'R': {
                // Wait for COMMANDDELAY ms to be sure that the Serial buffer is filled
                delay(COMMANDDELAY);

                fillBuffer( commandBuffer, COMBUFFERSIZE );

                // Convert buffer to integer
                uint8_t newR = atoi( commandBuffer );

                setVoltageReference(newR);
                }
                break;

            case 'e':            // 'e' for new trigger event setting
            case 'E': {
                // Wait for COMMANDDELAY ms to be sure that the Serial buffer is filled
                delay(COMMANDDELAY);

                fillBuffer( commandBuffer, COMBUFFERSIZE );

                // Convert buffer to integer
                uint8_t newE = atoi( commandBuffer );
/*
                if (newE == 4){
                    isContinuous = true;
                }
                else {
                    isContinuous = false;
                    triggerEvent = newE;
                    setTriggerEvent(newE);
                }
*/
                }
                break;

            case 'w':            // 'w' for new wait setting
            case 'W': {
                // Wait for COMMANDDELAY ms to be sure that the Serial buffer is filled
                delay(COMMANDDELAY);

                fillBuffer( commandBuffer, COMBUFFERSIZE );

                // Convert buffer to integer
                uint16_t newW = atoi( commandBuffer );

//                newWaitDuration = newW;
                }
                break;

            case 't':            // 't' for new threshold setting
            case 'T': {
                // Wait for COMMANDDELAY ms to be sure that the Serial buffer is filled
                delay(COMMANDDELAY);

                fillBuffer( commandBuffer, COMBUFFERSIZE );

                // Convert buffer to integer
                uint8_t newT = atoi( commandBuffer );
/*
                threshold = newT;
                analogWrite( thresholdPin, threshold );
*/
                }
                break;

            case 'd':            // 'd' for display status
            case 'D':
                printStatus();
                break;

            default:
                error();
        }
    }
}


