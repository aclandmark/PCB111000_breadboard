

//14 more projects very like those saved under            
//“0_project_zero” this time generating simple patterns on the display 
//some of them regular and repeating and some of them random.
//Why not copy the C code for one or two examples to be found in folder "C_file_images\1_first_project"



#include "First_project_header.h"
#include "Local_subroutines.c"
#include "display_header.h"



  
/*********************************************************  
int main (void)               //Example_1
{unsigned int Port_1, Port_2;

setup_HW;

  Port_1 = 1;
  Port_2 = 1;
for(int m = 0; m <= 15; m++){
display_binary (Port_1, Port_2, 5);
Port_1 = Port_1 << 1;
Port_2 = Port_2 << 1; 
  }SW_reset;}

************************************************************
int main (void)   //Example 3
  { unsigned int Port_1;

  setup_HW;
  wdt_enable(WDTO_30MS);
  Port_1 = 1;
  for (int m = 0; m <= 15; m++)
  {  display_binary (Port_1 << m, Port_1 << m, 5);}
for (int m = 14; m; m--)
{  display_binary
(Port_1 << m, Port_1 << m, 5);}
  while(1); }


************************************************************
int main (void)    //Example 5
  { unsigned int PORT_1, PORT_2;
  setup_HW;
  while (1)
  { PORT_1 = 0b0000000000000001; 
    PORT_2 = 0b1000000000000000;  
    for (int m = 0; m <= 15; m++)
    { display_binary(PORT_1, PORT_2,2);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }}return 1;  }


************************************************************
 int main (void)       //Example 6
  { unsigned long PORT_1, PORT_2;
  setup_HW;
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x80000000;
    for (int m = 0; m <= 31; m++)
    {  display_binary(PORT_1, PORT_2, 4);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    } }return 1;}



************************************************************
int main (void)             //Example 8
  { char digit[] =  "01234567777654321000";
        char letter;
    char counter=0;
    char direction = 0;
    char segments[8];
    
    setup_HW;
  for(int m = 0; m <=7; m++)segments[m] = 0;
  while(1){
if (counter < 8)letter = 'a';
if (counter == 8) letter = 'f';
if (counter == 9) letter = 'e';
if ((counter >= 10) && (counter <= 17)) letter = 'd';
if (counter == 18) letter = 'c';
if (counter == 19) letter = 'b';
if (counter == 20) letter = 'a';

 if(!(direction)) segments[digit[counter]-'0'] |= (1 << (letter - 'a')); 
 else segments[digit[counter]-'0'] &= (~(1 << (letter - 'a')));  
  display_pattern(segments, 50);
counter  += 1;
if (counter == 20){direction ^= 1; counter = 0;} 
}SW_reset;}



************************************************************
   int main (void)   //Example 12
  { unsigned int random_num;
  unsigned char PRN_counter;
  long PORT_1 = 1, PORT_2 = 1;

  setup_HW;
  wdt_enable(WDTO_30MS);
  PRN_counter = 0;
  random_num = PRN_16bit_GEN (0, &PRN_counter);
  while (1)
  { for (int m = 0; m < random_num % 3; m++)
    { if (!(PORT_1 = ((PORT_1 * 2) % 0x10000)))
        PORT_1 = 1;}
    if (!(PORT_2 = ((PORT_2 * 2) % 0x10000)))
  PORT_2 = 1;
    
    display_binary (PORT_1, PORT_2, 5);
       random_num = PRN_16bit_GEN 
  (random_num, &PRN_counter);}} 


  
 
************************************************************
int main (void)     //Example 13  Random display
  {int T1_period = 15;
  char direction;
  char duration = 50;
  char seg_counter;
  char segments[8];
  
  setup_HW;
  for(int m = 0; m <= 7; m++)segments[m] = 0;
    
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
   direction=1;
  while(1){
     direction ^= 1;
   seg_counter=0;
 PRN = random_display
 (direction, seg_counter, PRN, duration, segments);}}

   
 
 ************************************************************
 int main (void)               //Example 14 Random binary
{ unsigned int PRN;
  unsigned char PRN_counter;

  setup_HW;
  wdt_enable(WDTO_30MS);
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
  while (1)
  { PRN = PRN_16bit_GEN (PRN, &PRN_counter);
    display_binary (PRN, (PRN << ((PRN % 2) + 1)), 5);}}


  
 ************************************************************
int main (void){                //Example 15  numerical sequences
unsigned int Port_1, Port_2;
  char digits[12];
   char Inc = 0; 
   int duration;
   
  setup_HW;
  Port_1 = 1;
  Port_2 = 0;
 String_to_PC_Basic("Enter speed 1 - 9");
duration = waitforkeypress_Basic() - '0';

Port_1 = 1;
while(1){
Port_2 = 0x8000 - Port_1;
display_binary(Port_1, Port_2, duration);
if(char_present){if (!(Inc))Inc = 1;
else Inc = 0;
if (Char_from_PC_Basic() == 'x')SW_reset;}

if (!(Inc)) Port_1 += 1;}}



*********************************************************/
 
