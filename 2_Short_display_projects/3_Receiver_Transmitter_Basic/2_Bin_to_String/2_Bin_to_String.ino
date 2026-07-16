
//5 Projects that explore the conversion of numbers to strings
//so that they can be printed out


#include "Receiver_Transmitter_header.h"
#include "Local_subroutines.c"

//Five examples to experiment with.
  




/**********************************************************************************
int main (void)              //Example 1 
  { int i = 0;              //Convert number to string
  int number = 12345;
  char s[12];
  setup_HW;
  //Set up watchdog timer to generate a reset
  wdt_enable(WDTO_120MS);
 while(switch_3_down)wdr();

  //Convert binary number to string
  while(1) {
    s[i++] = number % 10 + '0';
    number = number/10;
    if (!(number))break;
  }s[i] = '\0';

  //Print string out in reverse order
    for (int m = i; m > 0; m--)
    Char_to_PC_Basic(s[m - 1]);
  newline_Basic();
 //Generate a reset
 while(switch_3_up)wdr();
  while(switch_3_down);
  return 1;}


**********************************************************************
int main (void)               //Example 2
  {                             //Convert number to string
  long number = 2;        //Use local subroutines
 char num_string[12];
 char direction = 0;
 int str_len;
  
  setup_HW;
 
while(number) {
str_len = Bin_to_string_Local(number, num_string);
 Num_string_to_PC_Local(num_string, str_len);
 if (!(direction))number = number *3/2;
else number = number *2/3;
  
  newline_Basic();
 waitforkeypress_Basic();
if (number >= 18000){direction ^= 1;
number = number *2/3;newline_Basic();}}
newline_Basic();SW_reset;
  return 1;}


**********************************************************************
int main (void)                 //Example 3
  { long number = 1;      //Print out a column of numbers
  long number_old = 1;
 
  setup_HW;
  wdt_enable(WDTO_120MS);
  while(switch_3_down)wdr();
  
  for(int m = 2; m < 11; m++){
  Int_to_PC_Basic(number);
 newline_Basic();

number = (number_old * 10) + m;  
number_old = number;}

while(switch_3_up)wdr();
  while(switch_3_down);
  return 1;}


**********************************************************************
 int main (void)                    //Example 4
  { int i = 0;             //Print out a column of numbers
  long number = 123456789;
  long number_old = 123456789;
  char s[12];
  setup_HW;
   wdt_enable(WDTO_120MS);
  while(switch_3_down)wdr();
  
  for(int m = 2; m < 11; m++){
Int_to_PC_Basic(number);
 newline_Basic();

number = number_old / 10;  
number_old = number;}

while(switch_3_up)wdr();
  while(switch_3_down);
  return 1;}


**********************************************************************
int main (void)                          //Example 5 
  { unsigned int random_num; 
    unsigned char PRN_counter;
    unsigned int Short_random_number; 
  char num_string[12];
 int str_len;
  int num_array[40];

  setup_HW; 
  PRN_counter = 0;
  random_num = PRN_16bit_GEN (0, &PRN_counter);
  Short_random_number = PRN_8bit_GEN();

while(1){
  
 for(int m = 0; m <40; m++){
switch(Short_random_number%4)
 {case 0:num_array[m] = random_num%10; break;
  case 1:num_array[m] = random_num%100; break;
  case 2:num_array[m] = random_num%1000; break;
  case 3:num_array[m] = random_num%10000; break;}

str_len = Bin_to_string_Local(num_array[m], num_string);
 Num_string_to_PC_Local(num_string, str_len);
waitforkeypress_Basic(); 
Char_to_PC_Basic(' ');

random_num = PRN_16bit_GEN (random_num, &PRN_counter);
 Short_random_number = PRN_8bit_GEN();}
 
 
 Re_order_array(num_array,40);
}
return 1;}


  
******************************************************************************/
