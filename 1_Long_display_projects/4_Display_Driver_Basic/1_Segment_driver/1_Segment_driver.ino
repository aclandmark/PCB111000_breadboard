
/*
 Enables users to drive the display manually
 This indicates that there is not necessarily any connection between 
 the display and an actual number.
 */

#include "display_header.h"
#include "Segment_driver_header.h"


#define message_1 "\r\nPress key a to g (x for next digit).\r\n\
Press 'z' to clear the display.\r\n"
#define message_2 "Again ?\r\n"


int main (void){

char letter = 0, digit_num;            
char seg_counter = 0;
setup_HW;

if(first_run_after_programming)
{clear_programmer;
String_to_PC_Basic(message_1);}
else String_to_PC_Basic(message_2);

digit_num=1;
while(digit_num <= 8){

do{
letter = waitforkeypress_Basic();
  
  if(!(seg_counter)){
 Clear_digits;
  Clear_segments;
  
switch (digit_num){
 case 1: digit_1_LH_on; break; 
 case 2: digit_2_LH_on; break;
 case 3: digit_3_LH_on; break;
 case 4: digit_4_LH_on; break; 
 case 5: digit_1_RH_on; break; 
 case 6: digit_2_RH_on; break; 
 case 7: digit_3_RH_on; break; 
 case 8: digit_4_RH_on; break;}}
  seg_counter += 1;
  
  switch(letter)
 {case 'a': a_on;   break;                     
case 'b': b_on;    break;                    
case 'c': c_on;    break;
case 'd': d_on;    break;
case 'e': e_on;    break;
case 'f': f_on;    break;
case 'g': g_on;    break; 
case 'x':  digit_num += 1;seg_counter = 0; break;
case 'z': SW_reset;break;
default: break;}

}while(letter != 'x');
}SW_reset; }



/********************************************************************************************************************/
