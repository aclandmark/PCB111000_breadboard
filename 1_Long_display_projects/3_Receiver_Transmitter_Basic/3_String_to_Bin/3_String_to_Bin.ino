

//3 projects that explore the conversion of strings to numbers so that
//they can be entered at the keyboard





#include "Receiver_Transmitter_header.h"


//Three examples to experiment with

#include "Local_subroutines.c"







//***********************Subroutines*********************************
void Num_string_from_KBD_Local(char * array_ptr)
{ char keypress;
  while ((keypress = waitforkeypress_Basic()) != '\r')
  { *array_ptr = keypress;
    Char_to_PC_Basic(keypress);
    array_ptr += 1;
  }
  *array_ptr = '\0';}



//*********************************************************************
long Askii_to_binary_Local(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';
    }
  }
  return num;}




/***********************************************************************************
int main (void){               //Example 1
  char num_string[12];
  long num;
setup_HW;
if (first_run_after_programming)
{clear_programmer;
String_to_PC_Basic("Enter numbers at keyboard\r\n");}
Num_string_from_KBD_Local(num_string);
Char_to_PC_Basic('\t');
num = Askii_to_binary_Local(num_string);
Int_to_PC_Basic(num/2);
newline_Basic();
SW_reset;
return 1;}



******************************************************************************
int main (void){                //Example 2
  char num_string[12];
  long num = 2;
  long old_num = 2;
setup_HW;
String_to_PC_Basic("Multiply number by 2 and enter it\r\n");
String_to_PC_Basic("2\r\n");
while(1){
  
Num_string_from_KBD_Local(num_string);
num = Askii_to_binary_Local(num_string);

if(num == old_num * 2)
{newline_Basic();old_num = num;}
else Char_to_PC_Basic('?');
}
SW_reset;
return 1;}



************************************************************************************************
int main (void){                //Example 3
  char num_string[12];        //Re-oders numbers smallest to largest
  int num_array[20],  array_length=0;
      
setup_HW;

String_to_PC_Basic("Enter numbers at keyboard (zero to exit)\r\n");

while(1){
Num_string_from_KBD_Local(num_string);
Char_to_PC_Basic(' ');
num_array[array_length] = Askii_to_binary_Local(num_string);
if(!(num_array[array_length++]))break;}
newline_Basic();
array_length -= 1;

Re_order_array(num_array,array_length);

SW_reset;
return 1;}



****************************************************************************************/
