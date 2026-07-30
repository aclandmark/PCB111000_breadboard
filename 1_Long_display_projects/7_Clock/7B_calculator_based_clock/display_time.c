#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void Timer_T0_sub(char, unsigned char);

#define T0_delay_1200uS     3,106
#define T0_delay_900uS      3, 144
#define T0_delay_300uS      3,218

//#define min_intensity 1

extern int led_off_time;
extern int led_on_time;


void display_single_digit (const char*, int, char);


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



/********************************************************/
#define a_off   PORTD |= (1 << PD6);
#define a_on  PORTD &= (~(1 << PD6));

#define b_off   PORTB |= (1 << PB0);
#define b_on  PORTB &= (~(1 << PB0));

#define c_off   PORTB |= (1 << PB3);
#define c_on  PORTB &= (~(1 << PB3));

#define d_off   PORTB |= (1 << PB5);
#define d_on  PORTB &= (~(1 << PB5));

#define e_off   PORTC |= (1 << PC0);
#define e_on  PORTC &= (~(1 << PC0));

#define f_off   PORTD |= (1 << PD7);
#define f_on  PORTD &= (~(1 << PD7));

#define g_off   PORTB |= (1 << PB2);
#define g_on  PORTB &= (~(1 << PB2));

#define dp_off   PORTB |= (1 << PB4);
#define dp_on  PORTB &= (~(1 << PB4));



/********************************************************/
#define digit_4_RH_on  PORTB |= (1 << PB1);
#define digit_4_RH_off  PORTB &= (~(1 << PB1));

#define digit_3_RH_on  PORTD |= (1 << PD4);
#define digit_3_RH_off  PORTD &= (~(1 << PD4));

#define digit_2_RH_on  PORTD |= (1 << PD5);
#define digit_2_RH_off  PORTD &= (~(1 << PD5));

#define digit_1_RH_on  PORTD |= (1 << PD3);
#define digit_1_RH_off  PORTD &= (~(1 << PD3)); 

#define digit_4_LH_on  PORTC |= (1 << PC1);
#define digit_4_LH_off  PORTC &= (~(1 << PC1));

#define digit_3_LH_on  PORTC |= (1 << PC2);
#define digit_3_LH_off  PORTC &= (~(1 << PC2));

#define digit_2_LH_on  PORTC |= (1 << PC3);
#define digit_2_LH_off  PORTC &= (~(1 << PC3));

#define digit_1_LH_on  PORTD |= (1 << PD2);
#define digit_1_LH_off  PORTD &= (~(1 << PD2));



/********************************************************/
#define clear_display   Clear_segments; Clear_digits;
#define Clear_segments    a_off;b_off;c_off;d_off;e_off;f_off;g_off;dp_off;

#define Clear_digits \
digit_1_RH_off;digit_2_RH_off;digit_3_RH_off;digit_4_RH_off;\
digit_1_LH_off;digit_2_LH_off;digit_3_LH_off;digit_4_LH_off;



/*********************************************************************************************/
void display_time(char*num_string){

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

digit_num++;
if(!(digit))continue;                       

#ifdef min_intensity 
Timer_T0_sub(T0_delay_900uS);
#endif

display_single_digit(string_ptr, digit_num, dp);

#ifdef min_intensity 
Timer_T0_sub(T0_delay_300uS);
#else
Timer_T0_sub(T0_delay_1200uS);
#endif


}while (digit_num < 8); 
if (UCSR0A & (1 << RXC0))return;}}


/******************************************************************************************/
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
  
 //if(dp){dp_on;}
 switch (digit_num){
  case 7:
  case 5:
  case 3: {dp_on;}break;}
  }





/*********************************************************************************************/
/*void display_single_digit (const char* s, int digit_num, char dp){             //Subroutine requires a pointer to the string   
int char_ptr=0;                                                     //containing segments used to define a digit
char letter;

while(1){
letter = *(s + char_ptr);                                           //Note these two expressions are equivalent
switch(letter){                                                     //Work through the segments contained in the 
case 'a':                                                           //string until '\0' is encountered
case 'b': 
case 'c': 
case 'd': 
case 'e': 
case 'f': 
case 'g': Any_segment(letter);break;
                                                                    //update display one segment at a time
case 0:  break;                                                     //zero indicates the end of the string
default: break;}
if(!(letter))break;
char_ptr++;}                                                         //incrementing "char_ptr" steps through the string
  
 if(dp){dp_on;}}*/                                                                   
      
                                                                    
   

/*********************************************************************************************/
