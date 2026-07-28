/*
Responds to key presses by printing out the askii characters
Multiple keypresses can be made any time 
Send Character strings
 */

volatile int p=0;

char repeats[50];

#include "4A_Rx_interrupt_header.h"


volatile char keypress_counter = 0;

int main (void)
  { char symbol;
    char q = 0;
    int n = 0;
    char next_keypress;
    
  setup_HW;

  for(int m = 0; m <50; m++)repeats[m] = 0;
 

if(first_run)
{clear_first_run;
String_to_PC_Basic("\r\nMultiple key presses?\r\n");}

else ;

    UCSR0B |= (1 << RXCIE0);
sei();
 
while(!(keypress_counter));

 next_keypress = 1;

  do{
symbol = repeats[next_keypress - 1];symbol -= '!';
for(int q = 0; q <='~' - '!'; q++)Char_to_PC_Basic((symbol+q)%94 + '!');
newline_Basic(); if(next_keypress < keypress_counter)next_keypress += 1;
else break;} 
while(next_keypress < 50);
 
 
newline_Basic();
SW_reset;}


ISR(USART_RX_vect)
{ keypress_counter += 1;
  repeats[p++] = Char_from_PC_Basic();}




/***************************************************************************************/
