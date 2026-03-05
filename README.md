# PCB111000_breadboard
Atmega168 with bootloader
PCB111000_UNO_V2 has a bootloader that runs on the Atmega 328 (UNO) device.
It is used to upload user programs.
All non essential features such as the text programmer have been removed and
it has been possible to fit the resulting code into the boot partition of an Atmega 168.

This Atmega 168 can now be plugged into breadboard along with a USB bridge (CP2102 module).
Other components such as a 4 four digit 7 segment dispay, leds, piezzo sounder, analogue voltage source etc. 
can then be added.  Simple projects can now be developed using the most basic and cheepest hardware and
experience in C programming readily gained.

The development environment is provided by Arduino used together with the Br@y++ terrminal program. 
The bootloader is slightly different from the one provided by Arduino.  It does not require and external resonator
but runs off its internal RC clock. This clock is calibrated when the bootloader is uploaded using a UNO pcb loaded with 
preograming code.
