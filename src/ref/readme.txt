Sam Rutschilling
Lab 3: 
ECE 387 Spring 2022
Miami University

Febuary 10,2022



Youtube Demonstration of working project:
https://youtu.be/_FFq0tg9W6I


The Arduino was programmed using modified compile_script on Linux Virtual Machine (slight changes
to change \ to / and remove .exe in avrdude. The script will likely not work completley correctly for Windows machines.

The Com port passed to my Linux Virtual Machine by VMWARE Workstation is defined as /dev/ttyACM0, this is used for programming.
This was also used using the USART library for serial communication while trying to debug.

running the command "python compile_script.py 4" compiles the program and uploads it to the arduino using /dev/ttyACM0.

Additional files and compiled files can be removed then using the command "python compile_script.py 0" This is equivalent to "clean" in Visual Studio.

Also added to the program were Design by contract Pre and Post proccessor functions. The preprocessor functions for the stoplight function were tested in a video linked below.
For this video one of the function calls explicitly calls for two of the lights to be on, this causes the pin 13 led to light up and the program to be in a DBC error state. This
DBC pre function uses Exculsive OR call. PRE and POST DBC functions turn on PIN13 (the built in Arduino LED) if they fail. This tells the user/programmer that an error occured. POST_ errors turn
the LED on for half of the time that PRE_ issues do so that differentiates which function failed. This is helpful for debugging. The compiled program will be smaller and will execute faster without DBC functions
Included. Since they are handled using preprocessor directives it should make no difference to fully remove them as the preprocessor and compiler will ignore them and not compile them if they are turned off. Similarly,
in C++ I have used #If 0 preprocessor directives to turn off complete blocks of code, since they are turned off by preprocessor directives they will be ignored at the preprocessing stage and not handled by the compiler.

Link of DBC Error Video:
https://youtu.be/MKCNsZm0w2o


A Pull down resistor (large value 4K+ Ohm) is necessary for an input button on the arduino. This keeps the input pin grounded and from "floating" if the button is not pushed and the value is not high. This will keep
unexpected results from occuring where the arduino reads the input as high when the button was not pushed.