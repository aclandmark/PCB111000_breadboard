



//Accepts an integer number at the keyboard and 
//prints out its factors.


/************************************************************************************************************/
#include "Integer_numbers_header.h"

#define message_1 "\r\nEnter integer number:  PCB returns all factors of that number.\r\n"
#define message_2 "\r\nNew number?\r\n"


//Type main routine here

int main (void)  
  { 
    char num_string[12];
    long  num;
    long m = 1;
 
 setup_HW;

if (first_run_after_programming)
{clear_programmer;
String_to_PC_Basic(message_1);}

else String_to_PC_Basic(message_2);
  
num = Int_from_PC_Basic(num_string);

newline_Basic();
Int_to_PC_Basic(num);
String_to_PC_Basic("\t");

do{
if(!(num%m)){Int_to_PC_Basic(m);}
m += 1; if(!(m%10000))String_to_PC_Basic(".");}while(m < num);

SW_reset;
return 1;  }




/******************************************************************************************/
