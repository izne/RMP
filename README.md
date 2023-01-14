# Radio Management Panel
A minimalistic control panel for flight simulators, mimicking the RMP on A320

#
## Purpose
To control the radio panels within a flight simulator, using a rotary encoder and two 7-segment displays for Active and Standby frequencies (COM1-only at this time).


#
## Single rotary encoder operation
To accommodate single rotary encoder operation, the control logic is simplified so that the click of the button has two modes:
- Mode 1: control of MHz part of the frequency
    - Button logic: Switch to Mode 2
- Mode 2: control of KHz part of the frequency
    - Button logic: Send "SWAP" signal and go back to Mode 1


#
## Components
- 2x TM1637, 6-digit, 7-segment display, orange backlight
- EC11 Rotary encoder
- Arduino nano


#
## Dependencies
Libraries for Arduino:

[FlightSimLibrary by Bits&Droids](https://github.com/BitsAndDroids/BitsAndDroidsFlightSimLibrary)

[TM1637_6D by TinyTronics](https://github.com/TinyTronics/TM1637_6D)

[Encoder Library](https://www.arduinolibraries.info/libraries/encoder)

