//#define F_CPU 8000000

#include <avr/wdt.h>

char watch_dog_reset;
char power_on_reset;
char User_response;
char r_prompt;

unsigned int PRN;
unsigned char PRN_counter;

#define T0_delay_10ms   5,178

void Char_to_PC_Local(char);



#define setup_HW \
setup_watchdog;\
ADMUX |= (1 << REFS0);\
OSC_CAL;\
Set_display_drivers;\
Clear_segments;\
Clear_digits;\
set_up_switched_inputs;\
setup_PC_comms_B(0,16);\
Timer_T0_10mS_delay_x_m(5);\
Check_for_r_prompt();\
Check_for_POR;



#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}



/***********************************************************************************************/
void Check_for_r_prompt(void){
  if (!(eeprom_read_byte((uint8_t*)0x3EF) & 0x04))
  r_prompt = 1;
  else r_prompt = 0;}



/***********************************************************************************************/
#define Check_for_POR \
if(MCUSR & (1 << PORF))\
{MCUSR &= ~(1<<PORF);\
\
r_prompt = 1;}

//User_prompt_B;


/***********************************************************************************************/
#define just_programmed     !(eeprom_read_byte((uint8_t*)0x3EF) & 0x02)
#define repeat_program      eeprom_write_byte((uint8_t*)0x3EF, ~0x02)



/***********************************************************************************************/
#define clear_resets \
eeprom_write_byte((uint8_t*)0x3EF, 0xFF);\
watch_dog_reset = 0;


/***********************************************************************************************/
#define Set_display_drivers \
DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);\
DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);\
DDRD = (1 << DDD2) |(1 << DDD3) |(1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);



/***********************************************************************************************/
#define Clear_segments    a_off;b_off;c_off;d_off;e_off;f_off;g_off;dp_off;

#define Clear_digits \
digit_1_RH_off;digit_2_RH_off;digit_3_RH_off;digit_4_RH_off;\
digit_1_LH_off;digit_2_LH_off;digit_3_LH_off;digit_4_LH_off;



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



#define set_up_PCI_on_sw1_and_sw2        PCICR |= (1 << PCIE1);
#define enable_pci_on_sw1                PCMSK1 |= (1 << PCINT13);
#define enable_pci_on_sw2                PCMSK1 |= (1 << PCINT12);
#define dissable_pci_on_sw1              PCMSK1 &= (~(1 << PCINT13));



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



/***********************************************************************************************/
#define OSC_CAL \
if ((eeprom_read_byte((uint8_t*)0x3FE) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x3FE) < 0xF0) && (eeprom_read_byte((uint8_t*)0x3FE)\
== eeprom_read_byte((uint8_t*)0x3FF))) {OSCCAL = eeprom_read_byte((uint8_t*)0x3FE);}



/*****************************************************************************/
#include "328_Resources/Subroutines/HW_timers.c"
#include "328_Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "328_Resources/Subroutines/Random_and_prime_nos.c"



/********************************************************************************/
