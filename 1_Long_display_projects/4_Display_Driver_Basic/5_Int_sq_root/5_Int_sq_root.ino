

#include "int_sq_root_header.h"
#include "display_header.h"
#include "square_root_subroutines.c"

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
num = atol (real_num_string);

root_computation(num, digits);
Num_string_to_PC_Basic(digits);
 
String_to_PC_Basic("\r\n"); 
String_to_PC_Basic(digits);
for(int m = 0; m <=14; m++)
{if (digits[m] == '.'){digits_pre_dp = m-1; break;}}
digits[digits_pre_dp] |= 0x80;


for(int m = digits_pre_dp + 1; m < 14; m++)digits[m] = digits[m+1];

String_to_PC_Basic ("\r\n\r\nAK to repeat");
digits[8] = 0;
invert_num_string(digits);
display_real_num(digits);

exit_Key_press = Char_from_PC_Basic();

SW_reset;}



/***************************************************************************************/
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
display_single_digit(string_ptr, dp);
digit_num++;
_delay_us(led_on_time);
}  while (digit_num < 8); 

for (int m = digit_num; m < 8; m++)_delay_us(1200);

if (UCSR0A & (1 << RXC0))return;}}





/************************************************************************************************************************/
void display_single_digit (const char* s, char dp){             //Subroutine requires a pointer to the string   
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
