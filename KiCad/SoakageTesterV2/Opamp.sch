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
Sheet 16 19
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2250 3600 0    60   Input ~ 0
OPAMP_Vdd
$Comp
L LM2902N U7
U 1 1 592DC11A
P 3750 2950
AR Path="/592D275E/592DBAFF/592DC11A" Ref="U7"  Part="1" 
AR Path="/592D275E/592E70C1/592DC11A" Ref="U7"  Part="2" 
AR Path="/592D275E/592E73B7/592DC11A" Ref="U7"  Part="3" 
AR Path="/592D275E/592E74F8/592DC11A" Ref="U7"  Part="4" 
F 0 "U7" H 3750 3150 50  0000 L CNN
F 1 "LM2902N" H 3750 2750 50  0000 L CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_Socket_LongPads" H 3700 3050 50  0001 C CNN
F 3 "" H 3800 3150 50  0001 C CNN
	1    3750 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3600 3650 3250
Wire Wire Line
	2250 3600 3650 3600
$Comp
L R R50
U 1 1 592DC123
P 3000 2850
AR Path="/592D275E/592DBAFF/592DC123" Ref="R50"  Part="1" 
AR Path="/592D275E/592E70C1/592DC123" Ref="R54"  Part="1" 
AR Path="/592D275E/592E73B7/592DC123" Ref="R58"  Part="1" 
AR Path="/592D275E/592E74F8/592DC123" Ref="R62"  Part="1" 
F 0 "R50" V 3080 2850 50  0000 C CNN
F 1 "3456" V 3000 2850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2930 2850 50  0001 C CNN
F 3 "" H 3000 2850 50  0001 C CNN
	1    3000 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 2850 3450 2850
$Comp
L R R53
U 1 1 592DC12B
P 3850 3300
AR Path="/592D275E/592DBAFF/592DC12B" Ref="R53"  Part="1" 
AR Path="/592D275E/592E70C1/592DC12B" Ref="R57"  Part="1" 
AR Path="/592D275E/592E73B7/592DC12B" Ref="R61"  Part="1" 
AR Path="/592D275E/592E74F8/592DC12B" Ref="R65"  Part="1" 
F 0 "R53" V 3930 3300 50  0000 C CNN
F 1 "3456" V 3850 3300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3780 3300 50  0001 C CNN
F 3 "" H 3850 3300 50  0001 C CNN
	1    3850 3300
	0    1    1    0   
$EndComp
$Comp
L R R51
U 1 1 592DC132
P 3000 3300
AR Path="/592D275E/592DBAFF/592DC132" Ref="R51"  Part="1" 
AR Path="/592D275E/592E70C1/592DC132" Ref="R55"  Part="1" 
AR Path="/592D275E/592E73B7/592DC132" Ref="R59"  Part="1" 
AR Path="/592D275E/592E74F8/592DC132" Ref="R63"  Part="1" 
F 0 "R51" V 3080 3300 50  0000 C CNN
F 1 "3456" V 3000 3300 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2930 3300 50  0001 C CNN
F 3 "" H 3000 3300 50  0001 C CNN
	1    3000 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3300 3700 3300
Wire Wire Line
	4000 3300 4250 3300
Wire Wire Line
	4250 3300 4250 2950
Wire Wire Line
	4050 2950 4900 2950
Wire Wire Line
	2850 2850 2650 2850
Text HLabel 4900 2950 2    60   Output ~ 0
V_out
Connection ~ 4250 2950
Wire Wire Line
	2850 3300 2650 3300
$Comp
L R R52
U 1 1 592DC150
P 3300 2600
AR Path="/592D275E/592DBAFF/592DC150" Ref="R52"  Part="1" 
AR Path="/592D275E/592E70C1/592DC150" Ref="R56"  Part="1" 
AR Path="/592D275E/592E73B7/592DC150" Ref="R60"  Part="1" 
AR Path="/592D275E/592E74F8/592DC150" Ref="R64"  Part="1" 
F 0 "R52" V 3380 2600 50  0000 C CNN
F 1 "3456" V 3300 2600 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3230 2600 50  0001 C CNN
F 3 "" H 3300 2600 50  0001 C CNN
	1    3300 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2350 3300 2350
Text HLabel 2600 2350 0    60   Input ~ 0
V_in+
Wire Wire Line
	2250 2100 3650 2100
Text GLabel 2250 2100 0    60   Input ~ 0
OPAMP_Vss
Wire Wire Line
	3650 2100 3650 2650
Wire Wire Line
	3300 2350 3300 2450
Connection ~ 3300 2850
Wire Wire Line
	3450 3050 3300 3050
Wire Wire Line
	3300 3050 3300 3300
Connection ~ 3300 3300
Text HLabel 2650 3300 0    60   Input ~ 0
V_in-
Text HLabel 2650 2850 0    60   Input ~ 0
V_ref
Wire Wire Line
	3300 2750 3300 2850
$EndSCHEMATC
