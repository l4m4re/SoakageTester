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
LIBS:CapTester-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 8
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ina213 IC1
U 1 1 5880227E
P 5350 2450
F 0 "IC1" H 5350 2950 60  0000 C CNN
F 1 "ina213" H 5400 1700 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SC-70-6_Handsoldering" H 5350 1450 60  0001 C CNN
F 3 "http://www.ti.com/product/ina213" H 5500 1250 60  0001 C CNN
	1    5350 2450
	1    0    0    -1  
$EndComp
$Comp
L R R_shunt1
U 1 1 5880234E
P 3300 3300
F 0 "R_shunt1" V 3380 3300 50  0000 C CNN
F 1 "10m" V 3300 3300 50  0000 C CNN
F 2 "" V 3230 3300 50  0000 C CNN
F 3 "" H 3300 3300 50  0000 C CNN
	1    3300 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2450 3300 3150
Wire Wire Line
	3050 3000 4000 3000
Wire Wire Line
	3300 3450 3300 3650
Wire Wire Line
	3000 3650 3800 3650
Wire Wire Line
	4650 2450 3300 2450
Connection ~ 3300 3000
Wire Wire Line
	4650 2550 3800 2550
Wire Wire Line
	3800 2550 3800 3800
Connection ~ 3300 3650
Connection ~ 3800 3650
Text HLabel 6350 2250 2    60   Output ~ 0
Vout_50
Text HLabel 6350 3950 2    60   Output ~ 0
Vout_5
Text HLabel 3000 4350 0    60   Input ~ 0
Vref
Wire Wire Line
	3000 4350 4650 4350
Wire Wire Line
	4650 2650 3550 2650
Wire Wire Line
	3550 2650 3550 4350
Connection ~ 3550 4350
Wire Wire Line
	6350 3950 6050 3950
Wire Wire Line
	6350 2250 6050 2250
Text Notes 4650 3450 0    60   ~ 0
Make sure you don't input more than 1.8V to the analog input pins of a BeagleBone.
$Comp
L ina213 IC2
U 1 1 588022CA
P 5350 4150
F 0 "IC2" H 5350 4650 60  0000 C CNN
F 1 "ina213" H 5400 3400 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SC-70-6_Handsoldering" H 5350 3150 60  0001 C CNN
F 3 "http://www.ti.com/product/ina213" H 5500 2950 60  0001 C CNN
	1    5350 4150
	1    0    0    -1  
$EndComp
Text HLabel 3050 3000 0    60   Input ~ 0
I_sense
Text Notes 8250 4400 2    60   ~ 0
Ina213: V_out = I_load * R_shunt * 50  + V_ref\n
Text GLabel 4550 2250 0    60   Input ~ 0
+5V_BGL
Text GLabel 4550 2850 0    60   Input ~ 0
GND_BGL
Wire Wire Line
	4650 2250 4550 2250
Wire Wire Line
	4650 2850 4550 2850
Text GLabel 3000 3650 0    60   Input ~ 0
GND_PWR
$Comp
L R R4
U 1 1 59103B38
P 4000 3950
F 0 "R4" V 4080 3950 50  0000 C CNN
F 1 "180k" V 4000 3950 50  0000 C CNN
F 2 "" V 3930 3950 50  0001 C CNN
F 3 "" H 4000 3950 50  0001 C CNN
	1    4000 3950
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 59103BAB
P 3800 3950
F 0 "R3" V 3880 3950 50  0000 C CNN
F 1 "180k" V 3800 3950 50  0000 C CNN
F 2 "" V 3730 3950 50  0001 C CNN
F 3 "" H 3800 3950 50  0001 C CNN
	1    3800 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 4150 4650 4150
Text GLabel 4600 4550 0    60   Input ~ 0
GND_BGL
Text GLabel 4600 3950 0    60   Input ~ 0
+5V_BGL
Wire Wire Line
	4600 3950 4650 3950
Wire Wire Line
	4650 4550 4600 4550
Wire Wire Line
	4000 3000 4000 3800
Wire Wire Line
	4000 4100 4000 4150
Wire Wire Line
	4650 4250 3800 4250
Wire Wire Line
	3800 4250 3800 4100
$EndSCHEMATC
