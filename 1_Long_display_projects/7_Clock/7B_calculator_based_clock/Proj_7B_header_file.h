//#define F_CPU 8000000

#include <avr/wdt.h>
#include <util/delay.h>



char watch_dog_reset = 0;
char power_on_reset = 0;
char User_response;
char r_prompt;

char num_as_string[12];
char str_counter;

char digits[8], charH, charL ;
char Hours, Minutes, Seconds, deci_Secs;
volatile long deci_sec_counter;

volatile char tick_counter; 
volatile char clock_tick;

#define T0_delay_10ms   5,178


/***************************************************************************/
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



/***************************************************************************/
#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}


#define Check_for_POR \
if(MCUSR & (1 << PORF)){power_on_reset = 1;\
MCUSR &= ~(1<<PORF);}


/***********************************************************************************************/
void Check_for_r_prompt(void){
  if (!(eeprom_read_byte((uint8_t*)0x3EF) & 0x04))
  r_prompt = 1;
  else r_prompt = 0;}



/***********************************************************************************************/
/*#define Check_for_POR \
if(MCUSR & (1 << PORF))\
{MCUSR &= ~(1<<PORF);\
User_prompt_B;\
r_prompt = 1;}*/





/***********************************************************************************************/
#define just_programmed     !(eeprom_read_byte((uint8_t*)0x3EF) & 0x02)
#define repeat_program      eeprom_write_byte((uint8_t*)0x3EF, ~0x02)



/***********************************************************************************************/
#define clear_resets \
eeprom_write_byte((uint8_t*)0x3EF, 0xFF);\
watch_dog_reset = 0;


/*********************************************************************************/
#define Set_display_drivers \
DDRB = (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);\
DDRC = (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);\
DDRD = (1 << DDD2) |(1 << DDD3) |(1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);



/***********************************************************************************************/
#define Clear_segments    a_off;b_off;c_off;d_off;e_off;f_off;g_off;dp_off;

#define Clear_digits \
digit_1_RH_off;digit_2_RH_off;digit_3_RH_off;digit_4_RH_off;\
digit_1_LH_off;digit_2_LH_off;digit_3_LH_off;digit_4_LH_off;





#define reset_clock_1   {digits[0] = 0; for (int m = 1; m < 8; m++)digits[m] = '0'; }



#define HoursH digits[7]
#define HoursL digits[6]
#define MinsH digits[5]
#define MinsL digits[4]
#define SecsH digits[3]
#define SecsL digits[2]
#define deci_SecsH digits[1]
#define deci_SecsL digits[0]



/***************************************************************/
#define set_up_switched_inputs \
MCUCR &= (~(1 << PUD));\
DDRC &= (~((1 << PC5) | (1 << PC4)));\
PORTC |= ((1 << PC5) | (1 << PC4));



/**********************************************************************************************/
#define switch_1_down ((PINC & 0x20)^0x20)
#define switch_1_up   (PINC & 0x20)
#define switch_2_down ((PINC & 0x10)^0x10)
#define switch_2_up   (PINC & 0x10)




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





/********************************************************************************/
