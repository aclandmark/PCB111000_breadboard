

#include "Eight_digit_display_header.h"
#include "display_header.h"


#define min_intensity 1


#ifdef min_intensity 
int led_off_time = 900;
int led_on_time = 300;
#else
int led_off_time = 50;
int led_on_time = 1150;
#endif

#define test_delay _delay_ms(1);

int max_delay = 100;


int main (void){
          
int string_counter=0;
int letter_counter=0;
long num;
char num_string[] = "87654321";   //num_string[11];

setup_HW;               

while(1){
Display_Int(num_string);
for(int m = 0; m <= 7; m++)num_string[m] = (num_string[m]-'0' +1)%10 + '0';}

SW_reset;}


/*************************************************************************************/
void Display_Int(char * num_string){
  int digit_num=0; 
char   digit;
const char* string_ptr = 0;
  
while(1){

for (digit_num = 1; digit_num <= 8; digit_num++){
  Clear_digits;
  Clear_segments;
digit = num_string[digit_num-1];

switch (digit_num){
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
case '9': string_ptr = nine; break;} 
                      
for (int m = 0; m < max_delay; m++)test_delay;
_delay_us(led_off_time);

display_single_digit(string_ptr);

_delay_us(led_on_time);}  

if(switch_3_down){max_delay *= 2;max_delay /= 3;}
if(switch_2_down){if (!(max_delay))max_delay = 2; else {max_delay *= 3;max_delay /= 2;}}

if (UCSR0A & (1 << RXC0))break;}Char_from_PC_Basic();}




/********************************************************************************************************************/
void display_single_digit (const char* s){             //Subroutine requires a pointer to the string   
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
char_ptr++;}}                                                       //incrementing "char_ptr" steps through the string
  
                                                                    

/************************************************************************************************************************/ 
