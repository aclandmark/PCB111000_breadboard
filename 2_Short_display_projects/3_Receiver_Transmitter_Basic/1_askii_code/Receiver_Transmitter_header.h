

#include <avr/wdt.h>

char watch_dog_reset;
char User_response;

#define T0_delay_10ms   5,178

#define setup_HW \
setup_watchdog;\
ADMUX |= (1 << REFS0);\
OSC_CAL;\
Set_display_drivers;\
Clear_segments;\
Clear_digits;\
set_up_switched_inputs;\
set_up_unused_IO;\
setup_PC_comms_Basic(0,16);\
Timer_T0_10mS_delay_x_m(10);



/***************************************************************/
#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}



/***************************************************************/
#define Set_display_drivers \
DDRB = (1 << DDB0) |  (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);\
DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);\
DDRD = (1 << DDD2) | (1 << DDD6) | (1 << DDD7);



/********************************************************/
#define a_off   PORTD |= (1 << PD6);
#define a_on  PORTD &= (~(1 << PD6));

#define b_off   PORTB |= (1 << PB0);
#define b_on  PORTB &= (~(1 << PB0));

#define c_off   PORTB |= (1 << PB3);
#define c_on  PORTB &= (~(1 << PB3));

#define d_off   PORTB |= (1 << PB5);
#define d_on  PORTB &= (~(1 << PB5));

#define e_off   PORTC |= (1 << PC0);
#define e_on  PORTC &= (~(1 << PC0));

#define f_off   PORTD |= (1 << PD7);
#define f_on  PORTD &= (~(1 << PD7));

#define g_off   PORTB |= (1 << PB2);
#define g_on  PORTB &= (~(1 << PB2));

#define dp_off   PORTB |= (1 << PB4);
#define dp_on  PORTB &= (~(1 << PB4));



/********************************************************/
#define digit_4_LH_on  PORTC |= (1 << PC1);
#define digit_4_LH_off  PORTC &= (~(1 << PC1));

#define digit_3_LH_on  PORTC |= (1 << PC2);
#define digit_3_LH_off  PORTC &= (~(1 << PC2));

#define digit_2_LH_on  PORTC |= (1 << PC3);
#define digit_2_LH_off  PORTC &= (~(1 << PC3));

#define digit_1_LH_on  PORTD |= (1 << PD2);
#define digit_1_LH_off  PORTD &= (~(1 << PD2));



/********************************************************/
#define Clear_segments    a_off;b_off;c_off;d_off;e_off;f_off;g_off;dp_off;
#define Clear_digits \
digit_1_LH_off;digit_2_LH_off;digit_3_LH_off;digit_4_LH_off;



/***************************************************************/
#define set_up_switched_inputs \
MCUCR &= (~(1 << PUD));\
DDRC &= (~(1 << PC5));\
PORTC |= (1 << PC5);



/***************************************************************/
#define set_up_unused_IO \
DDRD &= (~((1 << PD3) | (1 << PD4) | (1 << PD5)));\
PORTD |= ((1 << PD3) | (1 << PD4) | (1 << PD5));\
DDRB &= (~(1 << PB1));\
PORTB |= (1 << PB1);



/***************************************************************/
#define switch_3_down ((PINC & 0x20)^0x20)
#define switch_3_up   (PINC & 0x20)



/***************************************************************/
#define first_run_after_programming   !(eeprom_read_byte((uint8_t*)0x1FA))
#define clear_programmer              eeprom_write_byte((uint8_t*)0x1FA, 0xFF);



/***************************************************************/
#define User_prompt_Basic \
while(1){\
do{String_to_PC_Basic("R?    ");}  while((isCharavailable_Basic (50) == 0));\
User_response = Char_from_PC_Basic();\
if((User_response == 'R') || (User_response == 'r'))break;} String_to_PC_Basic("\r\n");

/***********************************************************************************************/
#define OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FE) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FE) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FE)\
== eeprom_read_byte((uint8_t*)0x3FF))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}


/*****************************************************************************/
#include "328_Resources/Subroutines/HW_timers.c"
#include "328_Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "328_Resources/Subroutines/Random_and_prime_nos.c"



/*********************************************************************************/
