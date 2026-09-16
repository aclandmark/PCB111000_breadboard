
//Defining digits in terms of their segments
//so that numbers can simply be entered at the keyboard
//For use with breadboard loaded with single digit


//Send file num_string or send string from Br@y with delay set to 1



#include "One_Digit_display_header.h"
#include "display_header.h"
#include "Local_subroutines.c"


#define zero "abcdef"                   //chars a,b,c,d,e and f are stored in an array named "zero"
#define one "bc"                        //chars b and c are stored in an array named "one"
#define two "abdeg"                     //Note: the compiler terminates each string in zero
#define three "abcdg"
#define four "bcfg"
#define five "acdfg"
#define six "gcdef"
#define seven "bca"
#define eight "abcdefg"
#define nine "gabcf"

const char *message_1 = "String memory dump\t";
  const char *message_2 = "\r\nDigit\tAddress    String\r\n";




int main (void){

char   digit='0';  
int string_counter=0;
int letter_counter=0;
int dig_counter;
const char* string_ptr = 0;     //pointer: will be loaded with the address of a segment string 
                                 //(i.e. the address of string "zero", "one", "two" etc....) 

setup_HW;               

print_memory_contents;


String_to_PC_B("\r\nSend digits?");


dig_counter = 0;

do{ 

while(!(isCharavailable_B(1)))wdr(); 
digit = Char_from_PC_B();                   //user enters digit (0 to 9) at the PC keyboard
Clear_digits;
Clear_segments;


switch (dig_counter){
  case 7: digit_1_LH_on; break;
  case 6: digit_2_LH_on; break;
  case 5: digit_3_LH_on; break;
  case 4: digit_4_LH_on; break;
  case 3: digit_1_RH_on; break;
  case 2: digit_2_RH_on; break;
  case 1: digit_3_RH_on; break;
  case 0: digit_4_RH_on; break;}


switch(digit){                                  //The appropriate address is loaded into location 
                                                //"string_pointer"
case '0': string_ptr = zero; break;             //The address of array zero is loaded into 
                                                //location "string_ptr"
case '1': string_ptr = one; break;
case '2': string_ptr = two; break;
case '3': string_ptr = three; break;
case '4': string_ptr = four; break;
case '5': string_ptr = five; break;
case '6': string_ptr = six; break;
case '7': string_ptr = seven; break;
case '8': string_ptr = eight; break;
case '9': string_ptr = nine; break;
default: continue; break;}                        //Illegal key press: Go immediately to the start of the 
                                                  //do loop. 

                                                  //Send the address of the required string to 
                                                  //subroutine "display_num_string();"
display_single_digit_B(string_ptr);

dig_counter += 1;
dig_counter %= 8;

} while (1);}



/************************************************************************************************************************/
void display_single_digit_B (const char* s){             //Subroutine requires a pointer to the string   
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
}



/************************************************************************************************************************/ 
