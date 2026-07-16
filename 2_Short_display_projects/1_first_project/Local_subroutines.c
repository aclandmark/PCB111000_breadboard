

#include <avr/wdt.h>
#include <util/delay.h>

#include "display_header.h"

void display_pattern(char *, int);
void backup_the_display(char, char);
unsigned int PRN_16bit_GEN(unsigned int, unsigned char*);
void save_segment(char);

extern  unsigned char PRN_counter;

char display_bkp[7];

char digit_num;

#define wdr()  __asm__ __volatile__("wdr")

void Timer_T0_10mS_delay_x_m(int m);


/**************************************************************************************************/
void display_binary (unsigned long Port_1, unsigned long Port_2, int duration)
{for (int q = 0; q <= duration; q++){wdr();
for(int m = 0; m <= 15; m++)
{switch(m){

case 0: if(Port_1 & (1 << m)){digit_4_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_4_LH_on; c_on;}break;
case 1: if(Port_1 & (1 << m)){digit_4_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_4_LH_on; e_on;}break;

case 2: if(Port_1 & (1 << m)){digit_3_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_3_LH_on; c_on;}break;
case 3: if(Port_1 & (1 << m)){digit_3_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_3_LH_on; e_on;}break;

case 4: if(Port_1 & (1 << m)){digit_2_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_2_LH_on; c_on;}break;
case 5: if(Port_1 & (1 << m)){digit_2_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_2_LH_on; e_on;}break;

case 6: if(Port_1 & (1 << m)){digit_1_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_1_LH_on; c_on;}break;
case 7: if(Port_1 & (1 << m)){digit_1_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_1_LH_on; e_on;}break;
}_delay_us(750);
Clear_segments;
Clear_digits;}}}



/**************************************************************************************************/      
void display_pattern(char * seg_store, int duration){     

for (int q = 0; q <= duration; q++){
for(int p = 0; p <= 7; p++){

Clear_segments;
Clear_digits;
  
switch (p){
case 0: digit_4_LH_on; break;
case 1: digit_3_LH_on; break;
case 2: digit_2_LH_on; break;
case 3: digit_1_LH_on; break;}

for(int m = 0; m <=7; m++){
  if (seg_store[p] & (1 << m)){switch(m){
  case 0: a_on; break;
  case 1: b_on; break;
  case 2: c_on; break;
  case 3: d_on; break;
  case 4: e_on; break;
  case 5: f_on; break;
  case 6: g_on; break;}}
}_delay_us(120);}}  
Clear_segments;
Clear_digits;}



/**************************************************************************************************/
unsigned long random_display (char direction, char seg_counter, unsigned long PRN, char duration, char * segs)
{char letter;
char prompt;

  while (seg_counter < 28) {
      letter = (PRN % 7) + 'a';
      PRN = PRN_16bit_GEN (PRN, &PRN_counter);
      digit_num = (PRN % 4);
      if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) {
        PRN_counter -= 1;
        continue; }

      if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) {
       PRN_counter -= 1;
       continue;}
       
      if(!(direction)) segs[digit_num] |= (1 << (letter - 'a'));
      else segs[digit_num] &= (~(1 << (letter - 'a')));
      
      display_pattern(segs, duration);
      backup_the_display(letter, digit_num);
      seg_counter += 1;}
      return PRN;}



/**************************************************************************************************/
  void backup_the_display(char segment, char digit_num)
  { display_bkp[segment - 'a'] =
    display_bkp[segment - 'a'] ^ (1 << digit_num);}


    /*************************************************************************************************/
