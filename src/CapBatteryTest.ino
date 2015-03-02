//-----------------------------------------------------------------------------
// CapBatteryTest.ino
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

#if DEBUG == 1
#include "ADC.h"
#endif



//-----------------------------------------------------------------------------
// Includes for Libraries
//-----------------------------------------------------------------------------
// http://jamesreubenknowles.com/multiple-source-files-with-the-arduino-ide-1618
// 
// Library Warning
// Please note that there is a quirk in the Arduino IDE that can prevent
// libraries from being included in the compile. The IDE requires all
// libraries to be #include’d in the main (.ino) file. If you do not do
// this, the library will not be included, and you’ll get errors during
// compile. 
// 
// How It Works
// When compiling, the IDE copies all the files to a temporary directory.
// It scans the .ino file for libraries, and copies the library files to
// the temporary directory. Finally, it does the actual compile. If you
// #include a library in any of the tabbed files, but not in the .ino file,
// the library will not be available to the parser. The IDE only scans the
// .ino file for libraries.
//-----------------------------------------------------------------------------

#include <TimerOne.h>
#include <MsTimer2.h>

/*
Problem: while Cap under test (CUT) charges, the spike gets lower,
because the buffer cap can unly discharge down to the CUT voltage.
*/




//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
uint32_t testnr;
uint32_t runnr;
float    max_eff;
float    ampOffset;

//-----------------------------------------------------------------------------
// Main routines
//-----------------------------------------------------------------------------


float measure()
{

        // read the input on analog PIN 0
        int sensorValue = analogRead(A2) - 512;

        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
        float amperage = sensorValue*.02;
        // print out the value you read:
/*
        Serial.print("    Input: ");
        Serial.println(sensorValue);
*/
        Serial.print("    ");
        Serial.print(amperage);
        Serial.print("A ");

        // read the input on analog PIN 0
        sensorValue = analogRead(A1);

        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
        float voltage = sensorValue/10.0 ;  // Take 100/1000 instead of 1023, so we get a max of 102.3V.
        // print out the value you read:
        Serial.print(voltage);
        Serial.println("V");
        
        delay(100);
        
        if( voltage < 0.01 )  return amperage;
        
        return 0;
}



void setup (void) 
{ // Setup of the microcontroller
    initPins();
    initSerial();
    
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);

//    Serial.println("Test with 24.1V input on 10.000 uF/40V capacitor");
    Serial.println("Test with 30V input on big 30.000 uF/70V capacitor");

// discharge cap before starting    
    digitalWrite(dischargePin, HIGH);

    float amp = 0;
    int count = 0;
    float totalamp = 0;
    for(int idx=0; idx<50; idx++)
    {
        amp = measure();
        if( amp )
        {  
            count++;
            totalamp += amp;
        }
    }
        
    digitalWrite(dischargePin, LOW);


    ampOffset = totalamp / count;
    Serial.print("Amp Offset: ");
    Serial.print(ampOffset);
    Serial.println("A.");
    
    initPWM();
    initADC();
    
    // Activate interrupts
    sei();

    runnr = 0;
    max_eff = 0;
}



//-----------------------------------------------------------------------------
// Main routine controlling the test cycle
//-----------------------------------------------------------------------------
// Implemented using static coroutine 'scr' macros adapted from:
//    http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
//-----------------------------------------------------------------------------
void testCycle()
{   
    static int count;
  
    // 'local' variables must be declared static, because routine
    // re-enters multiple times.
//    static unsigned long charge_done_millis;
    
    scrBegin; 

//        dshow( "scrBegin" );
    
// around 128 
#define PERIOD_INIT     100   // 100 = 10 kHz
#define PERIOD_MAX      5000  // 5000 == 200 Hz

// around 50
//#define PULSEWDT_INIT     45
//#define PULSEWDT_INIT     50
#define PULSEWDT_INIT    (PWMPeriod*0.15) // min 15% duty``
#define PULSEWDT_MAX     (PWMPeriod*0.9)  // max 90% duty

#define CDPAUSE_INIT     20
//#define CDPAUSE_MAX      13

#define MULTIPLIER        1.25

	// setup
        PWMPeriod     = PERIOD_INIT;   // the PWM period in microseconds
        CDPauseTime   = CDPAUSE_INIT;  // Pause time in charge/discharge cycle in msec
        PWMPulseWidth = PULSEWDT_INIT; // PWM pulsewidth in microseconds, minimal 50
        
        // TODO: make interface for this and/or set these at logical place:
        setFullyChargedVoltage(18.0);
        setFullyDischargedVoltage(0.75);

        max_eff = 0;
        runnr++;
        testnr = 0;
        count  = 0;
      
        Serial.println("=============================");
        Serial.print("Startung run: ");
        Serial.println(runnr);       
        
    scrReturnV;
    
      myloop:
      
          testnr++;
                    
//        for( static int i=0; i<5; i++ )
            while( !chargeDischargeCycle() ) 
                 scrReturnV;


          dshow( "chargeDischarge cycle done" );



// TODO: further development. First get static right.
     
        if( count++ < 25 )                  goto myloop;   
        
        count = 0;     
#ifdef MULTIPLIER
        PWMPulseWidth     *= MULTIPLIER;
#else
        PWMPulseWidth     += 1;
#endif

        if( PWMPulseWidth <= PULSEWDT_MAX)  goto myloop;   

 
        PWMPulseWidth      = PULSEWDT_INIT;
        
#ifdef MULTIPLIER
        PWMPeriod         *= MULTIPLIER;
#else
        PWMPeriod         += 1;
#endif
        if( PWMPeriod     <= PERIOD_MAX )    goto myloop; 

/*
        PWMPulseWidth      = PULSEWDT_INIT;  
        PWMPeriod          = PERIOD_INIT;        
        //CDPauseTime       *= MULTIPLIER;
        CDPauseTime       += 1;
        if( CDPauseTime   <= CDPAUSE_MAX )   goto myloop; 
  
*/     
      
        Serial.print("Finished run: ");
        Serial.println(runnr);       
            
    scrFinishV;
}



void loop() 
{
  #if DEBUG == 3
    static unsigned long last_millis=millis();
    
    if( (unsigned long)(millis() - last_millis) >= 500 )
    {
        dprint(ADCCounter);
        dprint(ADCLastIdxRead);
        dprint(ADCChannel);
        //dprint(ADCDone);
        Serial.println( ADCSRA, BIN );
        Serial.println( ADCSRB, BIN );
        last_millis=millis();
    } 
  #endif

    processSerial();
    testCycle();
    processBuffer();
}
