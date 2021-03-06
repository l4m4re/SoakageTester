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
Sheet 3 19
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
L IXTP10P50P Q6
U 1 1 58F74B1B
P 5950 2050
F 0 "Q6" H 6200 2125 50  0000 L CNN
F 1 "IXTP10P50P" H 6200 2050 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 6200 1975 50  0000 L CIN
F 3 "" H 5950 2050 50  0000 L CNN
	1    5950 2050
	1    0    0    1   
$EndComp
$Comp
L IRFB3307 Q5
U 1 1 58F751F0
P 5900 3350
F 0 "Q5" H 6150 3425 50  0000 L CNN
F 1 "IRFB3307" H 6150 3350 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 6150 3275 50  0000 L CIN
F 3 "" H 5900 3350 50  0000 L CNN
	1    5900 3350
	1    0    0    -1  
$EndComp
$Comp
L D_Zener_ALT D2
U 1 1 5901F635
P 5500 1750
F 0 "D2" H 5500 1850 50  0000 C CNN
F 1 "12V" H 5500 1650 50  0000 C CNN
F 2 "Diodes_THT:D_A-405_P2.54mm_Vertical_KathodeUp" H 5500 1750 50  0001 C CNN
F 3 "" H 5500 1750 50  0000 C CNN
	1    5500 1750
	0    1    1    0   
$EndComp
$Comp
L Screw_Terminal_1x02 J3
U 1 1 59021216
P 7550 1600
F 0 "J3" H 7550 1850 50  0000 C TNN
F 1 "Coil" V 7400 1600 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 7550 1375 50  0001 C CNN
F 3 "" H 7525 1600 50  0001 C CNN
	1    7550 1600
	-1   0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J4
U 1 1 5902133F
P 7650 2800
F 0 "J4" H 7650 3050 50  0000 C TNN
F 1 "Test Cap" V 7500 2800 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 7650 2575 50  0001 C CNN
F 3 "" H 7625 2800 50  0001 C CNN
	1    7650 2800
	-1   0    0    -1  
$EndComp
$Comp
L D_ALT D3
U 1 1 59021CD5
P 6400 1500
F 0 "D3" H 6400 1600 50  0000 C CNN
F 1 "1N4007" H 6400 1400 50  0000 C CNN
F 2 "Diodes_THT:D_5W_P12.70mm_Horizontal" H 6400 1500 50  0001 C CNN
F 3 "" H 6400 1500 50  0000 C CNN
	1    6400 1500
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D4
U 1 1 59021FD0
P 6900 1850
F 0 "D4" H 6900 1950 50  0000 C CNN
F 1 "1N4007" H 6900 1750 50  0000 C CNN
F 2 "Diodes_THT:D_5W_P12.70mm_Horizontal" H 6900 1850 50  0001 C CNN
F 3 "" H 6900 1850 50  0000 C CNN
	1    6900 1850
	0    1    1    0   
$EndComp
Text HLabel 7850 3150 2    60   Output ~ 0
I_sense
Text HLabel 2200 3250 0    60   Input ~ 0
Discharge
$Comp
L Screw_Terminal_1x02 J5
U 1 1 5902BCCC
P 7650 3500
F 0 "J5" H 7650 3750 50  0000 C TNN
F 1 "Load" V 7500 3500 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 7650 3275 50  0001 C CNN
F 3 "" H 7625 3500 50  0001 C CNN
	1    7650 3500
	-1   0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5902DCF5
P 5500 3650
F 0 "R10" V 5580 3650 50  0000 C CNN
F 1 "10k" V 5500 3650 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5430 3650 50  0001 C CNN
F 3 "" H 5500 3650 50  0001 C CNN
	1    5500 3650
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 59108C19
P 4800 1800
F 0 "R8" V 4880 1800 50  0000 C CNN
F 1 "680" V 4800 1800 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4730 1800 50  0001 C CNN
F 3 "" H 4800 1800 50  0000 C CNN
	1    4800 1800
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 59108C35
P 5200 1750
F 0 "R9" V 5280 1750 50  0000 C CNN
F 1 "22k" V 5200 1750 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5130 1750 50  0001 C CNN
F 3 "" H 5200 1750 50  0000 C CNN
	1    5200 1750
	1    0    0    -1  
$EndComp
Text HLabel 2150 2500 0    60   Input ~ 0
Charge
$Comp
L Jumper_NC_Dual JP1
U 1 1 59121723
P 7200 1050
F 0 "JP1" H 7250 950 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 7200 1150 50  0000 C BNN
F 2 "Connectors:PINHEAD1-3" H 7200 1050 50  0001 C CNN
F 3 "" H 7200 1050 50  0001 C CNN
	1    7200 1050
	1    0    0    -1  
$EndComp
$Comp
L D_ALT D1
U 1 1 591238AF
P 5250 4250
F 0 "D1" H 5250 4350 50  0000 C CNN
F 1 "1N4007" H 5250 4150 50  0000 C CNN
F 2 "Diodes_THT:D_5W_P12.70mm_Horizontal" H 5250 4250 50  0001 C CNN
F 3 "" H 5250 4250 50  0000 C CNN
	1    5250 4250
	-1   0    0    -1  
$EndComp
$Comp
L Jumper_NC_Dual JP2
U 1 1 59124035
P 7800 2050
F 0 "JP2" H 7850 1950 50  0000 L CNN
F 1 "Jumper_NC_Dual" H 7800 2150 50  0000 C BNN
F 2 "Connectors:PINHEAD1-3" H 7800 2050 50  0001 C CNN
F 3 "" H 7800 2050 50  0001 C CNN
	1    7800 2050
	1    0    0    -1  
$EndComp
Text HLabel 2200 4450 0    60   Input ~ 0
Bedini
$Comp
L BC337-40 Q1
U 1 1 5912D561
P 4150 4450
F 0 "Q1" H 4350 4525 50  0000 L CNN
F 1 "BC337-40" H 4350 4450 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 4350 4375 50  0001 L CIN
F 3 "" H 4150 4450 50  0001 L CNN
	1    4150 4450
	1    0    0    -1  
$EndComp
$Comp
L BUX85 Q3
U 1 1 5912EB5A
P 4750 4800
F 0 "Q3" H 5000 4875 50  0000 L CNN
F 1 "BUX85" H 5000 4800 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-220_Vertical" H 5000 4725 50  0001 L CIN
F 3 "" H 4750 4800 50  0001 L CNN
	1    4750 4800
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5912ECAE
P 4250 5000
F 0 "R7" V 4330 5000 50  0000 C CNN
F 1 "1k" V 4250 5000 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4180 5000 50  0001 C CNN
F 3 "" H 4250 5000 50  0001 C CNN
	1    4250 5000
	1    0    0    -1  
$EndComp
Text HLabel 8000 2450 2    60   Output ~ 0
V_cap
$Comp
L MPSA42 Q4
U 1 1 59157162
P 5100 2400
F 0 "Q4" H 5300 2475 50  0000 L CNN
F 1 "MPSA42" H 5300 2400 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 5300 2325 50  0001 L CIN
F 3 "" H 5100 2400 50  0001 L CNN
	1    5100 2400
	1    0    0    -1  
$EndComp
$Comp
L MPSA42 Q2
U 1 1 591571D5
P 4500 2400
F 0 "Q2" H 4700 2475 50  0000 L CNN
F 1 "MPSA42" H 4700 2400 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 4700 2325 50  0001 L CIN
F 3 "" H 4500 2400 50  0001 L CNN
	1    4500 2400
	-1   0    0    -1  
$EndComp
NoConn ~ 7600 1850
$Comp
L L L1
U 1 1 591716BE
P 1400 4100
F 0 "L1" V 1350 4100 50  0000 C CNN
F 1 "10m" V 1475 4100 50  0000 C CNN
F 2 "Choke_Axial_ThroughHole:Choke_Horizontal_RM15mm" H 1400 4100 50  0001 C CNN
F 3 "" H 1400 4100 50  0001 C CNN
	1    1400 4100
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J1
U 1 1 59193F75
P 900 2350
F 0 "J1" H 900 2600 50  0000 C TNN
F 1 "30-300V" V 750 2350 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 900 2125 50  0001 C CNN
F 3 "" H 875 2350 50  0001 C CNN
	1    900  2350
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x02 J2
U 1 1 59194439
P 1000 4900
F 0 "J2" H 1000 5150 50  0000 C TNN
F 1 "12V_Bedini" V 850 4900 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 1000 4675 50  0001 C CNN
F 3 "" H 975 4900 50  0001 C CNN
	1    1000 4900
	1    0    0    -1  
$EndComp
$Sheet
S 2400 2300 1100 400 
U 591C9EED
F0 "ChargeOpto" 60
F1 "OptoDriver.sch" 60
F2 "IN" I L 2400 2500 60 
F3 "OUT_Emitter" I R 3500 2500 60 
F4 "Vss" B R 3500 2350 60 
F5 "Vdd" B R 3500 2650 60 
$EndSheet
$Sheet
S 2400 3050 1100 400 
U 591C9EFF
F0 "DischargeOpto" 60
F1 "OptoDriver.sch" 60
F2 "IN" I L 2400 3250 60 
F3 "OUT_Emitter" I R 3500 3250 60 
F4 "Vss" B R 3500 3100 60 
F5 "Vdd" B R 3500 3400 60 
$EndSheet
$Sheet
S 2400 4250 1100 400 
U 591C9F11
F0 "BediniOpto" 60
F1 "OptoDriver.sch" 60
F2 "IN" I L 2400 4450 60 
F3 "OUT_Emitter" I R 3500 4450 60 
F4 "Vss" B R 3500 4300 60 
F5 "Vdd" B R 3500 4600 60 
$EndSheet
Text Label 1900 3850 0    60   ~ 0
GND_PWR
Text Label 1550 1100 0    60   ~ 0
+300V_PWR
$Comp
L GNDPWR #PWR4
U 1 1 591E44C0
P 1000 4300
F 0 "#PWR4" H 1000 4100 50  0001 C CNN
F 1 "GNDPWR" H 1000 4170 50  0000 C CNN
F 2 "" H 1000 4250 50  0001 C CNN
F 3 "" H 1000 4250 50  0001 C CNN
	1    1000 4300
	1    0    0    -1  
$EndComp
Connection ~ 1400 3850
Wire Wire Line
	1000 3850 6000 3850
Wire Wire Line
	1000 4300 1000 3850
Wire Wire Line
	1400 1100 5200 1100
Connection ~ 3700 2650
Connection ~ 3700 4050
Wire Wire Line
	3700 4300 3700 4050
Wire Wire Line
	3500 4300 3700 4300
Connection ~ 4250 4050
Wire Wire Line
	8500 4050 8500 1050
Wire Wire Line
	8500 1050 7450 1050
Wire Wire Line
	2200 3250 2400 3250
Wire Wire Line
	2400 2500 2150 2500
Wire Wire Line
	5500 3250 3500 3250
Wire Wire Line
	3800 1500 4800 1500
Wire Wire Line
	3800 2500 3800 1500
Wire Wire Line
	3500 2500 3800 2500
Connection ~ 3700 3400
Connection ~ 3700 3850
Wire Wire Line
	3700 2650 3700 3850
Wire Wire Line
	1750 4800 1200 4800
Wire Wire Line
	1750 4050 1750 4800
Wire Wire Line
	1750 4050 8500 4050
Wire Wire Line
	4250 4050 4250 4250
Connection ~ 3700 5250
Wire Wire Line
	3700 4600 3700 5250
Wire Wire Line
	3500 4600 3700 4600
Wire Wire Line
	2400 4450 2200 4450
Wire Wire Line
	3500 4450 3950 4450
Wire Wire Line
	3500 3400 3700 3400
Wire Wire Line
	8350 2050 8350 4250
Wire Wire Line
	8050 2050 8350 2050
Connection ~ 7800 2450
Wire Wire Line
	7250 2450 7250 3400
Wire Wire Line
	7250 2050 7250 1700
Wire Wire Line
	8350 4250 5400 4250
Wire Wire Line
	5100 4250 4850 4250
Wire Wire Line
	1750 5000 1750 5250
Wire Wire Line
	1200 5000 1750 5000
Wire Wire Line
	1400 2250 1400 1100
Wire Wire Line
	1100 2250 1600 2250
Wire Wire Line
	1100 2450 1600 2450
Wire Wire Line
	1400 2450 1400 3950
Wire Wire Line
	4700 2400 4900 2400
Wire Wire Line
	4800 1950 4800 2400
Wire Wire Line
	4800 2050 4400 2050
Wire Wire Line
	4400 2050 4400 2200
Connection ~ 4800 2400
Connection ~ 4800 2050
Wire Wire Line
	5200 2000 5750 2000
Wire Wire Line
	6050 1500 6050 1850
Wire Wire Line
	5200 1500 6250 1500
Connection ~ 5500 1500
Wire Wire Line
	5200 1900 5200 2200
Wire Wire Line
	5500 2000 5500 1900
Connection ~ 5500 2000
Connection ~ 5200 2000
Wire Wire Line
	5500 1500 5500 1600
Wire Wire Line
	5200 1100 5200 1600
Wire Wire Line
	5200 2650 5200 2600
Wire Wire Line
	6050 2350 6700 2350
Wire Wire Line
	6050 2350 6050 2250
Wire Wire Line
	6700 2350 6700 1500
Connection ~ 6700 1500
Connection ~ 6050 1500
Wire Wire Line
	7250 2700 7450 2700
Wire Wire Line
	7250 1700 7350 1700
Wire Wire Line
	7350 2900 7450 2900
Wire Wire Line
	6900 1050 6900 1700
Connection ~ 6900 1500
Wire Wire Line
	6900 2650 6900 2000
Wire Wire Line
	7850 3150 7350 3150
Wire Wire Line
	7350 3150 7350 2900
Wire Wire Line
	7250 3400 7450 3400
Wire Wire Line
	6000 3850 6000 3550
Wire Wire Line
	5500 3400 5700 3400
Wire Wire Line
	5500 3250 5500 3500
Connection ~ 5500 3400
Wire Wire Line
	5500 3850 5500 3800
Wire Wire Line
	6000 3150 6000 2950
Connection ~ 5200 2650
Wire Wire Line
	3500 2650 6900 2650
Connection ~ 5500 3850
Connection ~ 4400 2650
Wire Wire Line
	4800 1500 4800 1650
Connection ~ 5200 1500
Wire Wire Line
	7350 1500 7200 1500
Wire Wire Line
	7200 1500 7200 1150
Wire Wire Line
	6550 1500 6900 1500
Wire Wire Line
	6750 2950 6750 3600
Wire Wire Line
	6000 2950 6750 2950
Wire Wire Line
	7550 2050 7250 2050
Wire Wire Line
	7800 2150 7800 2450
Wire Wire Line
	7250 2450 8000 2450
Wire Wire Line
	6750 3600 7450 3600
Wire Wire Line
	1750 5250 4850 5250
Wire Wire Line
	6950 1050 6900 1050
Connection ~ 7250 2700
Wire Wire Line
	4250 4650 4250 4850
Wire Wire Line
	4250 4800 4550 4800
Connection ~ 4250 4800
Wire Wire Line
	4250 5250 4250 5150
Wire Wire Line
	4850 5250 4850 5000
Connection ~ 4250 5250
Wire Wire Line
	4850 4250 4850 4600
$Comp
L PWR_FLAG #FLG1
U 1 1 59201798
P 1600 2250
F 0 "#FLG1" H 1600 2325 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 2400 50  0000 C CNN
F 2 "" H 1600 2250 50  0001 C CNN
F 3 "" H 1600 2250 50  0001 C CNN
	1    1600 2250
	1    0    0    -1  
$EndComp
Connection ~ 1400 2250
$Comp
L PWR_FLAG #FLG2
U 1 1 592019BF
P 1600 2450
F 0 "#FLG2" H 1600 2525 50  0001 C CNN
F 1 "PWR_FLAG" H 1600 2600 50  0000 C CNN
F 2 "" H 1600 2450 50  0001 C CNN
F 3 "" H 1600 2450 50  0001 C CNN
	1    1600 2450
	1    0    0    -1  
$EndComp
Connection ~ 1400 2450
Wire Wire Line
	4400 2600 4400 2650
Wire Wire Line
	3600 3100 3500 3100
Wire Wire Line
	3600 2350 3600 3100
Wire Wire Line
	3600 2350 3500 2350
$Comp
L GNDD #PWR5
U 1 1 5920A114
P 1400 4300
F 0 "#PWR5" H 1400 4050 50  0001 C CNN
F 1 "GNDD" H 1400 4150 50  0000 C CNN
F 2 "" H 1400 4300 50  0001 C CNN
F 3 "" H 1400 4300 50  0001 C CNN
	1    1400 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4250 1400 4300
$Comp
L +12VA #PWR8
U 1 1 5922F05A
P 3850 2850
F 0 "#PWR8" H 3850 2700 50  0001 C CNN
F 1 "+12VA" H 3850 2990 50  0000 C CNN
F 2 "" H 3850 2850 50  0001 C CNN
F 3 "" H 3850 2850 50  0001 C CNN
	1    3850 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2850 3850 2900
Wire Wire Line
	3850 2900 3600 2900
Connection ~ 3600 2900
Text Label 1250 4800 0    60   ~ 0
Bedini+12V
Text Label 1250 5000 0    60   ~ 0
Bedini_GND
$Comp
L Screw_Terminal_1x02 J11
U 1 1 59271943
P 1000 5950
F 0 "J11" H 1000 6200 50  0000 C TNN
F 1 "12V Opto" V 850 5950 50  0000 C TNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Pheonix_MKDS1.5-2pol" H 1000 5725 50  0001 C CNN
F 3 "" H 975 5950 50  0001 C CNN
	1    1000 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 5850 1900 5850
Wire Wire Line
	1200 6050 1500 6050
$Comp
L PWR_FLAG #FLG3
U 1 1 5927194D
P 1900 5850
F 0 "#FLG3" H 1900 5925 50  0001 C CNN
F 1 "PWR_FLAG" H 1900 6000 50  0000 C CNN
F 2 "" H 1900 5850 50  0001 C CNN
F 3 "" H 1900 5850 50  0001 C CNN
	1    1900 5850
	1    0    0    -1  
$EndComp
Connection ~ 1500 5850
Connection ~ 1500 6050
$Comp
L GNDPWR #PWR7
U 1 1 59272780
P 1500 6050
F 0 "#PWR7" H 1500 5850 50  0001 C CNN
F 1 "GNDPWR" H 1500 5920 50  0000 C CNN
F 2 "" H 1500 6000 50  0001 C CNN
F 3 "" H 1500 6000 50  0001 C CNN
	1    1500 6050
	1    0    0    -1  
$EndComp
$Comp
L +12VA #PWR6
U 1 1 59273311
P 1500 5850
F 0 "#PWR6" H 1500 5700 50  0001 C CNN
F 1 "+12VA" H 1500 5990 50  0000 C CNN
F 2 "" H 1500 5850 50  0001 C CNN
F 3 "" H 1500 5850 50  0001 C CNN
	1    1500 5850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
