/*
Acquiring real numbers from the KBD


Step 1    Convert a number entered at the KBD such as  5.875 to two numbers 5875 and 1000
Step 2    Divide 5875 by 1000 to give 5 with a remainder of 875
          Double 875 to 1750 and divide by 1000 to give 1 remainder 750
          Double 750 to 1500 and divide by 1000 to give 1 remainder 500
          Double 500 to 1000 and divide by 1000 to give 1 remainder zero
          We now know that 5.875 is 101.111 in binary
          0.111 is 0.5 + 0.25+ 0.125 = 0.875
Step 3    Convert this number to two numbers 101111 and 2^3 (=8)
          101111 is 47 and 47/8 is 5.875
          101111 is ka the integer part
          3 is ka the exponent
Step 4    We can now do integer arithmetic with the number 101111 
          and must take account of the twos exponent separately
Step 5    The integer and exponent parts are now combined into a 
          single 32 bit number.  The integer has 23 bits, the exponents 8 bits
          The final bit bit 31 is reserved for the sign. 

Note: Here we only deal with numbers with a decimal point which are ka real numbers
The same methods can be expanded to deal with floating point numbers which are 
real numbers with a tens exponent such as 5.875 x 10^5
*/


//see https://www.h-schmidt.net/FloatConverter/IEEE754.html


#include "FPN_from_KBD_header.h"


void print_fpn_as_binary(float, char);




int main (void){
  char digits[12];
long dividend, divisor;
int twos_expt;
long int_result;
char decimal_places;
 float fpn_result;
 char num_string[12];

     
setup_HW;
sei();
if(MCUSR & (1 << PORF)){User_prompt_A;eeprom_write_byte((uint8_t*)0x3FA, 0);MCUSR = 0;}
if(!(eeprom_read_byte((uint8_t*)0x3FA)))
{Serial.write("Enter real number (i.e. with decimal point)\r\n");
eeprom_write_byte((uint8_t*)0x3FA, 0xFF);}   

dividend = Real_Num_from_PC(digits, &divisor, &decimal_places);     //Step 1
Serial.write ('\t');Int_Num_to_PC_A(dividend, num_string, ' ');
Serial.write (" / ");Int_Num_to_PC_A(divisor, num_string, ' ');

int_result = int_divide_Local (dividend, divisor, &twos_expt);                    //Steps 2 to 4

Serial.write ('\t');
Int_Num_to_PC_A(int_result, num_string, ' ');
Serial.write (" x 2 exp ");
Int_Num_to_PC_A(twos_expt, num_string, ' ');

fpn_result = assemble_fpn_Local (int_result,twos_expt);                           //Step 5

Serial.write ('\t');
print_fpn_as_binary(fpn_result, '\t');


Serial.print(fpn_result,decimal_places);                                    //Use Arduino library function

SW_reset;}


/***************************************************************************************************************************/
long int_divide_Local(long A, long B, int * binary_pt_counter)    
  {
    long Div, mod;
    long Int_result;

 *binary_pt_counter = 0;
 
real_divide_Local(A, B, &Div, &mod);                      //Perform the first division to get the integer result plus remainder
 Int_result = Div;
while (!(Int_result & 0x1000000))                   //Reserve 25 bits for the result of the division      
{real_divide_Local(mod*2, B, &Div, &mod);                 //Double the remainder and repeat the division.
 Int_result = Int_result <<1;                       //For each division shift result one place left
    if (Div) Int_result = Int_result | 1;           //If the result was one place a one in the bit just vacated
    *binary_pt_counter -= 1;}                            //The number of bits to the right of the binary point
   Int_result += 1;                                 //Add 1 to round up the result
   Int_result = Int_result>> 1;                     //Reduce number to 24 bits
  *binary_pt_counter += 1;
   
  return Int_result; } 



/*****************************************************************************************************************************/
void real_divide_Local(long A, long B, long *Div, long *mod)      
  {*Div = A/B;
  *mod = A%B;}

/*****************************************************************************************************************************/
float assemble_fpn_Local (long int_result,int twos_expt){
float fpn;

twos_expt += 24;                                                        //Shift binary point from right hand end to left hand end
twos_expt += 126;                                                       //Floating point number convention                
int_result = int_result  &  (~((unsigned long)0x80000000 >> 8));        //Clear bit 23 (which is always 1)
int_result = int_result | ((long)twos_expt << 23);                      //Exponent can now occupy bits 23 to 30 (bit 31 reserved for sign)
fpn =  *(float*)&int_result;  
return fpn;}


/****************************************************************************************************************************/


/**************************************************************************************************************************************/
