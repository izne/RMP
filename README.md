# Really Minimalistic Panel
A minimalistic control panel for MFS20 flight simulator, that can control various panels in the cockpit, such as: COM, NAV, Transponder, FCU, etc.

<img title="The OEM RMP panel on the Airbus A320, image by SIM-on-A320" src="https://sim-on-a320.com/wp-content/uploads/2017/12/RMP_OEM1-768x576.jpg" width="480px">
<img title="The OEM FCU panel on the Airbus A320, image by Soarbywire" src="https://soarbywire.files.wordpress.com/2017/01/l1010492.jpg?w=610" width="480px">

#
## Purpose
To control the various panels within an MFS20 flight simulator. Uses a rotary encoder and two 7-segment displays to dial-in frequencies, altitudes and etc.


#
## Single rotary encoder operation
COM1
To accommodate a single rotary encoder operation, the control logic is designed so that the click of the button is switching between two control modes:
- Mode 1: control of MHz part of the frequency
    - Button click: Switches to Mode 2
- Mode 2: control of KHz part of the frequency
    - Button click: Sends "SWAP" signal and switches to Mode 1

#
## Extending the project
It was quickly obvious that only a radio panel will not be enough. Especially when the screens can be re-used on multiple panels, like NAV, ILS, ADF, DME, FCU, Transponder.
So at least one fork of this could be established on this path of making "universal" device, that can control multiple panels, in a minimalistic way.
For the time being here, lets call this one RMP+ and use if for prototyping.

#
## RMP+ new modes
COM1, (NAV1, Transponder)
A new switch button will toggle between the modes.
An LED indicates (label) in which mode the panel is.

<img title="Minimal code as well" src="/images/rmp_compact.PNG" width="480px">

#
## Two 7-segment displays for "COM1 Active" and "COM1 StandBy" frequencies
Initial setup features two 6-digit 7-segment displays using the TM1637 driver.

## Additional components for FCU mixed mode: ALT, HDG, SPD
As there are still free pins, another display could be attached to be used for the FCU.
In the example, a bigger (0.5") 6-digit 7-segment display is connected. It can be used for showing three different values of main importance on the FCU: Altitude, Speed and Heading values. 
Additional EC11 is to be used to dial and switch between the submodes.

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
## Schematic
Coming soon

#
## AVR Embedded C code
Coming soon

#
## Typical usage
- Power and MCU board
    - Socket for the Arduino Nano board
    - 5V Power line with reservoir and lowpass filter caps
    - Connectors for the control and display board
- Control and display board
    - 7seg1 - 6 digit display that is suited for frequencies (123.455)
    - 7seg2 - another screen to be used in the context of each panel/mode. E.g. Active/Standby freqs, Nav1 and Nav2 freqs, VOR/ILS freqs, etc.
    - Rotary 1 used by the Radionav part of the panel
    - Rotary 1 Button (Switch) e.g. MHz/KHz
    - Rotary 2 used by the FCU part of the panel
    - Rotary 2 Button (FCU Push)
    - Button 1 (Radionav Mode): switches the radio/navigation modes COM, NAV, ILS, XPDR, etc.
    - Button 2 (Radionav Action) Send (Swap the frequencies)
    - Button 3 (FCU Mode): switches independently between FCU values (ALT, HDG, SPD)
    

#
## Dependencies
Libraries for Arduino:

[FlightSimLibrary by Bits&Droids (RMP-mod)](/Bits_and_Droids_flight_sim_library/)

[TM1637_6D by TinyTronics](https://github.com/TinyTronics/TM1637_6D)

[Arduino Encoder Library](https://www.arduinolibraries.info/libraries/encoder)

#
## Connection to MFS20
- Download and install the [Bits&Droids Flight Connector](https://www.bitsanddroids.com/release-notes-1-6-0/)
- Import the [Profile](RMP.json) (or create youself the outputs: Active and Standby COM1 frequencies)
- Connect the Nano to a USB port and configure the device settings before hitting Start
