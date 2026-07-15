

#include <avr/wdt.h>

char User_response;
char watch_dog_reset;
unsigned int PRN;
unsigned char PRN_counter;

#define T0_delay_10ms   5,178

#define setup_HW \
setup_watchdog;\
ADMUX |= (1 << REFS0);\
OSC_CAL;\
Set_display_drivers;\
Clear_segments;\
Clear_digits;\
setup_PC_comms_Basic(0,16);\
Timer_T0_10mS_delay_x_m(5);


#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}

#define Set_display_drivers \
DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);\
DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);\
DDRD = (1 << DDD2) |(1 << DDD3) |(1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);


/***********************************************************************************************/
#define User_prompt_Basic \
while(1){\
do{String_to_PC_Basic("R?    ");}  while((isCharavailable_Basic (50) == 0));\
User_response = Char_from_PC_Basic();\
if((User_response == 'R') || (User_response == 'r'))break;} String_to_PC_Basic("\r\n");



/***********************************************************************************************/
#define OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x1FE) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x1FE) < 0xF0) && (eeprom_read_byte((uint8_t*)0x1FE)\
== eeprom_read_byte((uint8_t*)0x1FF))) {OSCCAL = eeprom_read_byte((uint8_t*)0x1FE);}




/*****************************************************************************/
#include "Resources/Subroutines/HW_timers.c"
#include "Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "Resources/Subroutines/Random_and_prime_nos.c"



/********************************************************************************/
