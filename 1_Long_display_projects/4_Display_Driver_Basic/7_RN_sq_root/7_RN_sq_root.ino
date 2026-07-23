

#include "Int__sq_root_header.h"
#include "display_header.h"
#include "square_root_subroutines.c"
#include "dp_processor.h"

#define min_intensity 1


#ifdef min_intensity 
int led_off_time = 900;
int led_on_time = 300;
#else
int led_off_time = 50;
int led_on_time = 1150;
#endif



int main (void){

char real_num_string[15];
long num;
char exit_Key_press;
char digits[15];
char digits_pre_dp;
char digits_post_dp;

setup_HW;               

if(power_on_reset){
 User_prompt_Basic;
 record_POR; 
 Clear_segments;}

 if(first_run){
  clear_programmer;
  String_to_PC_Basic("\r\nEnter integer?");
String_to_PC_Basic ("\r\nAK to display root\r\n");}

else 

String_to_PC_Basic("\r\nAgain\t");

Real_num_from_PC_Basic(real_num_string);

display_real_num(real_num_string);    //needs AK to exit
exit_Key_press = Char_from_PC_Basic();

invert_num_string(real_num_string);
Real_num_string_to_PC_Basic(real_num_string);

digits_post_dp = 0;
digits_pre_dp = 0;

remove_dp_and_count_post_dp_digits;
add_trailing_zero_for_even_number_of_post_dp_digits;

//diagnostic_print_out;

num = atol (real_num_string);

root_computation(num, digits);

integrate_dp_for_integer_root;

if(digits_post_dp){
digits_post_dp /= 2;

real_num_greater_than_1;
real_num_less_than_1;}

Char_to_PC_Basic ('\t');
Real_num_string_to_PC_Basic(digits);
digits[8] = 0;
invert_num_string(digits);
display_real_num(digits);

exit_Key_press = Char_from_PC_Basic();

SW_reset;}



/***************************************************************************************/
void Real_num_string_to_PC_Basic(char * digits){
 for (int m = 0; m <= 8; m++){if(!(digits[m]))return;  if(!(digits[m] & 0x80))
 Char_to_PC_Basic(digits[m]);
 else {Char_to_PC_Basic(digits[m] & ~0x80);Char_to_PC_Basic('.');}}}



/****************************************************************************************/
void display_real_num(char*num_string){

char   digit;
int digit_num=0;            
int string_counter=0;
int letter_counter=0;
const char* string_ptr = 0;
char dp;

  
while(1){digit_num=0;
do{
  Clear_digits;
  Clear_segments;
  dp_off;
digit = num_string[digit_num];

if(digit & 0x80) {dp = 1; digit &= (~(0x80));} else dp = 0;

switch (digit_num + 1){
case 1:  digit_4_RH_on; break;
case 2:  digit_3_RH_on; break;
case 3:  digit_2_RH_on; break;
case 4:  digit_1_RH_on; break;
case 5:  digit_4_LH_on; break;
case 6:  digit_3_LH_on; break;
case 7:  digit_2_LH_on; break;
case 8:  digit_1_LH_on; break;}
switch(digit){ 
case '0': string_ptr = zero; break;
case '1': string_ptr = one; break;
case '2': string_ptr = two; break;
case '3': string_ptr = three; break;
case '4': string_ptr = four; break;
case '5': string_ptr = five; break;
case '6': string_ptr = six; break;
case '7': string_ptr = seven; break;
case '8': string_ptr = eight; break;
case '9': string_ptr = nine; break;
case 0: break;} 

if(!(digit))break;                       
 _delay_us(led_off_time);
display_single_digit(string_ptr, digit_num, dp);
digit_num++;
_delay_us(led_on_time);
}  while (digit_num < 8); 

for (int m = digit_num; m < 8; m++)_delay_us(1200);


if (UCSR0A & (1 << RXC0))return;}}




/************************************************************************************************************************/
void display_single_digit (const char* s, int digit_num, char dp){             //Subroutine requires a pointer to the string   
int char_ptr=0;                                                     //containing segments used to define a digit
char letter;

while(1){
letter = *(s + char_ptr);                                           //Note these two expressions are equivalent
switch(letter){                                                     //Work through the segments contained in the 
case 'a':  a_on;    break;                                                           //string until '\0' is encountered
case 'b':  b_on;    break;
case 'c':  c_on;    break;
case 'd':  d_on;    break;
case 'e':  e_on;    break;
case 'f':  f_on;    break;
case 'g':  g_on;    break;
                                                                    //update display one segment at a time
case 0:  break;                                                     //zero indicates the end of the string
default: break;}
if(!(letter))break;
char_ptr++;}                                                         //incrementing "char_ptr" steps through the string
  
 if(dp){dp_on;}} 


/************************************************************************************************************************/ 
