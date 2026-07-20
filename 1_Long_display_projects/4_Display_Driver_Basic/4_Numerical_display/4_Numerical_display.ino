

#include "Numerical_display_header.h"
#include "display_header.h"


//#define min_intensity 1


#ifdef min_intensity 
int led_off_time = 900;
int led_on_time = 300;
#else
int led_off_time = 50;
int led_on_time = 1150;
#endif



int main (void){
          
int string_counter=0;
int letter_counter=0;
long num;
char num_string[11];


setup_HW;               

for(int n = 0; n<11; n++)num_string[n] = 0;

if(power_on_reset)
{User_prompt_Basic;
record_POR;
Clear_segments;}   

if(first_run)
{eeprom_write_byte((uint8_t*)0x3FA, 0xFF);
String_to_PC_Basic("\r\nSend integer? AK to repeat.");}

else 

String_to_PC_Basic("\r\nAgain");
num = Display_Int_from_PC_Basic(num_string);
invert_num_string(num_string);
ltoa(num/2, num_string, 10);
invert_num_string(num_string);
Display_Int(num_string);
SW_reset;}



void Display_Int(char * num_string){
  int digit_num=0; 
char   digit;
const char* string_ptr = 0;
char dp;
  
while(1){digit_num=0;

do{
  Clear_digits;
  Clear_segments;
digit = num_string[digit_num];

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

if (UCSR0A & (1 << RXC0))break;}}



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
                                                                    


/**********************************************************************************************************************************************************************************/
long Display_Int_from_PC_Basic(char digits[]){
char keypress;

do
{keypress =  waitforkeypress_Basic();} 
while (!(decimal_digit_Basic(keypress)));                                      //(non_decimal_char(keypress));  //Not -,0,1,2,3,4,5,6,7,8 or 9
digits[0] = keypress;
Display_Int(digits);
while(1){
if ((keypress = wait_for_return_key_Basic())  =='\r')break;
if (decimal_digit_Basic (keypress))                                           //012345678or9  :Builds up the number one keypress at a time
{for(int n = 7; n>=1; n--)
digits[n] = digits[n-1];                                                //Shifts display left for each keypress
digits[0] = keypress;}Display_Int(digits);}
invert_num_string(digits);           
return atol(digits);}



/************************************************************************************************************************/ 
