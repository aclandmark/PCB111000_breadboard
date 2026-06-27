
#define F_CPU 8000000UL 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <util/delay.h>


#include "../../328_Bootloader_resources\Bootloader_header.h"
#include "../../328_Bootloader_resources\Bootloader_SW_subs.c"
#include "../../328_Bootloader_resources\Basic_IO_subroutines.c"