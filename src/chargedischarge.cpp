//-----------------------------------------------------------------------------
// chargedischarge.cpp
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
#include "ADC.h"
#include <MsTimer2.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#define MAGIC     -1111.11

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

uint32_t          CDPauseTime; // Pause time in charge/discharge cycle in msec

volatile int      fullyChargedVal;
volatile int      fullyDischargedVal;

volatile bool     charging;
volatile bool     discharging;
volatile bool     start_charging;
volatile bool     start_discharging;

double            lastAmperage;
double            lastVoltage;

double            inJoules;
double            outJoules;

uint16_t          procIdx;

//-----------------------------------------------------------------------------
// Main routines
//-----------------------------------------------------------------------------


/*
http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/

Appologies for two posts in a row, but I have been reading and it seems
that if you set WGM13 and WGM12, then the value of ICR1 will trigger the
timer reset, rather than the OCR1A and OCR1B interrupts (which will be
called as normal when the timer reaches them). This behaviour is ideal
for my project, if it works. I hope this helps someone else 
*/



/*
http://www.gammon.com.au/interrupts

The code example below demonstrates reading the ADC converter (pin A0 in
this case) whilst doing something else at the same time.

Each ADC conversion takes around 104 uS, and since that would be 1664
clock cycles (something like 832 instructions) it would be useful to do
something (like process the previous reading) while you are doing it.

Once the reading has started you continue to execute the main loop,
checking to see if it completed in the ISR. Once it does you can process
it, print it, or whatever. 

Also consider putting a 0.1 uF capacitor between the AREF and GND pins
(adjacent to each other on the Uno board) to reduce noise in the analog
reference voltage.
*/


/*
Also see:
http://www.glennsweeney.com/tutorials/interrupt-driven-analog-conversion-with-an-atmega328p

The onboard ADC requires 13 clock cycles in order to process an analog
value. However, in order to get accurate results, the clock at the ADC
needs to be slower than the overall system clock. A prescaling constant,
by default 128, is used to divide the system clock before supplying it
to the ADC.

So, on an Arduino running at 16MHz (16,000KHz), the ADC clock is at
(16,000/128)KHz, or 125KHz. At 13 clock cycles, that's about 104us
(microseconds) to perform an ADC.

AL:
>>> print 1/104e-6
9615.38461538
>>> 


// Testing interrupt-based analog reading
// ATMega328p

// Note, many macro values are defined in <avr/io.h> and
// <avr/interrupts.h>, which are included automatically by
// the Arduino interface

// High when a value is ready to be read
volatile int readFlag;

// Value to store analog result
volatile int analogVal;


// Initialization
void setup(){
 
  // clear ADLAR in ADMUX (0x7C) to right-adjust the result
  // ADCL will contain lower 8 bits, ADCH upper 2 (in last two bits)
  ADMUX &= B11011111;
 
  // Set REFS1..0 in ADMUX (0x7C) to change reference voltage to the
  // proper source (01)
  ADMUX |= B01000000;
 
  // Clear MUX3..0 in ADMUX (0x7C) in preparation for setting the analog
  // input
  ADMUX &= B11110000;
 
  // Set MUX3..0 in ADMUX (0x7C) to read from AD8 (Internal temp)
  // Do not set above 15! You will overrun other parts of ADMUX. A full
  // list of possible inputs is available in Table 24-4 of the ATMega328
  // datasheet
  ADMUX |= 8;
  // ADMUX |= B00001000; // Binary equivalent
 
  // Set ADEN in ADCSRA (0x7A) to enable the ADC.
  // Note, this instruction takes 12 ADC clocks to execute
  ADCSRA |= B10000000;
 
  // Set ADATE in ADCSRA (0x7A) to enable auto-triggering.
  ADCSRA |= B00100000;
 
  // Clear ADTS2..0 in ADCSRB (0x7B) to set trigger mode to free
  // running.
  // This means that as soon as an ADC has finished, the next will be
  // immediately started.
  ADCSRB &= B11111000;
 
  // Set the Prescaler to 128 (16000KHz/128 = 125KHz)
  // Above 200KHz 10-bit results are not reliable.
  ADCSRA |= B00000111;
 
  // Set ADIE in ADCSRA (0x7A) to enable the ADC interrupt.
  // Without this, the internal interrupt will not trigger.
  ADCSRA |= B00001000;
 
  // Enable global interrupts
  // AVR macro included in <avr/interrupts.h>, which the Arduino IDE
  // supplies by default.
  sei();
 
  // Kick off the first ADC
  readFlag = 0;
  // Set ADSC in ADCSRA (0x7A) to start the ADC conversion
  ADCSRA |=B01000000;
}


// Processor loop
void loop(){

  // Check to see if the value has been updated
  if (readFlag == 1){
   
    // Perform whatever updating needed
   
    readFlag = 0;
  }
 
  // Whatever else you would normally have running in loop().
 
}


// Interrupt service routine for the ADC completion
ISR(ADC_vect){

  // Done reading
  readFlag = 1;
 
  // Must read low first
  analogVal = ADCL | (ADCH << 8);
 
  // Not needed because free-running mode is enabled.
  // Set ADSC in ADCSRA (0x7A) to start another ADC conversion
  // ADCSRA |= B01000000;
}
*/




/*  Use of millis() and rollover

    http://forum.arduino.cc/index.php?topic=122413

    if all your time calculations are done as:
    
        if  ((later_time - earlier_time ) >=duration ) {action}

    then the rollover does generally not come into play.

    Q: Are there instances where the rollover does come into play?
    A: When duration is >= the rollover period.  
       (Or if you use signed comparison, >= 1/2 the rollover period).
       
       
    https://www.baldengineer.com/arduino-how-do-you-reset-millis.html
    
    Avoiding rollover and checking how much time as passed is done in a single line:
	
      if ((unsigned long)(millis() - previousMillis) >= interval)

    That single line of code is all that is really needed, to avoid rollover! 
    
*/



/*
Pseudo code discharge:

Measure voltage1   -> set flag in ISR after charging and check in main loop.
Discharge
Measure voltage2   -> set flag in ISR after discharge and check in ML
Calculate Joules
TotalJoules += Joules
*/


void startSampling()
{
//TODO: print header
    procIdx        = ADCBUFFERSIZE + 1;
    ADCLastIdxRead = ADCBUFFERSIZE + 1;
    MsTimer2::start();
}

void stopSampling()
{
    MsTimer2::stop();  // stop sampling
//    procIdx        = ADCBUFFERSIZE + 1;
//    ADCLastIdxRead = ADCBUFFERSIZE + 1;
//TODO: print footer
}

inline void startCharging()
{
    charging = true;
    startPWM(); 
}

inline void stopCharging()
{
    charging = false;
    stopPWM(); 
}

inline void startDischarging()
{
    discharging = true;
    digitalWrite(dischargePin, HIGH);
}

inline void stopDischarging()
{
    discharging = false;
    digitalWrite(dischargePin, LOW);
}


void setFullyChargedVoltage( float voltage )
{
    // Convert the voltage to an analog reading for the input.  The
    // hardware contains a 1:20 voltage divider, which maps 0-100V to
    // 0-5V. This maps to an analog reading of 0-1023.

    // We take 100/1000 instead of 100/1023, so we get a max of 102.3V.

    fullyChargedVal = (voltage + 0.5)*10.0;
}


void setFullyDischargedVoltage( float voltage )
{
    // Convert the voltage to an analog reading for the input.  The
    // hardware contains a 1:20 voltage divider, which maps 0-100V to
    // 0-5V. This maps to an analog reading of 0-1023.

    // We take 100/1000 instead of 100/1023, so we get a max of 102.3V.

    fullyDischargedVal = (voltage + 0.5)*10.0;
}

//-----------------------------------------------------------------------------
// Hard-coded Callback from ADC ISR.
// Called once every time all channels have been sampled.
//-----------------------------------------------------------------------------
// The last input on ADC_VOLT_CHANNEL is stored in:
// ADCBuffer[ADCLastIdxRead][ADC_VOLT_CHANNEL]
#define LastVoltageValueRead ADCBuffer[ADCLastIdxRead][ADC_VOLT_CHANNEL-ADCFIRSTCHANNEL]
void ADCFinished()
{
    if( charging && (LastVoltageValueRead >= fullyChargedVal) ) 
	stopCharging();

    if( discharging && (LastVoltageValueRead <= fullyDischargedVal) ) 
	stopDischarging();
}
#undef LastVoltageValueRead


//-----------------------------------------------------------------------------
// Main routine controlling the charge-discharge cycle
// returns true when done
//-----------------------------------------------------------------------------
// Implemented using static coroutine 'scr' macros adapted from:
//    http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
//-----------------------------------------------------------------------------
bool chargeDischargeCycle()
{   
    // 'local' variables must be declared static, because routine
    // re-enters multiple times.
    static unsigned long pause_start_millis; // charge/discharge done timestamp

    scrBegin; 

        start_charging = true;
        //dshow( "set start charging" );


    scrReturn(false);

	// setup
	startSampling();
        //dshow( "start sampling" );

        pause_start_millis = millis();

    scrReturn(false);
 
        //dshow( "wait for CDPausetime to elapse" );

        // wait until resting period is done    
        if( (unsigned long)(millis() - pause_start_millis) < CDPauseTime ) 
            return false;

        startCharging();
        //dshow( "start charging" );

    scrReturn(false);

        //dshow( "wait until charging is done" );
	// wait until charging is done
	if( charging || start_charging ) return false;

        pause_start_millis = millis();

    scrReturn(false);
 
        // wait until resting period is done    
        //dshow( "wait until resting period is done" );
        //dprint((unsigned long)(millis() - pause_start_millis));
        if( (unsigned long)(millis() - pause_start_millis) < CDPauseTime ) 
            return false;

        //dshow( "set start discharging" );
        start_discharging = true;

    scrReturn(false);

        startDischarging();
        //dshow( "start discharging" );


    scrReturn(false);

	// wait until discharging is done.
        //dshow( "wait until discharging is done" );
	if( discharging || start_discharging ) return false;

        pause_start_millis = millis();

    scrReturn(false);
 
        // wait until resting period is done    
        //dshow( "wait until resting period 2 is done" );
        if( (unsigned long)(millis() - pause_start_millis) < CDPauseTime ) 
            return false;

//        dshow( "stop sampling" );
	stopSampling();
//        dshow( "stop sampling" );
 

    scrFinish(true);
}



//-----------------------------------------------------------------------------
// Transmit one sample(set) from the buffer trough serial
//-----------------------------------------------------------------------------
#define procIdxVoltage  (ADCBuffer[procIdx][ADC_VOLT_CHANNEL-ADCFIRSTCHANNEL])
#define procIdxAmperage (ADCBuffer[procIdx][ADC_AMP_CHANNEL-ADCFIRSTCHANNEL])
void processBuffer()
{
    static double  voltage    = 0; 
    static double  amperage   = 0; 
    static double  dPow       = 0; 
    static bool    isCharging = true;
   
    //dshow( "enter processBuffer" );
        
    if( start_charging )
    { 
        if( inJoules < 0)  inJoules  *= -1.0;
        if( outJoules < 0) outJoules *= -1.0;

#if DEBUG == 1
        
        Serial.println("----::----");
        
        dprint(runnr);
        dprint(testnr);
        
        dprint(PWMPeriod);
        dprint(PWMPulseWidth);
        dprint(CDPauseTime);
                 
        dprint(inJoules);
        dprint(outJoules);
        dprint(lastAmperage);
        dprint(lastVoltage);
        dprint(dPow);
        
 //       dprint(charging);
 //       dprint(discharging);
 //       dprint(isCharging);
        
#endif
        if( inJoules!=0.0 && outJoules!=0.0 )
        {
            // print results
            Serial.print(inJoules);
            Serial.print(" Joules in and ");
            Serial.print(outJoules);
            Serial.println(" Joules out.");
            Serial.print("Efficiency: ");
           
            static float efficiency;
            
            if( inJoules > 0 )  efficiency = 100.0*outJoules/inJoules;
            else                efficiency = 0.0;
               
            // sanity check
            //if( efficiency < 0 || efficiency > 1e9)
            //    efficiency = -1.0;
            
            
            Serial.print(efficiency);
            Serial.println("%");
    
            if( efficiency > max_eff || max_eff < 0 || max_eff > 50000.0 )
            {
                max_eff = efficiency;
                Serial.println("New MAX found....");
            }
       
            Serial.print("Best efficiency so far: ");
            Serial.print(max_eff);
            Serial.println("%");
        } 
        start_charging  = false;
        isCharging      = true;
               
        inJoules        = 0;
        lastAmperage    = 0;
        lastVoltage     = 0;
    } 
    else if( start_discharging )
    { 
        start_discharging = false;
        isCharging        = false;
        
        outJoules         = 0;
        lastAmperage      = 0;
        lastVoltage       = 0;
    }

    if( ADCLastIdxRead > ADCBUFFERSIZE )
    {
	// Sampling restarted. Wait until actual sample read.
        procIdx = ADCBUFFERSIZE + 1;
        return;
    }

    if( procIdx != ADCLastIdxRead &&  ADCLastIdxRead < ADCBUFFERSIZE)
    {  
        // Update index
	if( ++procIdx >= ADCBUFFERSIZE ) procIdx = 0;
               
        // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V)
        voltage = (procIdxVoltage)/10.0 ;  
        
        // Convert the analog reading (which goes from 0 - 1023) to an amperage
        amperage = ((procIdxAmperage - 512.0)*.02) - ampOffset;
        
        //if( charging && amperage<0.0 ) amperage = 0.0;
/*
        if(   
//              charging || 
              ( ((voltage - fullyDischargedVal) > 0.0) ) 
           )  // not noise 
        // TODO: consider what to measure and/or to monitor/adjust amperage meter
*/
        { 
        
              dPow = ( (amperage + lastAmperage) / 2 ) *
                     ( (voltage + lastVoltage)   / 2 ) * SAMPLEPERIOD * 1e-3;
        }
//        else  dPow = 0.0;


#if DEBUG == 2
        static unsigned long last_millis=millis();
        
        //if( (unsigned long)(millis() - last_millis) >= 500 )
        if( (unsigned long)(millis() - last_millis) >= 250 )
        {
            Serial.println("::::::::::::::::::::::::::::::::::");
          
            dprint(charging);
            dprint(discharging);
            dprint(isCharging);
 
            dprint(voltage);
            dprint(amperage);
            dprint(lastVoltage);
            dprint(lastAmperage);
            dprint(dPow);
            dprint(ampOffset);
 
 /*           
            dprint(ADCChannel);
            dprint(ADCCounter);
            dprint(ADCLastIdxRead);
            dprint(procIdx);
 */           
            last_millis=millis();
        }    
#endif



        
        // TODO: discharge time is measurement for energy :)
        //   ==> can *calculate* the current using discharge time.  :) :)
        
        // see comment further down
            
        
#if DEBUG == 2
        digitalWrite(11, !digitalRead(11));

        static unsigned long last_millis=millis();
        
        if( (unsigned long)(millis() - last_millis) >= 50 )
        {
            dprint(inJoules);
            dprint(outJoules);
            dprint(amperage);
            dprint(voltage);
            dprint(lastAmperage);
            dprint(lastVoltage);
            dprint(dPow);

            dprint(charging);
            dprint(discharging);
            dprint(isCharging);
            
            Serial.println("----::----");
            
            last_millis=millis();
            
        }
#else
//        Serial.write( (uint8_t *)ADCBuffer[procIdx][0],
//		      ADCNRCHANNELS * sizeof(uint16_t) );
#endif

        if ( isCharging ) inJoules  += dPow;   // TODO: should be fabs()??
        else              outJoules += dPow; 

        lastAmperage = amperage;
        lastVoltage  = voltage;
    }
    
    //dshow( "exit processBuffer" );

}


/* TODO:

We kunnen calibreren op de discharge tijd can de condensator. Als we immers bij een constant 
Voltage stoppen met laden, dan zowel de ingaande energie als de uitgaande energie berekend
kunnen worden aan de hand van de rise- en fall-tijden van de COT.

Op die manier kunnen we de theoretische karakteristieken van de condensator correleren / kalibreren
aan de hand van onze metingen.

We gaan met andere woorden ons theoretische model gebruiken om ons model te toetsen aan de meetbare 
werkelijkheid.

De metingen zijn in principe bruikbaar, maar we hebben nogal wat ruis op de lijn. De karakteristieken
van de lamp qua weerstand/temperatuur zijn onbekend. Die zullen we moeten beschrijven. 
Ff
De Led op de cap geeft een heart-beat. Dit geeft een visuele waarneming. Deze geeft een indicatie van
de STRESS is de condensator. 

Gevoelsmatig lijkt hij ergens iets in de buurt van 0.5 Hz juist te zijn.



*/

