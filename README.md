# SoakageTester
Hard and software for studying dielectric absorption aka "soakage" in electrolytic capacitors and/or batteries

# Intro

This is a capacitor/battery pulsed charge-discharge cycle tester, as
part of a project to investigate the theory that the well known
"capacitor soakage" or "battery action" effect observed with
electrolytic capacitors can be enhanced using pulsed charging, as
demonstrated by John Bedini et al for years.

The hardware consists of:

1) An adjustable power supply, 0-300V;
2) Pulse charge circuitry, steered by a BeagleBone, using a MOSFET;
3) Current measurement circuitry, using a shunt, some opamps to amplify
the input signal, implement a low pass filter, etc.
4) Voltage measurement circuitry.

Both the current en voltage measurements are done by the BeagleBone using
it's analog inputs and it's ADC. 

Based on [small-scope](https://hackaday.io/project/5881-small-scope) by Marvin Sinister.



