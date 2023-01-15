# Radio Management Panel
A minimalistic control panel for MFS20 flight simulators, functionally resembling the RMP of Airbus A320 aircraft.

<img title="The OEM RMP panel on the Airbus A320, image by SIM-on-A320" src="https://sim-on-a320.com/wp-content/uploads/2017/12/RMP_OEM1-768x576.jpg" width="480px">

#
## Purpose
To control the COM1 radio panel within a flight simulator.  Uses a rotary encoder and two 7-segment displays for Active and Standby frequencies.


#
## Single rotary encoder operation
To accommodate a single rotary encoder operation, the control logic is designed so that the click of the button is switching between two control modes:
- Mode 1: control of MHz part of the frequency
    - Button click: Switches to Mode 2
- Mode 2: control of KHz part of the frequency
    - Button click: Sends "SWAP" signal and switches to Mode 1


#
## Demonstration
[![Watch on Youtube](https://img.youtube.com/vi/cJvjje6fKA4/0.jpg)](https://www.youtube.com/watch?v=cJvjje6fKA4)

#
## Components
- 2x [TM1637](https://www.rlocman.ru/i/File/2020/04/03/Datasheet_TM1637.pdf), 6-digit, 7-segment display, orange backlight
- [EC11 Rotary encoder](https://www.farnell.com/datasheets/1837001.pdf)
- [Arduino Nano](https://store.arduino.cc/products/arduino-nano)
- Filter capacitors on the 5V rail:
    - 100uF Electrolytic
    - 10nF Polypropylene

#
## Dependencies
Libraries for Arduino:

[FlightSimLibrary by Bits&Droids](https://github.com/BitsAndDroids/BitsAndDroidsFlightSimLibrary)

[TM1637_6D by TinyTronics](https://github.com/TinyTronics/TM1637_6D)

[Arduino Encoder Library](https://www.arduinolibraries.info/libraries/encoder)

#
## Connection to MFS20
- Download and install the [Bits&Droids Flight Connector](https://www.bitsanddroids.com/release-notes-1-6-0/)
- Import the [Profile](RMP.json) (or create youself the outputs: Active and Standby COM1 frequencies)
- Connect the Nano to a USB port and configure the device settings before hitting Start
