This is a virtual prototype project to control a 3D printer from a panel with the Arduino I2C communication channel. 

The project provides for the sending of some commands to the printer by pressing the keys on the panel connected to Arduino which in turn reacts to the printer status by showing the current status with LED and LCD, through I2C connection.

The first Arduino (ARD1) simulates the functions of the printer (the programming part of the Marlin firmware still have to do it), in the realization it will be Marlin to interact with the second Arduino (ARD2).

From the change I expect to have more memory and pins available to add functions, sensors or other to the 3D printer.

It is however a base to make two arduino work connected with I2C.

test link:
https://www.youtube.com/watch?v=FTpn1qINlrs
