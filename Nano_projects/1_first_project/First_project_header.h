//#define F_CPU 8000000 Generates conflist with UNO compiler


#include <avr/wdt.h>

char watch_dog_reset;
char power_on_reset;
char User_response;
char r_prompt;

unsigned int PRN;
unsigned char PRN_counter;

#define T0_delay_10ms   5,178

void Char_to_PC_Local(char);



/*****************************************************************************/
#define SW_reset                     {eeprom_write_byte((uint8_t*)(0x3EF),0);wdt_enable(WDTO_30MS);while(1);}
#define SW_reset_detected           !(eeprom_read_byte((uint8_t*)(0x3EF)))
#define clear_reset_eeprom           eeprom_write_byte((uint8_t*)(0x3EF),0xFF);



/*****************************************************************************/
#define setup_HW \
CLKPR = (1 << CLKPCE);                        /*Reduce 16MHz crystal clock to 8MHz*/\
CLKPR = (1 << CLKPS0);\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
Set_display_drivers;\
Clear_segments;\
Clear_digits;\
set_up_switched_inputs;\
setup_PC_comms_B(0,16);\
Timer_T0_10mS_delay_x_m(5);



/*****************************************************************************/
#define setup_watchdog \
if (SW_reset_detected){watch_dog_reset = 1;clear_reset_eeprom;}\
wdr();\
MCUSR &= ~(1<<WDRF);                          /*Line not needed WD flag already reset by bootloader */\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset                     {eeprom_write_byte((uint8_t*)(0x3EF),0);wdt_enable(WDTO_30MS);while(1);}
#define SW_reset_detected           !(eeprom_read_byte((uint8_t*)(0x3EF)))
#define clear_reset_eeprom           eeprom_write_byte((uint8_t*)(0x3EF),0xFF);



/***********************************************************************************************/
#define Set_display_drivers \
DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);\
DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);\
DDRD = (1 << DDD2) |(1 << DDD3) |(1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);




/***************************************************************/
#define set_up_switched_inputs \
MCUCR &= (~(1 << PUD));\
DDRC &= (~((1 << PC5) | (1 << PC4)));\
PORTC |= ((1 << PC5) | (1 << PC4));



/***********************************************************************************************/
#define switch_1_down ((PINC & 0x20)^0x20)
#define switch_1_up   (PINC & 0x20)
#define switch_2_down ((PINC & 0x10)^0x10)
#define switch_2_up   (PINC & 0x10)



/***********************************************************************************************/
#define set_IO_WPU \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;



/***********************************************************************************************/
#define User_prompt_B \
while(1){\
do{String_to_PC_B("R?    ");}  while((isCharavailable_B (50) == 0));\
User_response = Char_from_PC_B();\
if((User_response == 'R') || (User_response == 'r'))break;} String_to_PC_B("\r\n");



/*****************************************************************************/
#include "328_Resources/Subroutines/HW_timers.c"
#include "328_Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "328_Resources/Subroutines/Random_and_prime_nos.c"



/********************************************************************************/
