# Radio Management Panel
A minimalistic control panel for MFS20 flight simulators, functionally resembling the RMP of Airbus A320 aircraft.

<img title="The OEM RMP panel on the Airbus A320" src="https://sim-on-a320.com/wp-content/uploads/2017/12/RMP_OEM1-768x576.jpg" width="70%">

#
## Purpose
To control the radio panels within a flight simulator, using a rotary encoder and two 7-segment displays for Active and Standby frequencies (COM1-only at this time).


#
## Single rotary encoder operation
To accommodate a single rotary encoder operation, the control logic is designed so that the click of the button is switching between two control modes:
- Mode 1: control of MHz part of the frequency
    - Button logic: Switch to Mode 2
- Mode 2: control of KHz part of the frequency
    - Button logic: Send "SWAP" signal and go back to Mode 1


#
## Video demonstration
[![Watch on Youtube](https://img.youtube.com/vi/Up-8f32O-Tk/0.jpg)](https://www.youtube.com/watch?v=Up-8f32O-Tk)

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
- Get the [Bits&Droids Flight Connector ](https://www.bitsanddroids.com/release-notes-1-6-0/)
- Create(/import) the Profile (Active and Standby COM1 freqs)
- Connect the RMP device to a USB port
- Configure the device settings (PORT and Board)
- Start MFS20, wait for MFS20 and WASM indicators to turn "green"
- Press "Start" and observe "Boards" indicator to turn "green"
