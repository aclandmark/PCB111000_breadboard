

#include <avr/wdt.h>

char watch_dog_reset;

#define T0_delay_10ms   5,178

#define setup_HW \
Clear_digits;\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
Set_display_drivers;\
set_up_switched_inputs;\
setup_PC_comms_Basic(0,16);\
Timer_T0_10mS_delay_x_m(5);



/*************************************************************************/
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



/********************************************************************************/
#define Clear_segments    a_off;b_off;c_off;d_off;e_off;f_off;g_off;dp_off;

#define Clear_digits \
digit_1_RH_off;digit_2_RH_off;digit_3_RH_off;digit_4_RH_off;\
digit_1_LH_off;digit_2_LH_off;digit_3_LH_off;digit_4_LH_off;


#define digit_4_RH_on  PORTB |= (1 << PB1);
#define digit_4_RH_off  PORTB &= (~(1 << PB1));

#define digit_3_RH_on  PORTD |= (1 << PD4);
#define digit_3_RH_off  PORTD &= (~(1 << PD4));

#define digit_2_RH_on  PORTD |= (1 << PD5);
#define digit_2_RH_off  PORTD &= (~(1 << PD5));

#define digit_1_RH_on  PORTD |= (1 << PD3);
#define digit_1_RH_off  PORTD &= (~(1 << PD3)); 


#define digit_4_LH_on  PORTC |= (1 << PC1);
#define digit_4_LH_off  PORTC &= (~(1 << PC1));

#define digit_3_LH_on  PORTC |= (1 << PC2);
#define digit_3_LH_off  PORTC &= (~(1 << PC2));

#define digit_2_LH_on  PORTC |= (1 << PC3);
#define digit_2_LH_off  PORTC &= (~(1 << PC3));

#define digit_1_LH_on  PORTD |= (1 << PD2);
#define digit_1_LH_off  PORTD &= (~(1 << PD2));



/********************************************************************************/
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

#define switch_Seg_c    if(PORTB & (1 << PB3)){ c_on;} else c_off;
#define switch_Seg_e    if(PORTC & (1 << PC0)){ e_on;} else e_off;
#define switch_Seg_f    if(PORTD & (1 << PD7)){ f_on;} else f_off;
#define switch_Seg_b    if(PORTB & (1 << PB0)){ b_on;} else b_off;



/**********************************************************************************/
#define set_up_switched_inputs \
MCUCR &= (~(1 << PUD));\
DDRC &= (~((1 << PC5) | (1 << PC4)));\
PORTC |= ((1 << PC5) | (1 << PC4));

#define switch_3_down ((PINC & 0x20)^0x20)
#define switch_3_up   (PINC & 0x20)
#define switch_2_down ((PINC & 0x10)^0x10)
#define switch_2_up   (PINC & 0x10)

#define set_up_PCI_on_sw2_and_sw3        PCICR |= (1 << PCIE1);
#define enable_pci_on_sw3                PCMSK1 |= (1 << PCINT13);
#define enable_pci_on_sw2                PCMSK1 |= (1 << PCINT12);
#define dissable_pci_on_sw3              PCMSK1 &= (~(1 << PCINT13));



/*****************************************************************************/
#include "Resources/Subroutines/HW_timers.c"
#include "Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "Resources/Subroutines/Random_and_prime_nos.c"



/******************************************************************************/
