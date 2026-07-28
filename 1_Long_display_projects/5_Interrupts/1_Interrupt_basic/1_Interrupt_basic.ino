

     

#include "Interrupt_basic_header.h"
#include "display_header.h"


volatile unsigned int clock_rate = 500;                               //Extra for examples 2 and 3
volatile char dig_num = 0;
volatile int seg_num = 0;



 int main (void)   
  {
  setup_HW;
 
set_up_PCI_on_sw2_and_sw3                                             //Eamples 2 and 3 only
enable_pci_on_sw3;                                              //Eamples 2 and 3 only
    Clear_digits;
    Clear_segments;
digit_1_LH_on;
   String_to_PC_Basic("\r\nMomentarily switch pin 28 to gnd to increase flash rate");
    
    sei();
   T1_clock_tick(clock_rate);
 while(1);
   SW_reset;}



//*****************************************************************************************************
void T1_clock_tick(unsigned int T1_period_in_ms)              //Sets up the T1 clock (default value of T1_period_in_ms is 150) 
{ TCNT1 = 0;                                                  //TCNT1 increases by 1 for each clock tick 
OCR1A = T1_period_in_ms * 125;                                //Set register OCR1A to 150 x 125 = 18750
  TIMSK1 |= (1 <<  OCIE1A);                                   //Generates an intrerrupt TCNT1 equals OCR1A (i.e. after 150mS) 
  TCCR1B = 0x03;}                                             //Starts the clock with a speed of 125 ticks per mS



//*****************************************************************************************************
ISR(PCINT1_vect) {  
  dissable_pci_on_sw3;
  if (switch_3_up)return;
  Char_to_PC_Basic('.');
 
   if (switch_3_down)clock_rate = clock_rate *3/4;
  if(clock_rate <= 25)clock_rate = 500;
if (seg_num == 16) seg_num = 0;
  Clear_digits;
  
  switch (dig_num){
case 0:  digit_4_RH_on; break;
case 1:  digit_3_RH_on; break;
case 2:  digit_2_RH_on; break;
case 3:  digit_1_RH_on; break;
case 4:  digit_4_LH_on; break;
case 5:  digit_3_LH_on; break;
case 6:  digit_2_LH_on; break;
case 7:  digit_1_LH_on; break;}

  seg_num += 1;
  if ( !(seg_num%2))dig_num += 1;   
  dig_num = dig_num%8;
  sei();
  Timer_T0_10mS_delay_x_m(20);
  enable_pci_on_sw3;}



//Type Timer1 ISR here******************************************************************************

ISR(TIMER1_COMPA_vect)     
  { OCR1A = clock_rate * 125;
  TCNT1 = 0; 
  
   if(!(seg_num%2)){b_off; c_off;switch_Seg_e;switch_Seg_f} 
   else {f_off; e_off; switch_Seg_c;switch_Seg_b}}



  



//********************************************************************************************************
