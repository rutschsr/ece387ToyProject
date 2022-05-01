# ECE 387 Individual Final Project
## Overview
This useless box is entirely 3D printed and uses a Arduino Micro (ATMEGA 32U) programmed in C using AVR-GCC and AVRDUDE. 

The operation of the Useless Box toy is very simple ... there are two switches, and when each of them are turned on, an arm emerges from inside the box and turns it back off. Therefore the Useless Box is simply useless.



## Operational Demonstration

[![Img alt text](https://img.youtube.com/vi/gphNHizoBe4/0.jpg)](https://www.youtube.com/watch?v=gphNHizoBe4)

## Operational Overview

The Useless box is a simple toy, and simply turns the switch off when it is turned on by a user. 


## 3D Printed Parts

I designed all of the mechanical parts for the Useless Box in Autodesk Fusion 360. All of the design files are located in this [Folder](https://github.com/rutschsr/ece387ToyProject/tree/main/3-D%20Parts). Each part was "sliced" (split into layers and 3D printer gcode) using [Utlimaker Cura](https://ultimaker.com/software/ultimaker-cura). I then printed each of the pieces on my Creality Ender 3 V2 3D printer using PLA (polyactic acid) filament. Each piece is is hollow and includes between 40 and 60% fill in a triangular manner to reduce print time and increase

![PLA Filament](https://srutschilling.net/ECE387/ToyProject/Images/Filament.JPEG)


### Box Bottom

![Box in Fusion 360](https://srutschilling.net/ECE387/ToyProject/Images/BoxInOctoprint.JPEG)

Box in Autodesk Fusion 360. I exported the drawing to the Utilimaker Cura to slice it before it was printed.

![Box Starting to print](https://srutschilling.net/ECE387/ToyProject/Images/BoxStarting2.JPEG)

A raspberry pi running Octoprint is connected to my printer which provides a web interface to upload drawings and control the printer from. This printer is connected to the raspberry pi using a micro usb cable.

![Complete Bottom of Box on Printer](https://srutschilling.net/ECE387/ToyProject/Images/BottomCompleteOnPrinter.JPEG)

The bottom of the box used nearly the entire print volume of the printer, took approximatley 22 hours to complete, and used approximatley 200g ($4-5) of material.

### Box Top

![Finished Top](https://srutschilling.net/ECE387/ToyProject/Images/TopDoneOnPrinter.JPEG)

The top of the Useless box, still on the printer. The larger holes are where the switches are mounted, and the smaller holes are screw holes.


### Box Door

![Useless box door on printer](https://srutschilling.net/ECE387/ToyProject/Images/DoorOnPrinter.jpg)

The box with hinge mounts on the printer. The raised area on the bottom was originally planned to be a rubber band mount to close the door, but this was not necessary as the door closes by itself.

### Servo Mount

![Original Small Servo Mount](https://srutschilling.net/ECE387/ToyProject/Images/SmallServoMounted.JPEG)

The original small servo mount with a servo motor. This motor did not have enough torque and was replaced with a larger motor. The design of the Servo mount stayed the same design but was slightly larger.

### Servo Arm
![Brackets and Arms Printing](https://srutschilling.net/ECE387/ToyProject/Images/BracketsAndArmsPrinting2.JPEG)

The brackets and arms also took some trial and error to get correct. The larger servo motors meant that the arms had to be offset to turn off the switches as the box was not wide enough. This was the only real design change with the arm. I used screws to attach the arm to a mount that came with the servo. This just relies on friction between the gears to stay.

## Assembly

![Servo Motors inside Box](https://srutschilling.net/ECE387/ToyProject/Images/ArmsInside5.JPEG)

Servo Motors mounted inside The Box with switches and offset arms installed. From this view the width of the servo motors and box that required the arms to offset can be seen.

![Assembled Box](https://srutschilling.net/ECE387/ToyProject/Images/AssembledBox2.JPEG)

Assembled box with the door open.

## Wiring and Connections
![Useless Box Schematic Diagram](https://srutschilling.net/ECE387/ToyProject/Images/FinalProjectSchematic.png)
Above is the Schematic Diagram showing the connections for the Useless Box.

My Useless Box accepts a 5-7 V input on either the VIN jack on the outside of the box near the power switch, or the internal battery box which holds four AA batteries.

Internally, the servo motors are powered directly from the VIN port with no voltage regulation and this is why the input is limited to 7 volts. The Arduino Micro is then powered through its VIN pin. On the Arduino two digital input pins are used for the switches, and two PWM pins are used to control the servos. The wiring is very simple, with the only components being the servo motors, the switches, and bleed resistors for the switches.

![Soldering perf board in progress](https://srutschilling.net/ECE387/ToyProject/Images/SolderingPerfBoard.JPEG)

All of the connections are soldered or socketed to improve the reliability. I used a solder perfboard to attach all of the components and header pins for the Arduino and Servo motors.

![Arduino Micro on PerfBoard](https://srutschilling.net/ECE387/ToyProject/Images/ArduinoMicroInsideBox.jpg)

The Servo headers are on the bottom left of the perfboard, while the black 4 wire cable goes to the switches mounted on the top of the box. After I soldered the components on to the perfboard I used hotglue on all connections to ensure the wires do not break off at their connections.

## Issues

There were several issues and design changes while building the Useless Box. The first was my original choice in servo motor was very small 9g servo motors. After adding a large arm to be able to turn of the switch, these 



## Arduino Programming

## C code



## Power Reduction Techniques:
As this project can be battery powered, power reduction techniques are necessary to ensure a long battery life. The useless box can be powered by 4AA batteries in a battery case that is under the useless box door. The box's ATMEGA A32U microcontroller - integrated into the Arduino Micro, is programmed using baremetal C in order to reduce the overhead and power consumption. This also uses direct manipulation of counters for PWM control so any overhead required by the Arduino libraries was eliminated. The battery life is still quite poor however, as the Servo motors can draw approximately 1 amp each under load. When operating under battery power, the AA batteries cannot output 2A for a long period of time, so battery life is poor.

## Improvements:
As with any project, by the time it was finished there were several things that I would do differently or improve if I were to do the project again. One of these improvements would be further improving the power consumption. Even with the power reduction techniques described above the power consumption and battery life are still rather poor. One easy power reduction technique I would employ if starting again is controlling the power to the servo motors using a MOSFET, so they would only have power when they are active and have a reason to be moving. Another power reduction technique I would have employed is using interrupts for the switch control, so the microcontroller could be in a ultra low power state when niether of the servos are moving. Finally instead of using the Arduino micro with the ATMEGA 32U microcontroller, I likely would use a bare ATMEGA A328P for the better packaging and power consumption.

Other power improvments for the box could include a rechargable battery system. A rechargable lithium battery could be implemented into the system power it for longer periods of time. This also could be implemented with a USB power source to easier find a power source versus the DC barrel jack on the current Useless Box. As a sidenote, the barrel jack is necessary without a permanant onboard battery due to the high power requirements of the servos that a USB power supply (especially a computer) cannot support.

Mechanical improvements I would make if I were starting again would be to design the bottom of the box with the servo mounts intergrated. This would increase the servo mounts structual integrity, would reduce their movement, and remove the need for the hot glue I added to keep the motors from moving. I also would use screws to mount the servo "arms" to the servo motors instead of relying on friction of the gears to work. While designing the initial bottom of the box I should have also considered the motion of the door opening so that I would not have had to knotch the door on the sides to let it open. This was the first project I had completed with 3-D printed parts and Fusion 360, so it was a learning expierence both with the 3-D design software and my 3-D printer.

## More Information:

Additional Documentation found at: https://srutschilling.net/ECE387/ToyProject/

(Site will be undergoing maintenance between May 15-June 1 2022)


Additional help with PWM on ATMEGA 32U from: https://extremeelectronics.co.in/avr-tutorials/servo-motor-control-by-using-avr-atmega32-microcontroller/