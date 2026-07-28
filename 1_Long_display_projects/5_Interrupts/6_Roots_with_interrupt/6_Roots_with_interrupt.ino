
/*
 Drives the display while calculating and printing out the square root
 of an integer number entered at the keyboard.
 Calculates square roots by trial and error starting with 2.
 */
 

#include "Roots_with_interrrupt_header.h"
#include "display_header.h"
#include "Local_subroutines.c"

void Num_string_from_KBD_Local(char *);

#define message_1 "\r\nThis program calculates roots.\r\n\
Enter integer number\r\n?"


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



volatile char num_present = 0;                    //Set to one when number has been entered and -cr- presses (See Local subroutines)
volatile char ready_to_compute = 0;               //Set to one as the ISR exits (to provide a fixed known time for calculations)
volatile char dig_start = 0;
volatile char dig = 0;
volatile int digit_num;
volatile int clock_rate = 500;
char Num_string[12];
long Num;
const char* string_ptr = 0; 



int main (void)
{  setup_HW;
//_delay_ms(1);

set_up_PCI_on_sw2_and_sw3    
enable_pci_on_sw2; 
enable_pci_on_sw3; 


if(MCUSR & (1 << PORF)){User_prompt_Basic;eeprom_write_byte((uint8_t*)0x1FA, 0);MCUSR = 0;}
if(!(eeprom_read_byte((uint8_t*)0x1FA)))
{String_to_PC_Basic(message_1);
eeprom_write_byte((uint8_t*)0x1FA, 0xFF);}   

  digit_num = 0;
  sei();
 T1_clock_tick(clock_rate); 
 while (1) {
    Num_string_from_KBD_Local(Num_string);
    Num_string_to_PC_Basic(Num_string);
    Char_to_PC_Basic('\t');
   while(!(ready_to_compute));                    //Wait here for best time to start computation
  ready_to_compute = 0;
  num_present = 0; 
   Num = Askii_to_binary_Local(Num_string);       //Convert number entered at the KBD to binary
    root_computation(Num, Num_string);            //Calculate the root, and save in "Num_string" (see Int_to_String_Basic() in Localsubroutines)
    Num_string_to_PC_Basic(Num_string);           //Send result to the PC
    newline_Basic();
    Char_to_PC_Basic('?'); }}



/********************************************************************************************************/
void T1_clock_tick(int T1_period_in_ms)                               //Start the T1 clock
{ TCNT1 = 0;
  OCR1A = T1_period_in_ms * 125;
  TIMSK1 |= (1 <<  OCIE1A);
  TCCR1B = 0x03;}



/********************************************************************************************************/
ISR(TIMER1_COMPA_vect) 
{
 TCNT1 = 0;
  Clear_digits;
  
switch (digit_num + 1){
case 1:  digit_4_RH_on; break;
case 2:  digit_3_RH_on; break;
case 3:  digit_2_RH_on; break;
case 4:  digit_1_RH_on; break;
case 5:  digit_4_LH_on; break;
case 6:  digit_3_LH_on; break;
case 7:  digit_2_LH_on; break;
case 8:  digit_1_LH_on; break;}

  Clear_segments; 
  
switch(dig){        
case 0: string_ptr = zero; break;     
case 1: string_ptr = one; break;    
case 2: string_ptr = two; break;
case 3: string_ptr = three; break;
case 4: string_ptr = four; break;
case 5: string_ptr = five; break;
case 6: string_ptr = six; break;
case 7: string_ptr = seven; break;
case 8: string_ptr = eight; break;
case 9: string_ptr = nine; break;} 

display_single_digit (string_ptr, 1);

if (num_present) {ready_to_compute = 1;}

dig = (dig+1)%10;

  digit_num += 1;
digit_num = digit_num%8;
if(!(digit_num))dig = dig_start;}



/***********************************************************************************************************************/
void display_single_digit (const char* s, int digit_num){             //Subroutine requires a pointer to the string   
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
char_ptr++;}}                                                         //incrementing "char_ptr" steps through the string
  


/********************************************************************************************************/
long Askii_to_binary_Local(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';}}
  return num;}



/***********************************************************************************************/
ISR(PCINT1_vect) {  if ((switch_2_up)&& (switch_3_up))return;                                                    //Use with examples 2 & 3 only
  
  if (switch_3_down){clock_rate = clock_rate/2;
 TCNT1 = 0;
  OCR1A = clock_rate * 125;
  
  _delay_ms(100);
  if(clock_rate == 1)clock_rate = 500;}
    
  if (switch_2_down){dig_start = (PRN_8bit_GEN())%8;
  dig_start = dig_start%8;_delay_ms(50);}}




  /*************************************************************************************/
