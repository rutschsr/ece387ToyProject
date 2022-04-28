# ECE 387 Individual Final Project
## Overview
This useless box is entirely 3D printed and uses a Arduino Micro (ATMEGA 32U) programmed in C using AVR-GCC and AVRDUDE. 

The operation of the Useless Box toy is very simple ... there are two switches, and when each of them are turned on, an arm emerges from inside the box and turns it back off. Therefore the Useless Box is simply useless.



## Operational Demonstration

[![Img alt text](https://img.youtube.com/vi/gphNHizoBe4/0.jpg)](https://www.youtube.com/watch?v=gphNHizoBe4)


## 3D Printed Parts

## Wiring and Connections
![alt text](https://srutschilling.net/ECE387/ToyProject/Images/FinalProjectSchematic.png)
Above is the Schematic Diagram showing the connections for the Useless Box.

My Useless Box accepts a 5-7 V input on either the VIN jack on the outside of the box near the power switch, or the internal battery box which holds four AA batteries.

Internally, the servo motors are powered directly from the VIN port with no voltage regulation and this is why the input is limited to 7 volts. The Arduino Micro is then powered through its VIN pin. On the Arduino two digital input pins are used for the switches, and two PWM pins are used to control the servos.   



## Arduino Programming

## C code



# Power Reduction Techniques:
As this project can be battery powered, power reduction techniques are necessary to ensure a long battery life. The useless box can be powered by 4AA batteries in a battery case that is under the useless box door. The box's ATMEGA 

Additional Documentation found at: https://srutschilling.net/ECE387/ToyProject/

Additional help with PWM on ATMEGA 32U from: https://extremeelectronics.co.in/avr-tutorials/servo-motor-control-by-using-avr-atmega32-microcontroller/