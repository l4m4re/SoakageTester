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
Sheet 2 19
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
L R R_shunt1
U 1 1 5880234E
P 2450 2400
F 0 "R_shunt1" V 2530 2400 50  0000 C CNN
F 1 "10m" V 2450 2400 50  0000 C CNN
F 2 "Resistors_THT:R_Bare_Metal_Element_L21.3mm_W4.8mm_P20.30mm" V 2380 2400 50  0001 C CNN
F 3 "" H 2450 2400 50  0000 C CNN
	1    2450 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2100 2450 2250
Wire Wire Line
	2200 2100 2450 2100
Wire Wire Line
	2450 2550 2450 2850
Text HLabel 5400 2150 2    60   Output ~ 0
Is_x_5
Text HLabel 3500 2550 0    60   Input ~ 0
Vref
Wire Wire Line
	5400 2150 5100 2150
Text Notes 3700 1650 0    60   ~ 0
Make sure you don't input more than 1.8V to the analog input pins of a BeagleBone.
$Comp
L ina213 IC1
U 1 1 588022CA
P 4400 2350
F 0 "IC1" H 4400 2850 60  0000 C CNN
F 1 "ina213" H 4450 1600 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-363_SC-70-6_Handsoldering" H 4400 1350 60  0001 C CNN
F 3 "http://www.ti.com/product/ina213" H 4550 1150 60  0001 C CNN
	1    4400 2350
	1    0    0    -1  
$EndComp
Text HLabel 2200 2100 0    60   Input ~ 0
I_sense
Text Notes 7300 2600 2    60   ~ 0
Ina213: V_out = I_load * R_shunt * 50  + V_ref\n
$Comp
L R R1
U 1 1 59103B38
P 2850 2200
F 0 "R1" V 2930 2200 50  0000 C CNN
F 1 "180k" V 2850 2200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2780 2200 50  0001 C CNN
F 3 "" H 2850 2200 50  0001 C CNN
	1    2850 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 2350 3700 2350
Text GLabel 3600 2750 0    60   Input ~ 0
OPAMP_Vdd
Text GLabel 3650 2150 0    60   Input ~ 0
OPAMP_Vss
Wire Wire Line
	3650 2150 3700 2150
Wire Wire Line
	3600 2750 3700 2750
Wire Wire Line
	3000 2200 3000 2350
Text GLabel 2400 5200 0    60   Input ~ 0
OPAMP_Vdd
$Comp
L LM2902N U5
U 4 1 5914BE50
P 3900 4550
F 0 "U5" H 3900 4750 50  0000 L CNN
F 1 "LM2902N" H 3900 4350 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_Socket_LongPads" H 3850 4650 50  0001 C CNN
F 3 "" H 3950 4750 50  0001 C CNN
	4    3900 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5200 3800 4850
Wire Wire Line
	2400 5200 3800 5200
$Comp
L R R3
U 1 1 5914BE62
P 3150 4450
F 0 "R3" V 3230 4450 50  0000 C CNN
F 1 "10k" V 3150 4450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3080 4450 50  0001 C CNN
F 3 "" H 3150 4450 50  0001 C CNN
	1    3150 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 4450 3600 4450
$Comp
L R R6
U 1 1 5914BE6C
P 4000 4900
F 0 "R6" V 4080 4900 50  0000 C CNN
F 1 "10k" V 4000 4900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3930 4900 50  0001 C CNN
F 3 "" H 4000 4900 50  0001 C CNN
	1    4000 4900
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5914BE72
P 3150 4900
F 0 "R4" V 3230 4900 50  0000 C CNN
F 1 "1M" V 3150 4900 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3080 4900 50  0001 C CNN
F 3 "" H 3150 4900 50  0001 C CNN
	1    3150 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 4900 3850 4900
Wire Wire Line
	4150 4900 4400 4900
Wire Wire Line
	4400 4900 4400 4550
Wire Wire Line
	4200 4550 5050 4550
Wire Wire Line
	3000 4450 2800 4450
Text HLabel 5050 4550 2    60   Output ~ 0
V_cap_div_100
Connection ~ 4400 4550
Text Notes 2350 2450 2    60   ~ 0
TODO: edit shunt footprint
Text GLabel 6300 3300 0    60   Input ~ 0
OPAMP_Vss
Text GLabel 6300 3800 0    60   Input ~ 0
OPAMP_Vdd
$Comp
L C C1
U 1 1 5919C119
P 6550 3550
F 0 "C1" H 6575 3650 50  0000 L CNN
F 1 "100n" H 6575 3450 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 6588 3400 50  0001 C CNN
F 3 "" H 6550 3550 50  0001 C CNN
	1    6550 3550
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5919C1AE
P 6900 3550
F 0 "C2" H 6925 3650 50  0000 L CNN
F 1 "100n" H 6925 3450 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 6938 3400 50  0001 C CNN
F 3 "" H 6900 3550 50  0001 C CNN
	1    6900 3550
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5919C210
P 7200 3550
F 0 "C3" H 7225 3650 50  0000 L CNN
F 1 "100n" H 7225 3450 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 7238 3400 50  0001 C CNN
F 3 "" H 7200 3550 50  0001 C CNN
	1    7200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3300 7200 3400
Connection ~ 7200 3300
Wire Wire Line
	6900 3400 6900 3300
Connection ~ 6900 3300
Wire Wire Line
	6550 3400 6550 3300
Connection ~ 6550 3300
Wire Wire Line
	7200 3800 7200 3700
Connection ~ 7200 3800
Wire Wire Line
	6900 3700 6900 3800
Connection ~ 6900 3800
Wire Wire Line
	6550 3700 6550 3800
Connection ~ 6550 3800
Text Label 3200 2450 0    60   ~ 0
IC1_IN_NEG
Text Label 3200 2350 0    60   ~ 0
IC1_IN_POS
$Comp
L GNDPWR #PWR1
U 1 1 591E5516
P 2450 2850
F 0 "#PWR1" H 2450 2650 50  0001 C CNN
F 1 "GNDPWR" H 2450 2720 50  0000 C CNN
F 2 "" H 2450 2800 50  0001 C CNN
F 3 "" H 2450 2800 50  0001 C CNN
	1    2450 2850
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR3
U 1 1 591E57A2
P 2800 5000
F 0 "#PWR3" H 2800 4800 50  0001 C CNN
F 1 "GNDPWR" H 2800 4870 50  0000 C CNN
F 2 "" H 2800 4950 50  0001 C CNN
F 3 "" H 2800 4950 50  0001 C CNN
	1    2800 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 4900 2800 4900
Wire Wire Line
	2800 4900 2800 5000
Wire Wire Line
	2800 4450 2800 4600
$Comp
L GNDA_ADC #PWR2
U 1 1 591E784E
P 2800 4600
F 0 "#PWR2" H 2800 4350 50  0001 C CNN
F 1 "GNDA_ADC" H 2800 4450 50  0000 C CNN
F 2 "" H 2800 4600 60  0000 C CNN
F 3 "" H 2800 4600 60  0000 C CNN
	1    2800 4600
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 59103BAB
P 2850 2600
F 0 "R2" V 2930 2600 50  0000 C CNN
F 1 "180k" V 2850 2600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2780 2600 50  0001 C CNN
F 3 "" H 2850 2600 50  0001 C CNN
	1    2850 2600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3700 2450 3000 2450
Wire Wire Line
	3000 2450 3000 2600
Wire Wire Line
	3700 2550 3500 2550
Wire Wire Line
	2700 2600 2450 2600
Connection ~ 2450 2600
Wire Wire Line
	2700 2200 2450 2200
Connection ~ 2450 2200
$Comp
L R R5
U 1 1 5914BE5C
P 3450 4200
F 0 "R5" V 3530 4200 50  0000 C CNN
F 1 "1M" V 3450 4200 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3380 4200 50  0001 C CNN
F 3 "" H 3450 4200 50  0001 C CNN
	1    3450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 3950 3450 3950
Text HLabel 2750 3950 0    60   Input ~ 0
V_cap
Wire Wire Line
	2400 3700 3800 3700
Text GLabel 2400 3700 0    60   Input ~ 0
OPAMP_Vss
Wire Wire Line
	3800 3700 3800 4250
Wire Wire Line
	3450 3950 3450 4050
Wire Wire Line
	3450 4450 3450 4350
Connection ~ 3450 4450
Wire Wire Line
	3600 4650 3450 4650
Wire Wire Line
	3450 4650 3450 4900
Connection ~ 3450 4900
Wire Wire Line
	6300 3300 7800 3300
Wire Wire Line
	6300 3800 7800 3800
$Comp
L C C23
U 1 1 592E390F
P 7500 3550
F 0 "C23" H 7525 3650 50  0000 L CNN
F 1 "100n" H 7525 3450 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 7538 3400 50  0001 C CNN
F 3 "" H 7500 3550 50  0001 C CNN
	1    7500 3550
	1    0    0    -1  
$EndComp
$Comp
L C C24
U 1 1 592E3980
P 7800 3550
F 0 "C24" H 7825 3650 50  0000 L CNN
F 1 "100n" H 7825 3450 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 7838 3400 50  0001 C CNN
F 3 "" H 7800 3550 50  0001 C CNN
	1    7800 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3300 7500 3400
Wire Wire Line
	7500 3800 7500 3700
Wire Wire Line
	7800 3300 7800 3400
Connection ~ 7500 3300
Wire Wire Line
	7800 3800 7800 3700
Connection ~ 7500 3800
$EndSCHEMATC
