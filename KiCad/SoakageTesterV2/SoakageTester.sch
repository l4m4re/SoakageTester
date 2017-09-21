EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Texas_Instruments
LIBS:LamaresLib
LIBS:Beagle
LIBS:CapTester-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 19
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4500 1550 1300 800 
U 587E8D2A
F0 "Input Amplifier" 60
F1 "InputAmp.sch" 60
F2 "Vref" I L 4500 1750 60 
F3 "I_sense" I L 4500 2000 60 
F4 "Is_x_5" O R 5800 1850 60 
F5 "V_cap" I L 4500 2200 60 
F6 "V_cap_div_100" O R 5800 2200 60 
$EndSheet
$Sheet
S 2700 1700 1100 750 
U 587E487B
F0 "Power Electronics" 60
F1 "PowerElectronics.sch" 60
F2 "Charge" I L 2700 2250 60 
F3 "I_sense" O R 3800 2000 60 
F4 "Discharge" I L 2700 2000 60 
F5 "Bedini" I L 2700 1800 60 
F6 "V_cap" O R 3800 2200 60 
$EndSheet
Text Notes 600  1200 0    60   ~ 0
TODO: \n* Power supply from bus\n* Voltage dividers on filter outputs and adjustment of amplification\n* Use 12V power supply for everything except the Beagle\n\nAlso measure current going into coil / TOR\n- Add inductance / capacitance measuring circuit.
Text Notes 6900 5950 0    60   ~ 0
Add may be:\n\nSupport for Arduino as main board\n\nLC Meter:\nhttps://sites.google.com/site/vk3bhr/home/lcm1\nhttps://sites.google.com/site/vk3bhr/home/index2-html\n\nCHPS\nTesla Switch\nLawton (Puharich / Meyer)\nArduino Shield support\nXO Scope / sound scope\nLogic analyser\nSignal Generator\nHigh speed ADC
$Sheet
S 4500 3100 1950 850 
U 59107483
F0 "Beagle" 60
F1 "Beagle.sch" 60
F2 "Charge" O L 4500 3350 60 
F3 "Discharge" O L 4500 3500 60 
F4 "Bedini" O L 4500 3650 60 
F5 "V_ref" O L 4500 3200 60 
F6 "AIN0" I R 6450 3200 60 
F7 "AIN2" I R 6450 3400 60 
F8 "AIN1" I R 6450 3300 60 
F9 "AIN3" I R 6450 3500 60 
$EndSheet
$Sheet
S 6350 2200 1350 350 
U 5913B953
F0 "Voltage_Filter" 60
F1 "LowPass_50kHz.sch" 60
F2 "V_in" I L 6350 2300 60 
F3 "V_in_LP_div_6" O R 7700 2300 60 
F4 "V_in_LP_x_25_div_6" O R 7700 2450 60 
$EndSheet
$Sheet
S 6350 1450 1350 400 
U 5915A94F
F0 "Current_Filter" 60
F1 "LowPass_50kHz.sch" 60
F2 "V_in" I L 6350 1550 60 
F3 "V_in_LP_div_6" O R 7700 1550 60 
F4 "V_in_LP_x_25_div_6" O R 7700 1750 60 
$EndSheet
Wire Wire Line
	2550 2250 2700 2250
Wire Wire Line
	2450 2000 2700 2000
Wire Wire Line
	3800 2000 4500 2000
Wire Wire Line
	3800 2200 4500 2200
Wire Wire Line
	2700 1800 2300 1800
Wire Wire Line
	4400 1750 4500 1750
Wire Wire Line
	5800 2200 6150 2200
Wire Wire Line
	6150 2200 6150 2300
Wire Wire Line
	5800 1850 5900 1850
Wire Wire Line
	5900 1850 5900 1550
Wire Wire Line
	4400 1750 4400 3200
Wire Wire Line
	1350 3200 4500 3200
Wire Wire Line
	2550 2250 2550 3350
Wire Wire Line
	2550 3350 4500 3350
Wire Wire Line
	2450 2000 2450 3500
Wire Wire Line
	2450 3500 4500 3500
Wire Wire Line
	2300 1800 2300 3650
Wire Wire Line
	2300 3650 4500 3650
Wire Wire Line
	8450 2300 8450 3200
Wire Wire Line
	8450 3200 6450 3200
Wire Wire Line
	8500 2450 8500 3400
Wire Wire Line
	8500 3400 6450 3400
Wire Wire Line
	6450 3300 8550 3300
Wire Wire Line
	8550 3300 8550 1550
Wire Wire Line
	6450 3500 8600 3500
Wire Wire Line
	8600 3500 8600 1750
Wire Wire Line
	8450 2300 7700 2300
Wire Wire Line
	8500 2450 7700 2450
Wire Wire Line
	8600 1750 7700 1750
Wire Wire Line
	8550 1550 7700 1550
Wire Wire Line
	6150 2300 6350 2300
Wire Wire Line
	5900 1550 6350 1550
$Sheet
S 1900 4850 1950 1100
U 592B33E6
F0 "experimental" 60
F1 "experimental.sch" 60
$EndSheet
$Sheet
S 1900 6400 1950 1000
U 592D275E
F0 "Analog Experimental" 60
F1 "AnalogExperimental.sch" 60
F2 "V_ref" I L 1900 6650 60 
$EndSheet
Wire Wire Line
	1900 6650 1350 6650
Wire Wire Line
	1350 6650 1350 3200
Connection ~ 4400 3200
$EndSCHEMATC
