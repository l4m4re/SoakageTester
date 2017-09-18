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
Sheet 11 19
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
S 2150 1550 700  300 
U 592D3C54
F0 "Filter1" 60
F1 "SallenKey.sch" 60
F2 "V_in" I L 2150 1700 60 
F3 "V_out" I R 2850 1700 60 
$EndSheet
$Sheet
S 2150 2150 700  300 
U 592D5259
F0 "Filter2" 60
F1 "SallenKey.sch" 60
F2 "V_in" I L 2150 2300 60 
F3 "V_out" I R 2850 2300 60 
$EndSheet
$Comp
L CONN_01X04 J13
U 1 1 592D530A
P 1600 2000
F 0 "J13" H 1600 2250 50  0000 C CNN
F 1 "CONN_01X04" V 1700 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 1600 2000 50  0001 C CNN
F 3 "" H 1600 2000 50  0001 C CNN
	1    1600 2000
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X04 J14
U 1 1 592D5375
P 3450 2000
F 0 "J14" H 3450 2250 50  0000 C CNN
F 1 "CONN_01X04" V 3550 2000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 3450 2000 50  0001 C CNN
F 3 "" H 3450 2000 50  0001 C CNN
	1    3450 2000
	1    0    0    -1  
$EndComp
$Sheet
S 2150 2700 700  300 
U 592D6921
F0 "Filter3" 60
F1 "SallenKey.sch" 60
F2 "V_in" I L 2150 2850 60 
F3 "V_out" I R 2850 2850 60 
$EndSheet
$Sheet
S 2150 3200 700  300 
U 592D7C38
F0 "Filter4" 60
F1 "SallenKey.sch" 60
F2 "V_in" I L 2150 3350 60 
F3 "V_out" I R 2850 3350 60 
$EndSheet
$Sheet
S 2150 4300 1150 400 
U 592DBAFF
F0 "Amp1" 60
F1 "Opamp.sch" 60
F2 "V_out" O R 3300 4500 60 
F3 "V_in+" I L 2150 4350 60 
F4 "V_in-" I L 2150 4500 60 
F5 "V_ref" I L 2150 4650 60 
$EndSheet
Text HLabel 1200 4500 0    60   Input ~ 0
V_ref
$Comp
L CONN_01X04 J17
U 1 1 592DFA19
P 3950 4900
F 0 "J17" H 3950 5150 50  0000 C CNN
F 1 "CONN_01X04" V 4050 4900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 3950 4900 50  0001 C CNN
F 3 "" H 3950 4900 50  0001 C CNN
	1    3950 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 J15
U 1 1 592E03B5
P 1050 4950
F 0 "J15" H 1050 5200 50  0000 C CNN
F 1 "CONN_01X04" V 1150 4950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 1050 4950 50  0001 C CNN
F 3 "" H 1050 4950 50  0001 C CNN
	1    1050 4950
	-1   0    0    -1  
$EndComp
$Comp
L GNDA_ADC #PWR48
U 1 1 592E1EF7
P 1400 5850
F 0 "#PWR48" H 1400 5600 50  0001 C CNN
F 1 "GNDA_ADC" H 1400 5700 50  0000 C CNN
F 2 "" H 1400 5850 60  0000 C CNN
F 3 "" H 1400 5850 60  0000 C CNN
	1    1400 5850
	1    0    0    -1  
$EndComp
$Sheet
S 2150 5100 1150 400 
U 592E70C1
F0 "Amp2" 60
F1 "Opamp.sch" 60
F2 "V_out" O R 3300 5300 60 
F3 "V_in+" I L 2150 5150 60 
F4 "V_in-" I L 2150 5300 60 
F5 "V_ref" I L 2150 5450 60 
$EndSheet
$Sheet
S 2150 5900 1150 400 
U 592E73B7
F0 "Amp3" 60
F1 "Opamp.sch" 60
F2 "V_out" O R 3300 6100 60 
F3 "V_in+" I L 2150 5950 60 
F4 "V_in-" I L 2150 6100 60 
F5 "V_ref" I L 2150 6250 60 
$EndSheet
$Sheet
S 2150 6600 1150 400 
U 592E74F8
F0 "Amp4" 60
F1 "Opamp.sch" 60
F2 "V_out" O R 3300 6800 60 
F3 "V_in+" I L 2150 6650 60 
F4 "V_in-" I L 2150 6800 60 
F5 "V_ref" I L 2150 6950 60 
$EndSheet
Wire Wire Line
	3250 1850 3050 1850
Wire Wire Line
	3050 1850 3050 1700
Wire Wire Line
	3050 1700 2850 1700
Wire Wire Line
	2150 1700 1950 1700
Wire Wire Line
	1950 1700 1950 1850
Wire Wire Line
	2050 1950 2050 2300
Wire Wire Line
	2050 2300 2150 2300
Wire Wire Line
	2850 2300 3050 2300
Wire Wire Line
	3050 2300 3050 1950
Wire Wire Line
	3050 1950 3250 1950
Wire Wire Line
	2850 2850 3100 2850
Wire Wire Line
	3100 2850 3100 2050
Wire Wire Line
	3100 2050 3250 2050
Wire Wire Line
	2000 2050 2000 2850
Wire Wire Line
	2000 2850 2150 2850
Wire Wire Line
	3250 2150 3150 2150
Wire Wire Line
	3150 2150 3150 3350
Wire Wire Line
	3150 3350 2850 3350
Wire Wire Line
	1900 2150 1900 3350
Wire Wire Line
	1900 3350 2150 3350
Wire Wire Line
	2150 4650 1950 4650
Wire Wire Line
	1950 4500 1950 6950
Wire Wire Line
	1950 4500 1200 4500
Wire Wire Line
	1250 4800 1800 4800
Wire Wire Line
	1800 4800 1800 4350
Wire Wire Line
	1800 4350 2150 4350
Wire Wire Line
	3750 4750 3600 4750
Wire Wire Line
	3600 4750 3600 4500
Wire Wire Line
	3600 4500 3300 4500
Wire Wire Line
	1950 1850 1800 1850
Wire Wire Line
	2050 1950 1800 1950
Wire Wire Line
	2000 2050 1800 2050
Wire Wire Line
	1900 2150 1800 2150
Wire Wire Line
	1250 5800 1400 5800
Wire Wire Line
	1400 5800 1400 5850
Wire Wire Line
	1250 5400 2000 5400
Wire Wire Line
	2000 5400 2000 4500
Wire Wire Line
	2000 4500 2150 4500
Wire Wire Line
	1950 5450 2150 5450
Connection ~ 1950 4650
Wire Wire Line
	1950 6950 2150 6950
Connection ~ 1950 5450
Wire Wire Line
	2150 6250 1950 6250
Connection ~ 1950 6250
Wire Wire Line
	2150 5150 1900 5150
Wire Wire Line
	1900 5150 1900 4900
Wire Wire Line
	1900 4900 1250 4900
Wire Wire Line
	2150 5950 1850 5950
Wire Wire Line
	1850 5950 1850 5000
Wire Wire Line
	1850 5000 1250 5000
Wire Wire Line
	2150 6650 1800 6650
Wire Wire Line
	1800 6650 1800 5100
Wire Wire Line
	1800 5100 1250 5100
Wire Wire Line
	2150 5300 1750 5300
Wire Wire Line
	1750 5300 1750 5500
Wire Wire Line
	1750 5500 1250 5500
Wire Wire Line
	2150 6100 2000 6100
Wire Wire Line
	2000 6100 2000 5600
Wire Wire Line
	2000 5600 1250 5600
Wire Wire Line
	2150 6800 1750 6800
Wire Wire Line
	1750 6800 1750 5700
Wire Wire Line
	1750 5700 1250 5700
Wire Wire Line
	3750 4850 3450 4850
Wire Wire Line
	3450 4850 3450 5300
Wire Wire Line
	3450 5300 3300 5300
Wire Wire Line
	3750 4950 3500 4950
Wire Wire Line
	3500 4950 3500 6100
Wire Wire Line
	3500 6100 3300 6100
Wire Wire Line
	3750 5050 3600 5050
Wire Wire Line
	3600 5050 3600 6800
Wire Wire Line
	3600 6800 3300 6800
$Comp
L CONN_01X05 J16
U 1 1 592EB8B6
P 1050 5600
F 0 "J16" H 1050 5900 50  0000 C CNN
F 1 "CONN_01X05" V 1150 5600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05_Pitch2.54mm" H 1050 5600 50  0001 C CNN
F 3 "" H 1050 5600 50  0001 C CNN
	1    1050 5600
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
