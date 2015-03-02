#!/usr/bin/python

Vss = 300.0
zener = 12.0
R1 = 22.0

V_open = 5.5

I_R1 = V_open / R1

print "P-kanaal mosfet", V_open, "V opensturen met zener in parallel met", R1,"k weerstand" 
print I_R1, "mA over", R1, "k weerstand bij", V_open, "V"

voedingmin = 30.0

print "Minimale voedingsspanning: ", voedingmin

overR2 = voedingmin - V_open

R2 = overR2 / I_R1

print "R2 dan: ", R2, "k"

R2 = 100.0
print "Neem R2: ", R2, "k"  

MinV = V_open*(R1 + R2)/R1

print "Minimale voedingsspanning dan: ", MinV


overR2 = Vss - zener
I_R2max = overR2 / R2
P_R2 = overR2 * I_R2max
I_R1_zenersp = zener / R1
I_Zener = I_R2max - I_R1_zenersp
P_Zener = zener * I_Zener

print
print "Bij ", Vss, "V dan"
print " {0:.1f} mA door R2    = {1:.1f} mW".format(I_R2max, P_R2)
print " {0:.1f} mA door Zener = {1:.1f} mW".format(I_Zener, P_Zener)


C=100.0
Rds=1.5

RC = Rds*C*1e-6 
print
print "RC =", RC * 1000, "msec", "bij C=", C, "uF en Id=5A, ofwel Vgs= +/- 5.4 V @T=25"

Fco = 1/(2*3.14159*RC)

print "Cutoff frequentie: {0:.1f} kHz.".format(Fco / 1000)




adctime =  104e-6

print
print "Max adc freq", 1/(1000*adctime), "kHz"


print "10 cm of 1mm dia copper has a resistance of about 2 mOhm."
print "That means that 1 amp of current delivers 2 mV of voltage."

print

print "Shunt measured: 20.5 mV by 1.90A, so shunt resistance: 10.8 mOhm."
Rshunt = 10.8e-3

Ipeak = 100.0              # desired maximum current peak
Vi_peak = Ipeak * Rshunt
Vo_in_peak = 11.0          # desired output Voltage at I_peak

G_input_amp = Vo_in_peak / Vi_peak

print "Gain of input Opamp should be about {0:.1f} for {1:.1f} A peak at {2:.1f} V output".format(G_input_amp, Ipeak, Vo_in_peak)

rfb = 100.0  # kOhm
rin = 13.0   # kOhm
G=(rfb/rin) + 1

print "We get a gain of {0:.1f} with R_in={1:.1f} kOhm and R_fb={2:.1f} kOhm".format(G, rin, rfb)

 
print

print "A TL084 has a gain of 100k, so should be enough to amplify 2 mV"
print "to 0.1V, so we can measure up to 50 Amps."
print "That would be a gain of:", 0.1/2e-3
print "And a bandwidth of", 4000/50, "kHz."

print "Take a gain of 51.2"
print "This gives a resolution of", 51.2/512, "Amps when using 10 bits."
print "or", 51.2/128, "Amps when using 8 bits."

print "Gain = R_feedback/R_in + 1"
rin = 9000.0
print "Take R_in: ", rin
G = 51.2

# G=rf/rin + 1
# G rin = rf + rin
rf = G*rin - rin 

print "R_feedback: ", rf
rfp = 47e3
print "Take: ", rfp, "tolerance: ", rfp*.9, rfp*1.1, rfp*.2
print "Adjust with 10k potmeter in series"


print

print "With 2A constant current trough the shunt, we get 160 mV at the"
print "output of the low pass filter."
Vmaxo = 2.5    # V - This is without offset of 2.5 V.
Imaxi = 10.0   # A
Itest = 2.0    # A
Vtest = 160e-3 # V
Vmaxi = Imaxi/Itest * Vtest
print "Maximum input voltage:", Vmaxi, "V for input current of ",Imaxi, "A."

Vadc = 5.0     # V
G = Vadc/(2*Vmaxi)
print "Desired Gain:", G

# Schematic:
# http://www.daycounter.com/Circuits/OpAmp-Level-Shifter/OpAmp-Level-Shifter.phtml
# Calculator:
# http://www.daycounter.com/Calculators/Op-Amp/NonInverting-Op-Amp-Resistor-Calculator.phtml
#
# Input Parameters (Non-Inverting Op-amp)
# Vout            2.5    (V) 
# Gain 	          3.13
# R1              1.6    (KOhms)
# V1 (Input lead)   0    (V) 
# V2              2.5    (V)
# Vp              5.0    (V)
# Vn                0    (V)

R1 = 15e3
R2 = 47e3
R3 = R1
R4 = 47e3

print "Take R1/R3: ", R1/1000, "k"
print "Take    R4: ", R4/1000, "k"

A = (R4/R1) * (R1+R2)/(R3+R4)

print "Gain with calculated resistors: ", A

for R2 in {10e3,47e3, 90e3}:
  A = (R4/R1) * (R1+R2)/(R3+R4)
  print "Gain with R2=", R2/1000, "k :", A
 
