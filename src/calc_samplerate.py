#!/usr/bin/env python

# Variables from pru.c
clock_divider   = 1
open_delay      = 0
sample_delay    = 0
average         = 0
channels        = 2
idlestep        = 2  # cannot be disabled, appears to take 2 clock cycles

clock = 24000000

cyclespersample = (average+1)*(14+open_delay+sample_delay)
print cyclespersample, "ADC clock cycles per sample needed."

totalcycles     = idlestep + channels*cyclespersample
print totalcycles, "total cycles needed, including idle step"

fs = clock / (clock_divider*totalcycles)

print fs/1000, "kS/s per channel"
print
print "For two channels at max speed, measured result is about 800 kS/s"
print
print "Measured results, 10 and 20 minutes running:"
print "Final buffer_count: 955114752 "
print "Freq: 781.894252 "
print "kS/sSampling took 600.003836 sec."
print "Sampling rate 1591.847743 kS/s (795.923871 kS/s per chan)."
print 
print "Final buffer_count: 1913951232 "
print "Freq: 783.324942 "
print "kS/sSampling took 1200.003777 sec."
print "Sampling rate 1594.954340 kS/s (797.477170 kS/s per chan)."

