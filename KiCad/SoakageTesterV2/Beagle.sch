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
Sheet 7 19
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1100 3350 0    60   Output ~ 0
Charge
Text HLabel 1100 3450 0    60   Output ~ 0
Discharge
Text HLabel 4150 2950 2    60   Output ~ 0
Bedini
$Comp
L GNDD #PWR25
U 1 1 591451AA
P 2700 4750
F 0 "#PWR25" H 2700 4500 50  0001 C CNN
F 1 "GNDD" H 2700 4600 50  0000 C CNN
F 2 "" H 2700 4750 60  0000 C CNN
F 3 "" H 2700 4750 60  0000 C CNN
	1    2700 4750
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR16
U 1 1 591451C1
P 1200 2350
F 0 "#PWR16" H 1200 2100 50  0001 C CNN
F 1 "GNDD" H 1200 2200 50  0000 C CNN
F 2 "" H 1200 2350 60  0000 C CNN
F 3 "" H 1200 2350 60  0000 C CNN
	1    1200 2350
	0    1    1    0   
$EndComp
$Comp
L GNDD #PWR27
U 1 1 591451C7
P 5150 2250
F 0 "#PWR27" H 5150 2000 50  0001 C CNN
F 1 "GNDD" H 5150 2100 50  0000 C CNN
F 2 "" H 5150 2250 60  0000 C CNN
F 3 "" H 5150 2250 60  0000 C CNN
	1    5150 2250
	-1   0    0    1   
$EndComp
$Comp
L GNDD #PWR35
U 1 1 591451CD
P 10900 1400
F 0 "#PWR35" H 10900 1150 50  0001 C CNN
F 1 "GNDD" H 10900 1250 50  0000 C CNN
F 2 "" H 10900 1400 60  0000 C CNN
F 3 "" H 10900 1400 60  0000 C CNN
	1    10900 1400
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR22
U 1 1 591451E5
P 2300 2150
F 0 "#PWR22" H 2300 2000 50  0001 C CNN
F 1 "+3V3" H 2300 2290 50  0000 C CNN
F 2 "" H 2300 2150 60  0000 C CNN
F 3 "" H 2300 2150 60  0000 C CNN
	1    2300 2150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR21
U 1 1 591451EB
P 2100 2150
F 0 "#PWR21" H 2100 2000 50  0001 C CNN
F 1 "+5V" H 2100 2290 50  0000 C CNN
F 2 "" H 2100 2150 60  0000 C CNN
F 3 "" H 2100 2150 60  0000 C CNN
	1    2100 2150
	1    0    0    -1  
$EndComp
$Comp
L SYS_5V #PWR20
U 1 1 59145201
P 1850 2150
F 0 "#PWR20" H 1850 2000 50  0001 C CNN
F 1 "SYS_5V" H 1850 2290 50  0000 C CNN
F 2 "" H 1850 2150 60  0000 C CNN
F 3 "" H 1850 2150 60  0000 C CNN
	1    1850 2150
	1    0    0    -1  
$EndComp
$Comp
L GNDA_ADC #PWR26
U 1 1 5914520F
P 4850 3950
F 0 "#PWR26" H 4850 3700 50  0001 C CNN
F 1 "GNDA_ADC" H 4850 3800 50  0000 C CNN
F 2 "" H 4850 3950 60  0000 C CNN
F 3 "" H 4850 3950 60  0000 C CNN
	1    4850 3950
	1    0    0    -1  
$EndComp
$Comp
L BeagleBone_Black_Header P8
U 1 1 59145221
P 6000 3450
F 0 "P8" H 6000 4650 50  0000 C CNN
F 1 "BeagleBone_Black_Header" V 6000 3450 50  0000 C CNN
F 2 "Socket_BeagleBone_Black:Socket_BeagleBone_Black" H 6000 2600 60  0001 C CNN
F 3 "" H 6000 2600 60  0000 C CNN
	1    6000 3450
	1    0    0    -1  
$EndComp
Text Notes 2000 1900 0    60   ~ 0
+5V is raw 5V, can be used to power the beagle\nSYS_5V is output from on-board regulator\n
Text HLabel 4550 6750 2    60   Output ~ 0
V_ref
Text GLabel 1650 6300 0    60   Input ~ 0
OPAMP_Vss
Text GLabel 1650 7250 0    60   Input ~ 0
OPAMP_Vdd
$Comp
L LM2902N U6
U 4 1 59152211
P 3200 6750
F 0 "U6" H 3200 6950 50  0000 L CNN
F 1 "LM2902N" H 3200 6550 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_Socket_LongPads" H 3150 6850 50  0001 C CNN
F 3 "" H 3250 6950 50  0001 C CNN
	4    3200 6750
	1    0    0    -1  
$EndComp
$Comp
L R R21
U 1 1 59152218
P 3300 7150
F 0 "R21" V 3380 7150 50  0000 C CNN
F 1 "20k" V 3300 7150 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3230 7150 50  0001 C CNN
F 3 "" H 3300 7150 50  0001 C CNN
	1    3300 7150
	0    1    1    0   
$EndComp
$Comp
L R R20
U 1 1 5915221F
P 2550 6850
F 0 "R20" V 2630 6850 50  0000 C CNN
F 1 "10k" V 2550 6850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2480 6850 50  0001 C CNN
F 3 "" H 2550 6850 50  0001 C CNN
	1    2550 6850
	0    -1   -1   0   
$EndComp
Text Notes 650  5300 0    60   ~ 0
The Beaglebone provides a handy 1.8 Volt reference signal on pin 32  (on P9 header). \nAlways use pin 32 as your reference rail when working with analog inputs.\nSimilarly, you should use pin 34 (on P9 header) as your reference ground on your analog input circuits.\n
Text Notes 1100 6000 0    60   ~ 0
Amplify Beagle ref voltage to 5.4V for use as reference voltage. \nThe reference voltage used depends on the attenuation chosen for the \nvoltage dividers going to the analog inputs. For an attenuation of 6, the \nreference voltage should be 6 * 0.9 = 5.4 V.  The full scale maxium output\nvoltage for the opamps then becomes 6 * 1.8 = 10.8 V, which is slightly above\nthe maximum ouput voltage of the LM2902 (@ 12V supply) of 10.5 V.\n
Text HLabel 1100 4250 0    60   Input ~ 0
AIN0
Text HLabel 1100 4150 0    60   Input ~ 0
AIN2
Text HLabel 4200 4250 2    60   Input ~ 0
AIN1
Text HLabel 4200 4150 2    60   Input ~ 0
AIN3
$Comp
L +5V #PWR15
U 1 1 59167FBA
P 1100 1550
F 0 "#PWR15" H 1100 1400 50  0001 C CNN
F 1 "+5V" H 1100 1690 50  0000 C CNN
F 2 "" H 1100 1550 60  0000 C CNN
F 3 "" H 1100 1550 60  0000 C CNN
	1    1100 1550
	1    0    0    -1  
$EndComp
Text Label 2400 3950 2    60   ~ 0
AIN4
Text Label 2400 4050 2    60   ~ 0
AIN6
Text Label 2400 4150 2    60   ~ 0
AIN2
Text Label 2400 4250 2    60   ~ 0
AIN0
Text Label 3400 3850 2    60   ~ 0
VDD_ADC
Text Label 3400 3950 2    60   ~ 0
GND_ADC
Text Label 3200 4050 2    60   ~ 0
AIN5
Text Label 3200 4150 2    60   ~ 0
AIN3
Text Label 3200 4250 2    60   ~ 0
AIN1
Text Label 3300 4350 2    60   ~ 0
GPIO_7
Text Label 2450 4350 2    60   ~ 0
GPIO_20
$Comp
L C96ABC J8
U 1 1 5916550F
P 5850 800
F 0 "J8" H 5850 5700 50  0000 C CNN
F 1 "C96ABC" V 6100 800 50  0000 C CNN
F 2 "Connectors:C96ABCMD" H 5850 800 50  0001 C CNN
F 3 "" H 5850 800 50  0001 C CNN
	1    5850 800 
	0    -1   -1   0   
$EndComp
Text Notes 4500 7600 0    60   ~ 0
P8 pins 11-21 are used by eMMC, except pin 18.  \nOn a BBB, P8 pins 27-46 are used by HDMI. \n\nOn the BBG UART2 is used for the on-board I2C(?) interface,  \nwhich uses pin P9_22.\n\nPWMs using BoneScript works OOTB with pins: P8_13, P9_14, P9_21, P9_42
$Comp
L CONN_01X23 J10
U 1 1 59182C97
P 6700 3450
F 0 "J10" H 6700 4650 50  0000 C CNN
F 1 "CONN_01X23" V 6800 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x23_Pitch2.54mm" H 6700 3450 50  0001 C CNN
F 3 "" H 6700 3450 50  0001 C CNN
	1    6700 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X23 J9
U 1 1 59183339
P 5300 3450
F 0 "J9" H 5300 4650 50  0000 C CNN
F 1 "CONN_01X23" V 5400 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x23_Pitch2.54mm" H 5300 3450 50  0001 C CNN
F 3 "" H 5300 3450 50  0001 C CNN
	1    5300 3450
	-1   0    0    1   
$EndComp
Text Label 3000 4450 0    60   ~ 0
GNDD
$Comp
L CONN_01X23 J6
U 1 1 59185EBC
P 1500 3450
F 0 "J6" H 1500 4650 50  0000 C CNN
F 1 "CONN_01X23" V 1600 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x23_Pitch2.54mm" H 1500 3450 50  0001 C CNN
F 3 "" H 1500 3450 50  0001 C CNN
	1    1500 3450
	-1   0    0    1   
$EndComp
$Comp
L -5V #PWR17
U 1 1 591FCD2E
P 1700 1550
F 0 "#PWR17" H 1700 1650 50  0001 C CNN
F 1 "-5V" H 1700 1700 50  0000 C CNN
F 2 "" H 1700 1550 50  0001 C CNN
F 3 "" H 1700 1550 50  0001 C CNN
	1    1700 1550
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR33
U 1 1 591FD8A6
P 9850 1550
F 0 "#PWR33" H 9850 1400 50  0001 C CNN
F 1 "+12V" H 9850 1690 50  0000 C CNN
F 2 "" H 9850 1550 50  0001 C CNN
F 3 "" H 9850 1550 50  0001 C CNN
	1    9850 1550
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR32
U 1 1 591FDBD3
P 9250 1550
F 0 "#PWR32" H 9250 1650 50  0001 C CNN
F 1 "-12V" H 9250 1700 50  0000 C CNN
F 2 "" H 9250 1550 50  0001 C CNN
F 3 "" H 9250 1550 50  0001 C CNN
	1    9250 1550
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG4
U 1 1 5920202C
P 1100 1800
F 0 "#FLG4" H 1100 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 1950 50  0000 C CNN
F 2 "" H 1100 1800 50  0001 C CNN
F 3 "" H 1100 1800 50  0001 C CNN
	1    1100 1800
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG6
U 1 1 59202062
P 1700 1800
F 0 "#FLG6" H 1700 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 1700 1950 50  0000 C CNN
F 2 "" H 1700 1800 50  0001 C CNN
F 3 "" H 1700 1800 50  0001 C CNN
	1    1700 1800
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG10
U 1 1 59202A5D
P 9250 1800
F 0 "#FLG10" H 9250 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 9250 1950 50  0000 C CNN
F 2 "" H 9250 1800 50  0001 C CNN
F 3 "" H 9250 1800 50  0001 C CNN
	1    9250 1800
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG11
U 1 1 59202D80
P 9850 1800
F 0 "#FLG11" H 9850 1875 50  0001 C CNN
F 1 "PWR_FLAG" H 9850 1950 50  0000 C CNN
F 2 "" H 9850 1800 50  0001 C CNN
F 3 "" H 9850 1800 50  0001 C CNN
	1    9850 1800
	1    0    0    -1  
$EndComp
$Comp
L BeagleBone_Black_Header P9
U 1 1 5920384B
P 2700 3450
F 0 "P9" H 2700 4650 50  0000 C CNN
F 1 "BeagleBone_Black_Header" V 2700 3450 50  0000 C CNN
F 2 "Socket_BeagleBone_Black:Socket_BeagleBone_Black" H 2700 2600 60  0001 C CNN
F 3 "" H 2700 2600 60  0000 C CNN
	1    2700 3450
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG12
U 1 1 59203C89
P 10900 1250
F 0 "#FLG12" H 10900 1325 50  0001 C CNN
F 1 "PWR_FLAG" H 10900 1400 50  0000 C CNN
F 2 "" H 10900 1250 50  0001 C CNN
F 3 "" H 10900 1250 50  0001 C CNN
	1    10900 1250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG5
U 1 1 59203E34
P 1600 2250
F 0 "#FLG5" H 1600 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 2400 50  0000 C CNN
F 2 "" H 1600 2250 50  0001 C CNN
F 3 "" H 1600 2250 50  0001 C CNN
	1    1600 2250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG7
U 1 1 59203F2D
P 2550 2250
F 0 "#FLG7" H 2550 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 2550 2400 50  0000 C CNN
F 2 "" H 2550 2250 50  0001 C CNN
F 3 "" H 2550 2250 50  0001 C CNN
	1    2550 2250
	1    0    0    -1  
$EndComp
$Comp
L -12V #PWR19
U 1 1 59206275
P 1800 7200
F 0 "#PWR19" H 1800 7300 50  0001 C CNN
F 1 "-12V" H 1800 7350 50  0000 C CNN
F 2 "" H 1800 7200 50  0001 C CNN
F 3 "" H 1800 7200 50  0001 C CNN
	1    1800 7200
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR18
U 1 1 592064E0
P 1800 6250
F 0 "#PWR18" H 1800 6100 50  0001 C CNN
F 1 "+12V" H 1800 6390 50  0000 C CNN
F 2 "" H 1800 6250 50  0001 C CNN
F 3 "" H 1800 6250 50  0001 C CNN
	1    1800 6250
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG9
U 1 1 59206BF3
P 4450 3850
F 0 "#FLG9" H 4450 3925 50  0001 C CNN
F 1 "PWR_FLAG" H 4450 4000 50  0000 C CNN
F 2 "" H 4450 3850 50  0001 C CNN
F 3 "" H 4450 3850 50  0001 C CNN
	1    4450 3850
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG8
U 1 1 59206C22
P 4200 3950
F 0 "#FLG8" H 4200 4025 50  0001 C CNN
F 1 "PWR_FLAG" H 4200 4100 50  0000 C CNN
F 2 "" H 4200 3950 50  0001 C CNN
F 3 "" H 4200 3950 50  0001 C CNN
	1    4200 3950
	1    0    0    -1  
$EndComp
NoConn ~ 1400 1300
NoConn ~ 1500 1300
NoConn ~ 1600 1300
NoConn ~ 2100 1300
NoConn ~ 2400 1300
NoConn ~ 2700 1300
NoConn ~ 3000 1300
NoConn ~ 3900 1300
NoConn ~ 4500 1300
NoConn ~ 4800 1300
NoConn ~ 5000 1300
NoConn ~ 5100 1300
NoConn ~ 5200 1300
NoConn ~ 5300 1300
NoConn ~ 5400 1300
NoConn ~ 5500 1300
NoConn ~ 5600 1300
NoConn ~ 5700 1300
NoConn ~ 5800 1300
NoConn ~ 5900 1300
NoConn ~ 6000 1300
NoConn ~ 6100 1300
NoConn ~ 6200 1300
NoConn ~ 6300 1300
NoConn ~ 6400 1300
NoConn ~ 6500 1300
NoConn ~ 6600 1300
NoConn ~ 6700 1300
NoConn ~ 6800 1300
NoConn ~ 6900 1300
NoConn ~ 7000 1300
NoConn ~ 7100 1300
NoConn ~ 7200 1300
NoConn ~ 7300 1300
NoConn ~ 7400 1300
NoConn ~ 7500 1300
NoConn ~ 7600 1300
NoConn ~ 7700 1300
NoConn ~ 7800 1300
NoConn ~ 7900 1300
NoConn ~ 8000 1300
NoConn ~ 8100 1300
NoConn ~ 8200 1300
NoConn ~ 8300 1300
NoConn ~ 8400 1300
NoConn ~ 8500 1300
NoConn ~ 8600 1300
NoConn ~ 8700 1300
NoConn ~ 8800 1300
NoConn ~ 8900 1300
NoConn ~ 9000 1300
NoConn ~ 9100 1300
NoConn ~ 9500 1300
NoConn ~ 9600 1300
NoConn ~ 9700 1300
NoConn ~ 10100 1300
NoConn ~ 10200 1300
NoConn ~ 10300 1300
Text Label 2050 2750 0    50   ~ 0
PWR_BUT
Text Label 3450 2750 2    50   ~ 0
SYS_RESETN
$Comp
L VDD_ADC #PWR23
U 1 1 5920EEB5
P 2550 6550
F 0 "#PWR23" H 2550 6400 50  0001 C CNN
F 1 "VDD_ADC" H 2550 6690 50  0000 C CNN
F 2 "" H 2550 6550 60  0000 C CNN
F 3 "" H 2550 6550 60  0000 C CNN
	1    2550 6550
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5921459E
P 3850 7000
F 0 "C6" H 3875 7100 50  0000 L CNN
F 1 "100n" H 3875 6900 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 3888 6850 50  0001 C CNN
F 3 "" H 3850 7000 50  0001 C CNN
	1    3850 7000
	-1   0    0    1   
$EndComp
$Comp
L GNDA_ADC #PWR24
U 1 1 592146A4
P 2550 7450
F 0 "#PWR24" H 2550 7200 50  0001 C CNN
F 1 "GNDA_ADC" H 2550 7300 50  0000 C CNN
F 2 "" H 2550 7450 60  0000 C CNN
F 3 "" H 2550 7450 60  0000 C CNN
	1    2550 7450
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 59152226
P 2100 6900
F 0 "C5" H 2125 7000 50  0000 L CNN
F 1 "100n" H 2125 6800 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 2138 6750 50  0001 C CNN
F 3 "" H 2100 6900 50  0001 C CNN
	1    2100 6900
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X23 J7
U 1 1 59185E30
P 3900 3450
F 0 "J7" H 3900 4650 50  0000 C CNN
F 1 "CONN_01X23" V 4000 3450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x23_Pitch2.54mm" H 3900 3450 50  0001 C CNN
F 3 "" H 3900 3450 50  0001 C CNN
	1    3900 3450
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 59254A9C
P 4200 7000
F 0 "C4" H 4225 7100 50  0000 L CNN
F 1 "100n" H 4225 6900 50  0000 L CNN
F 2 "Capacitors_THT:C_Rect_L7.0mm_W2.5mm_P5.00mm" H 4238 6850 50  0001 C CNN
F 3 "" H 4200 7000 50  0001 C CNN
	1    4200 7000
	-1   0    0    1   
$EndComp
Entry Wire Line
	8200 2650 8100 2550
Entry Wire Line
	8200 3100 8100 3000
Entry Wire Line
	8200 2950 8100 2850
Entry Wire Line
	2200 1300 2300 1400
Entry Wire Line
	2500 1300 2600 1400
Entry Wire Line
	2800 1300 2900 1400
Entry Wire Line
	3100 1300 3200 1400
Text Label 2200 1300 1    60   ~ 0
C4
Text Label 2500 1300 1    60   ~ 0
C5
Text Label 2800 1300 1    60   ~ 0
C6
Text Label 3100 1300 1    60   ~ 0
C7
Text Label 8200 2800 2    60   ~ 0
C5
Text Label 8200 2950 2    60   ~ 0
C6
Text Label 8200 3100 2    60   ~ 0
C7
NoConn ~ 3300 1300
NoConn ~ 3600 1300
NoConn ~ 4200 1300
Entry Wire Line
	3400 1300 3500 1400
Entry Wire Line
	3700 1300 3800 1400
Entry Wire Line
	4000 1300 4100 1400
Entry Wire Line
	4300 1300 4400 1400
Text Label 3400 1300 1    60   ~ 0
C8
Text Label 3700 1300 1    60   ~ 0
C9
Text Label 4000 1300 1    60   ~ 0
C10
Text Label 4300 1300 1    60   ~ 0
C11
Entry Wire Line
	8200 2800 8100 2700
Text Label 8200 2650 2    60   ~ 0
C4
NoConn ~ 2000 1300
NoConn ~ 2300 1300
NoConn ~ 2600 1300
NoConn ~ 2900 1300
NoConn ~ 3200 1300
NoConn ~ 3500 1300
NoConn ~ 3800 1300
NoConn ~ 4100 1300
NoConn ~ 4400 1300
NoConn ~ 4700 1300
NoConn ~ 4600 1300
NoConn ~ 4900 1300
$Comp
L CONN_01X08 J12
U 1 1 592B6193
P 8700 3200
F 0 "J12" H 8700 3650 50  0000 C CNN
F 1 "CONN_01X08" V 8800 3200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 8700 3200 50  0001 C CNN
F 3 "" H 8700 3200 50  0001 C CNN
	1    8700 3200
	1    0    0    -1  
$EndComp
Entry Wire Line
	8200 3250 8100 3150
Entry Wire Line
	8200 3700 8100 3600
Entry Wire Line
	8200 3550 8100 3450
Text Label 8200 3400 2    60   ~ 0
C9
Text Label 8200 3550 2    60   ~ 0
C10
Text Label 8200 3700 2    60   ~ 0
C11
Entry Wire Line
	8200 3400 8100 3300
Text Label 8200 3250 2    60   ~ 0
C8
$Comp
L CONN_01X15 SR2
U 1 1 592BEAC1
P 8500 5650
F 0 "SR2" H 8500 6450 50  0000 C CNN
F 1 "CONN_01X15" V 8600 5650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 8500 5650 50  0001 C CNN
F 3 "" H 8500 5650 50  0001 C CNN
	1    8500 5650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR30
U 1 1 592BEE29
P 8200 4950
F 0 "#PWR30" H 8200 4800 50  0001 C CNN
F 1 "+5V" H 8200 5090 50  0000 C CNN
F 2 "" H 8200 4950 60  0000 C CNN
F 3 "" H 8200 4950 60  0000 C CNN
	1    8200 4950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR3
U 1 1 592BF26D
P 8950 5650
F 0 "SR3" H 8950 6450 50  0000 C CNN
F 1 "CONN_01X15" V 9050 5650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 8950 5650 50  0001 C CNN
F 3 "" H 8950 5650 50  0001 C CNN
	1    8950 5650
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR31
U 1 1 592BF501
P 8650 4950
F 0 "#PWR31" H 8650 4800 50  0001 C CNN
F 1 "+3V3" H 8650 5090 50  0000 C CNN
F 2 "" H 8650 4950 60  0000 C CNN
F 3 "" H 8650 4950 60  0000 C CNN
	1    8650 4950
	1    0    0    -1  
$EndComp
$Comp
L GNDD #PWR34
U 1 1 592BF894
P 10150 3400
F 0 "#PWR34" H 10150 3150 50  0001 C CNN
F 1 "GNDD" H 10150 3250 50  0000 C CNN
F 2 "" H 10150 3400 60  0000 C CNN
F 3 "" H 10150 3400 60  0000 C CNN
	1    10150 3400
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X30 SR1
U 1 1 592C084F
P 10450 4900
F 0 "SR1" H 10450 6450 50  0000 C CNN
F 1 "CONN_01X30" V 10550 4900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x30_Pitch2.54mm" H 10450 4900 50  0001 C CNN
F 3 "" H 10450 4900 50  0001 C CNN
	1    10450 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X12 SR4
U 1 1 592C1576
P 9900 5800
F 0 "SR4" H 9900 6450 50  0000 C CNN
F 1 "CONN_01X12" V 10000 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 9900 5800 50  0001 C CNN
F 3 "" H 9900 5800 50  0001 C CNN
	1    9900 5800
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X12 SR5
U 1 1 592C21ED
P 9900 4400
F 0 "SR5" H 9900 5050 50  0000 C CNN
F 1 "CONN_01X12" V 10000 4400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 9900 4400 50  0001 C CNN
F 3 "" H 9900 4400 50  0001 C CNN
	1    9900 4400
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X12 SR6
U 1 1 592C313E
P 9450 5800
F 0 "SR6" H 9450 6450 50  0000 C CNN
F 1 "CONN_01X12" V 9550 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x12_Pitch2.54mm" H 9450 5800 50  0001 C CNN
F 3 "" H 9450 5800 50  0001 C CNN
	1    9450 5800
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X30 SR7
U 1 1 592C3BD9
P 10800 4900
F 0 "SR7" H 10800 6450 50  0000 C CNN
F 1 "CONN_01X30" V 10900 4900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x30_Pitch2.54mm" H 10800 4900 50  0001 C CNN
F 3 "" H 10800 4900 50  0001 C CNN
	1    10800 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X26 SR8
U 1 1 592C4ED0
P 11100 4700
F 0 "SR8" H 11100 6050 50  0000 C CNN
F 1 "CONN_01X26" V 11200 4700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x26_Pitch2.54mm" H 11100 4700 50  0001 C CNN
F 3 "" H 11100 4700 50  0001 C CNN
	1    11100 4700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR9
U 1 1 592C6038
P 6000 5700
F 0 "SR9" H 6000 6500 50  0000 C CNN
F 1 "CONN_01X15" V 6100 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 6000 5700 50  0001 C CNN
F 3 "" H 6000 5700 50  0001 C CNN
	1    6000 5700
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR28
U 1 1 592C61FB
P 5700 5000
F 0 "#PWR28" H 5700 4850 50  0001 C CNN
F 1 "+12V" H 5700 5140 50  0000 C CNN
F 2 "" H 5700 5000 50  0001 C CNN
F 3 "" H 5700 5000 50  0001 C CNN
	1    5700 5000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR10
U 1 1 592C6322
P 6350 5700
F 0 "SR10" H 6350 6500 50  0000 C CNN
F 1 "CONN_01X15" V 6450 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 6350 5700 50  0001 C CNN
F 3 "" H 6350 5700 50  0001 C CNN
	1    6350 5700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR11
U 1 1 592C63DF
P 6700 5700
F 0 "SR11" H 6700 6500 50  0000 C CNN
F 1 "CONN_01X15" V 6800 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 6700 5700 50  0001 C CNN
F 3 "" H 6700 5700 50  0001 C CNN
	1    6700 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 1300 1200 1800
Wire Wire Line
	1700 4450 3700 4450
Wire Wire Line
	1700 4350 2450 4350
Wire Wire Line
	2450 4050 1700 4050
Wire Wire Line
	1700 3950 2450 3950
Connection ~ 1700 4150
Connection ~ 1700 4250
Connection ~ 3700 2350
Wire Wire Line
	2950 2850 3700 2850
Wire Wire Line
	2950 2950 4150 2950
Wire Wire Line
	2950 3050 3700 3050
Wire Wire Line
	3700 3150 2950 3150
Wire Wire Line
	2950 3250 3700 3250
Wire Wire Line
	3700 3350 2950 3350
Wire Wire Line
	2950 3450 3700 3450
Wire Wire Line
	3700 3550 2950 3550
Wire Wire Line
	2950 3650 3700 3650
Wire Wire Line
	3700 3750 2950 3750
Connection ~ 1700 2350
Connection ~ 2300 2450
Connection ~ 2100 2550
Connection ~ 1850 2650
Wire Wire Line
	2450 2850 1700 2850
Wire Wire Line
	2450 2950 1700 2950
Wire Wire Line
	1700 3050 2450 3050
Wire Wire Line
	1700 3150 2450 3150
Wire Wire Line
	2450 3250 1700 3250
Wire Wire Line
	1700 3350 2450 3350
Wire Wire Line
	1700 3450 2450 3450
Wire Wire Line
	1700 3650 2450 3650
Wire Wire Line
	1700 3550 2450 3550
Wire Wire Line
	1700 3750 2450 3750
Wire Wire Line
	2450 3850 1700 3850
Connection ~ 3700 3850
Connection ~ 3700 3950
Connection ~ 3700 4150
Connection ~ 3700 4250
Wire Wire Line
	3100 4750 3100 4450
Connection ~ 2300 4450
Connection ~ 3100 4450
Wire Wire Line
	5750 3350 5500 3350
Wire Wire Line
	5500 3450 5750 3450
Wire Wire Line
	5750 3550 5500 3550
Wire Wire Line
	5500 3650 5750 3650
Wire Wire Line
	5750 3750 5500 3750
Wire Wire Line
	5500 3850 5750 3850
Wire Wire Line
	5750 3950 5500 3950
Wire Wire Line
	5500 4050 5750 4050
Wire Wire Line
	5750 4150 5500 4150
Wire Wire Line
	5500 4250 5750 4250
Wire Wire Line
	5750 4350 5500 4350
Wire Wire Line
	5500 4450 5750 4450
Wire Wire Line
	5750 4550 5500 4550
Wire Wire Line
	6500 4550 6250 4550
Wire Wire Line
	6250 4450 6500 4450
Wire Wire Line
	6500 4350 6250 4350
Wire Wire Line
	6250 4250 6500 4250
Wire Wire Line
	6250 4150 6500 4150
Wire Wire Line
	6500 4050 6250 4050
Wire Wire Line
	6250 3950 6500 3950
Wire Wire Line
	6500 3850 6250 3850
Wire Wire Line
	6250 3750 6500 3750
Wire Wire Line
	6500 3650 6250 3650
Wire Wire Line
	6250 3550 6500 3550
Wire Wire Line
	6500 3450 6250 3450
Wire Wire Line
	6250 3350 6500 3350
Wire Wire Line
	6250 3250 6500 3250
Wire Wire Line
	6500 3150 6250 3150
Wire Wire Line
	6250 3050 6500 3050
Wire Wire Line
	6500 2950 6250 2950
Wire Wire Line
	6250 2850 6500 2850
Wire Wire Line
	6250 2750 6500 2750
Wire Wire Line
	6250 2650 6500 2650
Wire Wire Line
	6250 2550 6500 2550
Wire Wire Line
	5500 3050 5750 3050
Wire Wire Line
	5500 2950 5750 2950
Wire Wire Line
	5500 2850 5750 2850
Wire Wire Line
	5500 2750 5750 2750
Wire Wire Line
	5500 2650 5750 2650
Wire Wire Line
	5500 2550 5750 2550
Wire Wire Line
	5500 2450 5750 2450
Connection ~ 5500 2350
Wire Wire Line
	6250 2450 6500 2450
Wire Wire Line
	6500 2350 6250 2350
Connection ~ 10600 1300
Wire Wire Line
	10900 1250 10900 1400
Wire Wire Line
	1200 1550 1100 1550
Connection ~ 10500 1300
Connection ~ 1200 1300
Wire Wire Line
	1100 1300 1300 1300
Wire Wire Line
	10400 1300 10900 1300
Wire Wire Line
	1100 4150 2450 4150
Wire Wire Line
	1100 4250 2450 4250
Wire Wire Line
	2950 4250 4200 4250
Wire Wire Line
	2950 4150 4200 4150
Wire Wire Line
	5500 3250 5750 3250
Wire Wire Line
	2950 4350 3700 4350
Connection ~ 3600 6750
Connection ~ 1800 6300
Wire Wire Line
	1800 6250 1800 6300
Wire Wire Line
	3500 6750 4550 6750
Wire Wire Line
	3600 7150 3600 6750
Wire Wire Line
	2700 6850 2900 6850
Wire Wire Line
	1650 7250 3100 7250
Wire Wire Line
	1650 6300 3100 6300
Wire Wire Line
	3100 6300 3100 6450
Wire Wire Line
	1700 2750 2450 2750
Wire Wire Line
	2950 2750 3700 2750
Wire Wire Line
	4850 3850 4850 3800
Wire Wire Line
	5150 2350 5750 2350
Wire Wire Line
	1200 2350 3700 2350
Wire Wire Line
	1850 2150 1850 2650
Wire Wire Line
	1700 2650 3700 2650
Wire Wire Line
	2100 2550 2100 2150
Wire Wire Line
	1700 2550 3700 2550
Wire Wire Line
	2300 2150 2300 2450
Wire Wire Line
	1700 2450 3700 2450
Connection ~ 2700 4750
Wire Wire Line
	2300 4750 3100 4750
Connection ~ 3100 4550
Wire Wire Line
	1700 4550 3700 4550
Connection ~ 2300 4550
Wire Wire Line
	2300 4450 2300 4750
Wire Wire Line
	2950 3850 4850 3850
Wire Wire Line
	2950 3950 4850 3950
Wire Wire Line
	3700 4050 2950 4050
Wire Wire Line
	1800 1300 1800 1800
Wire Wire Line
	1700 1300 1900 1300
Connection ~ 1800 1300
Wire Wire Line
	1800 1550 1700 1550
Wire Wire Line
	9800 1300 10000 1300
Wire Wire Line
	9200 1300 9400 1300
Wire Wire Line
	10000 1300 10000 1800
Wire Wire Line
	10000 1550 9850 1550
Wire Wire Line
	9400 1300 9400 1800
Wire Wire Line
	9400 1550 9250 1550
Connection ~ 9300 1300
Connection ~ 9900 1300
Wire Wire Line
	10000 1800 9850 1800
Connection ~ 10000 1550
Wire Wire Line
	9400 1800 9250 1800
Connection ~ 9400 1550
Wire Wire Line
	1800 1800 1700 1800
Connection ~ 1800 1550
Wire Wire Line
	1200 1800 1100 1800
Connection ~ 1200 1550
Connection ~ 10900 1300
Wire Wire Line
	1600 2250 1850 2250
Connection ~ 1850 2250
Wire Wire Line
	2550 2250 2300 2250
Connection ~ 2300 2250
Connection ~ 2950 2450
Connection ~ 2450 2450
Connection ~ 2450 2350
Connection ~ 2950 2350
Connection ~ 2950 2550
Connection ~ 2450 2550
Connection ~ 2950 2650
Connection ~ 2450 2650
Connection ~ 2950 4450
Connection ~ 2450 4450
Connection ~ 2450 4550
Connection ~ 2950 4550
Connection ~ 3700 2450
Connection ~ 3700 2550
Connection ~ 3700 2650
Connection ~ 1700 2450
Connection ~ 1700 2550
Connection ~ 1700 2650
Wire Wire Line
	1800 7200 1800 7250
Connection ~ 1800 7250
Connection ~ 4450 3850
Connection ~ 4200 3950
Connection ~ 9950 -700
Wire Wire Line
	3600 7150 3450 7150
Wire Wire Line
	3150 7150 2800 7150
Wire Wire Line
	2800 7150 2800 6850
Connection ~ 2800 6850
Wire Wire Line
	3850 7350 3850 7150
Wire Wire Line
	2550 7350 2550 7450
Wire Wire Line
	3850 6850 3850 6750
Connection ~ 3850 6750
Wire Wire Line
	2100 7050 2100 7350
Wire Wire Line
	2100 7350 4200 7350
Wire Wire Line
	2550 6550 2550 6650
Wire Wire Line
	2400 6850 2350 6850
Wire Wire Line
	2350 6850 2350 7350
Connection ~ 2350 7350
Connection ~ 2550 7350
Wire Wire Line
	3100 7250 3100 7050
Wire Wire Line
	2100 6650 2900 6650
Connection ~ 2550 6650
Wire Wire Line
	2100 6650 2100 6750
Wire Wire Line
	1100 3350 1750 3350
Connection ~ 1750 3350
Connection ~ 3700 2950
Wire Wire Line
	1100 3450 1750 3450
Connection ~ 1750 3450
Wire Wire Line
	5500 3150 5750 3150
Wire Wire Line
	4200 6850 4200 6750
Connection ~ 4200 6750
Wire Wire Line
	4200 7350 4200 7150
Connection ~ 3850 7350
Wire Wire Line
	5150 2350 5150 2250
Wire Bus Line
	2000 1400 8900 1400
Wire Bus Line
	8100 1400 8100 3250
Wire Bus Line
	8100 2950 8100 3850
Connection ~ 8200 2800
Connection ~ 2200 1300
Connection ~ 2500 1300
Connection ~ 2800 1300
Connection ~ 3100 1300
Connection ~ 8200 2950
Connection ~ 8200 3100
Connection ~ 3400 1300
Connection ~ 3700 1300
Connection ~ 4000 1300
Connection ~ 4300 1300
Connection ~ 8200 2650
Wire Bus Line
	8100 2000 8100 3000
Wire Bus Line
	8100 3550 8100 3600
Connection ~ 8200 3400
Connection ~ 8200 3550
Connection ~ 8200 3700
Connection ~ 8200 3250
Wire Bus Line
	8100 3100 8100 3200
Wire Wire Line
	8500 2850 8450 2850
Wire Wire Line
	8450 2850 8450 2650
Wire Wire Line
	8450 2650 8200 2650
Wire Wire Line
	8500 2950 8400 2950
Wire Wire Line
	8400 2950 8400 2800
Wire Wire Line
	8400 2800 8200 2800
Wire Wire Line
	8500 3050 8350 3050
Wire Wire Line
	8350 3050 8350 2950
Wire Wire Line
	8350 2950 8200 2950
Wire Wire Line
	8500 3150 8300 3150
Wire Wire Line
	8300 3150 8300 3100
Wire Wire Line
	8300 3100 8200 3100
Wire Wire Line
	8500 3250 8200 3250
Wire Wire Line
	8500 3550 8450 3550
Wire Wire Line
	8450 3550 8450 3700
Wire Wire Line
	8450 3700 8200 3700
Wire Wire Line
	8500 3450 8400 3450
Wire Wire Line
	8400 3450 8400 3550
Wire Wire Line
	8400 3550 8200 3550
Wire Wire Line
	8500 3350 8350 3350
Wire Wire Line
	8350 3350 8350 3400
Wire Wire Line
	8350 3400 8200 3400
Connection ~ 10250 3650
Connection ~ 10250 3550
Connection ~ 10250 3450
Wire Wire Line
	10250 3450 10250 4850
Connection ~ 8300 6250
Connection ~ 8300 6150
Connection ~ 8300 6050
Connection ~ 8300 5950
Connection ~ 8300 5850
Connection ~ 8300 5750
Connection ~ 8300 5650
Connection ~ 8300 5550
Connection ~ 8300 5450
Connection ~ 8300 5350
Connection ~ 8300 5250
Connection ~ 8300 5150
Connection ~ 8300 5050
Connection ~ 8300 4950
Wire Wire Line
	8300 4950 8200 4950
Wire Wire Line
	8300 4950 8300 6350
Connection ~ 8750 6250
Connection ~ 8750 6150
Connection ~ 8750 6050
Connection ~ 8750 5950
Connection ~ 8750 5850
Connection ~ 8750 5750
Connection ~ 8750 5650
Connection ~ 8750 5550
Connection ~ 8750 5450
Connection ~ 8750 5350
Connection ~ 8750 5250
Connection ~ 8750 5150
Connection ~ 8750 5050
Connection ~ 8750 4950
Wire Wire Line
	8750 4950 8650 4950
Wire Wire Line
	8750 4950 8750 6350
Wire Wire Line
	10150 3450 10600 3450
Wire Wire Line
	10150 3450 10150 3400
Wire Wire Line
	10250 6350 10250 4650
Connection ~ 10250 4650
Connection ~ 10250 3750
Connection ~ 10250 3850
Connection ~ 10250 3950
Connection ~ 10250 4050
Connection ~ 10250 4150
Connection ~ 10250 4250
Connection ~ 10250 4350
Connection ~ 10250 4450
Connection ~ 10250 4550
Connection ~ 10250 4750
Connection ~ 10250 4850
Connection ~ 10250 4950
Connection ~ 10250 5050
Connection ~ 10250 5150
Connection ~ 10250 5250
Connection ~ 10250 5350
Connection ~ 10250 5450
Connection ~ 10250 5550
Connection ~ 10250 5650
Connection ~ 10250 5750
Connection ~ 10250 5850
Connection ~ 10250 5950
Connection ~ 10250 6050
Connection ~ 10250 6150
Connection ~ 10250 6250
Wire Wire Line
	10100 6350 10100 5250
Wire Wire Line
	9650 5250 10250 5250
Connection ~ 10100 5350
Connection ~ 10100 5450
Connection ~ 10100 5550
Connection ~ 10100 5650
Connection ~ 10100 5750
Connection ~ 10100 5850
Connection ~ 10100 5950
Connection ~ 10100 6050
Connection ~ 10100 6150
Connection ~ 10100 6250
Wire Wire Line
	10100 4950 10100 3850
Wire Wire Line
	10100 3850 10250 3850
Connection ~ 10100 3950
Connection ~ 10100 4050
Connection ~ 10100 4150
Connection ~ 10100 4250
Connection ~ 10100 4350
Connection ~ 10100 4450
Connection ~ 10100 4550
Connection ~ 10100 4650
Connection ~ 10100 4750
Connection ~ 10100 4850
Wire Wire Line
	9650 6350 9650 5250
Connection ~ 9650 5350
Connection ~ 9650 5450
Connection ~ 9650 5550
Connection ~ 9650 5650
Connection ~ 9650 5750
Connection ~ 9650 5850
Connection ~ 9650 5950
Connection ~ 9650 6050
Connection ~ 9650 6150
Connection ~ 9650 6250
Connection ~ 10100 5250
Connection ~ 10600 3650
Connection ~ 10600 3550
Connection ~ 10600 3450
Wire Wire Line
	10600 3450 10600 4850
Wire Wire Line
	10600 6350 10600 4650
Connection ~ 10600 4650
Connection ~ 10600 3750
Connection ~ 10600 3850
Connection ~ 10600 3950
Connection ~ 10600 4050
Connection ~ 10600 4150
Connection ~ 10600 4250
Connection ~ 10600 4350
Connection ~ 10600 4450
Connection ~ 10600 4550
Connection ~ 10600 4750
Connection ~ 10600 4850
Connection ~ 10600 4950
Connection ~ 10600 5050
Connection ~ 10600 5150
Connection ~ 10600 5250
Connection ~ 10600 5350
Connection ~ 10600 5450
Connection ~ 10600 5550
Connection ~ 10600 5650
Connection ~ 10600 5750
Connection ~ 10600 5850
Connection ~ 10600 5950
Connection ~ 10600 6050
Connection ~ 10600 6150
Connection ~ 10600 6250
Wire Wire Line
	10450 3450 10900 3450
Connection ~ 10900 3650
Connection ~ 10900 3550
Connection ~ 10900 3450
Wire Wire Line
	10900 3450 10900 4850
Connection ~ 10900 4650
Connection ~ 10900 3750
Connection ~ 10900 3850
Connection ~ 10900 3950
Connection ~ 10900 4050
Connection ~ 10900 4150
Connection ~ 10900 4250
Connection ~ 10900 4350
Connection ~ 10900 4450
Connection ~ 10900 4550
Connection ~ 10900 4750
Connection ~ 10900 4850
Connection ~ 10900 4950
Connection ~ 10900 5050
Connection ~ 10900 5150
Connection ~ 10900 5250
Connection ~ 10900 5350
Connection ~ 10900 5450
Connection ~ 10900 5550
Connection ~ 10900 5650
Connection ~ 10900 5750
Connection ~ 10900 5850
Connection ~ 10900 5950
Wire Wire Line
	10900 5950 10900 4250
Connection ~ 5800 6300
Connection ~ 5800 6200
Connection ~ 5800 6100
Connection ~ 5800 6000
Connection ~ 5800 5900
Connection ~ 5800 5800
Connection ~ 5800 5700
Connection ~ 5800 5600
Connection ~ 5800 5500
Connection ~ 5800 5400
Connection ~ 5800 5300
Connection ~ 5800 5200
Connection ~ 5800 5100
Connection ~ 5800 5000
Wire Wire Line
	5700 5000 6500 5000
Wire Wire Line
	5800 5000 5800 6400
Connection ~ 6150 6300
Connection ~ 6150 6200
Connection ~ 6150 6100
Connection ~ 6150 6000
Connection ~ 6150 5900
Connection ~ 6150 5800
Connection ~ 6150 5700
Connection ~ 6150 5600
Connection ~ 6150 5500
Connection ~ 6150 5400
Connection ~ 6150 5300
Connection ~ 6150 5200
Connection ~ 6150 5100
Connection ~ 6150 5000
Wire Wire Line
	6150 5000 6150 6400
Connection ~ 6500 6300
Connection ~ 6500 6200
Connection ~ 6500 6100
Connection ~ 6500 6000
Connection ~ 6500 5900
Connection ~ 6500 5800
Connection ~ 6500 5700
Connection ~ 6500 5600
Connection ~ 6500 5500
Connection ~ 6500 5400
Connection ~ 6500 5300
Connection ~ 6500 5200
Connection ~ 6500 5100
Connection ~ 6500 5000
Wire Wire Line
	6500 5000 6500 6400
$Comp
L CONN_01X15 SR12
U 1 1 592C7662
P 7250 5700
F 0 "SR12" H 7250 6500 50  0000 C CNN
F 1 "CONN_01X15" V 7350 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 7250 5700 50  0001 C CNN
F 3 "" H 7250 5700 50  0001 C CNN
	1    7250 5700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR13
U 1 1 592C766E
P 7600 5700
F 0 "SR13" H 7600 6500 50  0000 C CNN
F 1 "CONN_01X15" V 7700 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 7600 5700 50  0001 C CNN
F 3 "" H 7600 5700 50  0001 C CNN
	1    7600 5700
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X15 SR14
U 1 1 592C7674
P 7950 5700
F 0 "SR14" H 7950 6500 50  0000 C CNN
F 1 "CONN_01X15" V 8050 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x15_Pitch2.54mm" H 7950 5700 50  0001 C CNN
F 3 "" H 7950 5700 50  0001 C CNN
	1    7950 5700
	1    0    0    -1  
$EndComp
Connection ~ 7050 6300
Connection ~ 7050 6200
Connection ~ 7050 6100
Connection ~ 7050 6000
Connection ~ 7050 5900
Connection ~ 7050 5800
Connection ~ 7050 5700
Connection ~ 7050 5600
Connection ~ 7050 5500
Connection ~ 7050 5400
Connection ~ 7050 5300
Connection ~ 7050 5200
Connection ~ 7050 5100
Connection ~ 7050 5000
Wire Wire Line
	6950 5000 7750 5000
Wire Wire Line
	7050 5000 7050 6400
Connection ~ 7400 6300
Connection ~ 7400 6200
Connection ~ 7400 6100
Connection ~ 7400 6000
Connection ~ 7400 5900
Connection ~ 7400 5800
Connection ~ 7400 5700
Connection ~ 7400 5600
Connection ~ 7400 5500
Connection ~ 7400 5400
Connection ~ 7400 5300
Connection ~ 7400 5200
Connection ~ 7400 5100
Connection ~ 7400 5000
Wire Wire Line
	7400 5000 7400 6400
Connection ~ 7750 6300
Connection ~ 7750 6200
Connection ~ 7750 6100
Connection ~ 7750 6000
Connection ~ 7750 5900
Connection ~ 7750 5800
Connection ~ 7750 5700
Connection ~ 7750 5600
Connection ~ 7750 5500
Connection ~ 7750 5400
Connection ~ 7750 5300
Connection ~ 7750 5200
Connection ~ 7750 5100
Connection ~ 7750 5000
Wire Wire Line
	7750 5000 7750 6400
$Comp
L -12V #PWR29
U 1 1 592C78D9
P 6950 5000
F 0 "#PWR29" H 6950 5100 50  0001 C CNN
F 1 "-12V" H 6950 5150 50  0000 C CNN
F 2 "" H 6950 5000 50  0001 C CNN
F 3 "" H 6950 5000 50  0001 C CNN
	1    6950 5000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
