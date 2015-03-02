#!/usr/bin/python

import math

# kijken naar de joules per puls van Bedini -> levert weinig op. Alleen
# Amps.
# Ga uit van normale energie berekeningen. Stel, we willen een
# condensator van 1000 uF opladen tot 40V, met een condensator van 10 uF
# op 200V. Hoe lang duurt dat en hoeveel stroom trekken we?


# En we hebben te maken met energieverlies:

# http://www.smpstech.com/charge.htm

# Figure 1 (a) shows a capacitor C1 charged to voltage Vi and no voltage
# on capacitor C2 before switch closure. C1 is equal to C2 and the
# energy in the system is:
# 
# Energy = (C1*V1^2)/2
# 
# After switch closure (b), the charge and voltage is divided equally
# between the two capacitors (conservation of charge) and the total energy
# in the system is:
# 
# Energy = (C1*(V1/2)^2)/2 + (C2*(V2/2)^2)/2 = (C1*V1^2)/4


# So, we need TWO buck converters, one for charging the dump cap and one
# for dumping the cap into the EUT. ^_^
# From the same source:

# A rule of thumb, which we will use later for selecting a value of
# inductance in an LC filter, is to start with an inductor value that
# results in a peak-to-peak inductor current that is 10% of the full load
# current. For our example of a 12 V input, 5 V output, 20 A load, and 20
# kHz switching frequency, the inductor can be calculated from the formula
# V = L*(di/dt). This is a formula you will constantly use in
# switching-mode power supply design, hence worth memorizing.
# 
# Example:
# L = V*Ton/I
# V = 12 V - 5 V = 7 V
# Ton = D*T = 0.417*50E-6 = 20.85E-6
# I = 20 A * 10% = 2 A
# L = (7 V)*(20.85E-6 s)/(2 A) = 72.3 uH
# => 75 uH
# 
# The resulting two amps (1.94 A) peak-to-peak ripple current gives about
# a half volt peak-to-peak ripple current in the 5 V, 20 A load. Note that
# you can decrease the ripple current to as small as you want by
# increasing L, or make L smaller by allowing more ripple current.

# -------
# Let's start with following this guide and design a buck converter from
# 200V to 30V, outputting 100W and a switch frequency of 1 kHz:

print "Design parameters"
Vin     =  200.0 # Vdc
Vout    =   12.0 # Vdc
Pin     =  30.0  # W  -> more than enough for charging caps
Fswitch = 1000.0 # Hz 

print "Vin       : {0:.1f} V".format(Vin)
print "Vout      : {0:.1f} V".format(Vout)
print "Pin       : {0:.1f} W".format(Pin)
print "Fswitch   : {0:.1f} Hz".format(Fswitch)

print "------"

Duty = Vout/Vin
print "Duty      : {0:.3f}".format(Duty)

VoutRms = Vin * math.sqrt(Duty)
print "Vout RMS  : {0:.1f} V".format(VoutRms)

Iavg_in = Pin / Vin
print "Avg I inp : {0:.1f} A".format(Iavg_in)

Iavg_out = Pin / Vout
print "Avg I out : {0:.1f} A".format(Iavg_out)

Ctest = 30000 # uF
print "This charges a {0:.1f} uF capacitor in 1 sec to {1:.1f} V.".format(Ctest, (Iavg_out * 1) / (Ctest*1e-6)) 



Rload = Duty * Vin / Iavg_in
print "Rload     : {0:.1f} Ohm".format(Rload)

# A rule of thumb, which we will use later for selecting a value of
# inductance in an LC filter, is to start with an inductor value that
# results in a peak-to-peak inductor current that is 10% of the full
# load current. For our example of a 12 V input, 5 V output, 20 A load,
# and 20 kHz switching frequency, the inductor can be calculated from
# the formula V = L*(di/dt). This is a formula you will constantly use
# in switching-mode power supply design, hence worth memorizing.
# 
# Example:
# L = V*Ton/I
# V = 12 V - 5 V = 7 V
# Ton = D*T = 0.417*50E-6 = 20.85E-6
# I = 20 A * 10% = 2 A
# L = (7 V)*(20.85E-6 s)/(2 A) = 72.3 uH
# => 75 uH

# Bedini advanced handbook, page 30:
#
# "While this discharge rises to a height on the scope of 6 divisions,
# its total width is quite narrow, and its duration is expended in
# approximately 16 milliseconds (0.016 seconds)."
#
# This is at a frequency of 2.183 Hz.


# IXTP10P50P allows 30A peak current.

Vcoil = Vin - Vout
print "Vcoil     : {0:.1f} V".format(Vcoil)

Ton   = Duty * 1.0/Fswitch
print "Ton       : {0:.1f} us".format(Ton*1e6)

Il    = 20.0
#Il    = 0.3
L     = Vcoil * Ton/Il

print "L         : {0:.1f} uH".format(L*1e6)


# Ringcore Conrad: R 58 N30. In Mini Ringcore Calculator under SIFFERIT.
#  1 turn : 5.4   uH
#  2 turns: 21.6  uH
#  5 turns: 135   uH
# 10 turns: 520   uH
# 14 turns: 1.058 mH
# 15 turns: 1.215 mH
# 20 turns: 2.160 mH

#calc:
#for i in range(1,30):
#  print "#", i, "turns :",5.4*i*i, "uH"

# 1 turns : 5.4 uH
# 2 turns : 21.6 uH
# 3 turns : 48.6 uH
# 4 turns : 86.4 uH
# 5 turns : 135.0 uH
# 6 turns : 194.4 uH
# 7 turns : 264.6 uH
# 8 turns : 345.6 uH
# 9 turns : 437.4 uH
# 10 turns : 540.0 uH
# 11 turns : 653.4 uH
# 12 turns : 777.6 uH
# 13 turns : 912.6 uH
# 14 turns : 1058.4 uH
# 15 turns : 1215.0 uH
# 16 turns : 1382.4 uH
# 17 turns : 1560.6 uH
# 18 turns : 1749.6 uH
# 19 turns : 1949.4 uH
# 20 turns : 2160.0 uH
# 21 turns : 2381.4 uH
# 22 turns : 2613.6 uH
# 23 turns : 2856.6 uH
# 24 turns : 3110.4 uH
# 25 turns : 3375.0 uH
# 26 turns : 3650.4 uH
# 27 turns : 3936.6 uH
# 28 turns : 4233.6 uH
# 29 turns : 4541.4 uH

print "For R 58 N30, take 14 turns to get 1.058 mH"
print "This takes 82 cm of wire, with max 7.14 mm dia"
print "and gives reactance XL=6.648 Ohm @ 1 kHz, which is 2 pi f L" 
print "A 1 mH coil resonates with 25 uF @ 1 kHz."


# Magnet wire we have is just over 1.0 mm diameter. Resistance should be
# 22.282 mOhm per meter. This would be AWG 18. This has the following
# props:
#
# http://diyaudioprojects.com/Technical/American-Wire-Gauge/
#
# AWG 	                     : 18
# Diameter [mm] 	     : 1.02362
# Area [mm2]                 : 0.823
# Resistance [mOhms / m]     : 20.9428
# Max Current [Amperes]      : 2.3
# Max F for 100% skin depth  : 17 kHz


# Other magnet wire (from Courtiestown) we have is about .8 mm diameter.
# Resistance should be 33.727 mOhm per meter. This would be AWG 20. This
# has the following props:
#
# http://diyaudioprojects.com/Technical/American-Wire-Gauge/
#
# AWG 	                     : 20
# Diameter [mm] 	     : 0.8128
# Area [mm2]                 : 0.518
# Resistance [mOhms / m]     : 33.292
# Max Current [Amperes]      : 1.5
# Max F for 100% skin depth  : 27 kHz
#
# "Current (ampacity) Notes: The current ratings shown in the table are
# for power transmission and have been determined using the rule of 1
# amp per 700 circular mils, which is a very conservative rating."
#
# Judging from the ratings given by NEC for 14 AWG @ 30 degrees
# Centigrade, 3.8A (continous) should be no problem with AWG 20 "as part
# of a three conductor cable". 


# Old Ferrite core inductor adjustable between  8.6 and 169 uH with
# inner winding. Outer winding between 8.8 and 127 uH. In series between
# 31 and 608 uH.
# Outer winding: 51 turns, 310 cm wire length (including leads)
# Inner winding: 59 turms, 280 cm wire length.
#
# Variac adjustable from 5.5 uH up to much more than 2 mH.

# New coil with AWG20 wire.
# Layer 1: 36 turns. Adjustable between 16 and 87 uH.
# Layer 2: 40 turns. Adjustable between 51.5 and 370 uH.
# Layer 3: 37 turns. Adjustable between 125 and 832 uH.
# Layer 4: 35 turns. Adjustable between 214 and 1.4 mH.



#uHperN2_1 = 608.0 / (110.0*110.0)
turns=36
uHperN2_1 = 87.0 / (turns*turns)
turns+=40
uHperN2_2 = 370.0 / (turns*turns)
turns+=37
uHperN2_3 = 832.0 / (turns*turns)

#print turns
#calc:
#for i in range(1,200):
#  print "#", i, "turns :",uHperN2_1*i*i,uHperN2_2*i*i,uHperN2_3*i*i, "uH"


# New coil: 33 +33 + 32 + 31 turns in 4 layers.
# 179 uH - 1.3 mH

# Spice simulation with 500u L and 1000u charge cap C1, 1000 Hz
# After the first pulse, settling voltage on C1, varying C2:
#    C2 peak1  settle  IL,max
#    1u 0.67V   3.12V   21.4A
#   10u 2.93V   3.15V   17.6A
#   50u 3.25V   2.20V    5.8A
#  100u 2.27V   2.21V    3.3A
# 1000u 2.3V    2.23V    0.4A


# Opamps:  TL072, 2x TL074, TL082, TL084, LTC1049, LM324N

# TL072,TL074: Low-Noise JFET-Input General-Purpose Operational
# Amplifier.  dual/quad opamp,  Vcc: +/- 2-15V, GBW: min 2, typ 3 MHz.
#
# TL082 Wide Bandwidth Dual JFET Input Operational Amplifier. Vcc: +/-
# 6-15 V. GBW: 4 MHz.
#
# TL072 is sold as low noise version for audio apps.  TL082 is sold as
# device having best settling time for instrumentation/industrial apps
# TL072 aimed at audio apps, including pre-amps
# TL082 aimed at industrial apps: Filtering, Amplification, Precision
# rectification, Peak detectors, Sample and holds

# LTC1049: Low Power Zero-Drift Operational Amplifier with Internal
# Capacitors. Single Supply Operation: 4.75V to 16V
# The LTC 1049 is a high performance, low power zero-drift operational
# amplifier. The two sample-and-hold capacitors usually required
# externally by other chopper stabilized amplifiers are integrated on
# the chip. Further, the LTC1049 offers superior DC and AC performance
# with a nominal supply current of only 200 uA. The LTC1049 has a
# typical offset voltage of 2 uV, drift of 0.02 uV/degrC, 0.1Hz to 10Hz
# input noise voltage of 3 uV P-P and typical voltage gain of 160dB.
# The slew rate is 0.8V/us with a gain bandwidth product of 0.8MHz.

# LM324: Single Supply Quad Operational Amplifiers


# TDA2640: Switched mode PS IC
# TDA1012: Single Channel 2W Audio Power Amplifier 


print 'opamp filter'
print "Since we will sample at 250-500 Hz, we take f_c at 100 Hz"

# http://astro.u-strasbg.fr/~koppen/radio/Activee.html

print "We take the capacitors all 100n"
print "Then, R1=11k7, R2=10k74, R3=16k11, R4=6k21"
print "With E12, 10% tolerance, we get:"
print "R1=12k, R2=10k, R3=15k, R4=6k8"
