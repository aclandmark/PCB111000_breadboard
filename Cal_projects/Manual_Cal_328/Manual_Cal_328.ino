


#include "Manual_Cal_328_header.h"
#include "Manual_cal_resources/PC_comms.c"

int main (void){
long cal_error;
int OSCCAL_UV;
int OSCCAL_test;
int OSCCAL_WV;    
char digits[10];
int test;


setup_HW;

User_prompt;
OSCCAL_WV = OSCCAL;

String_to_PC_Basic("Atmega168 manual cal  AK to start\r\n\
Default OSCCAL   ");
Int_to_PC_Basic(eeprom_read_byte((uint8_t*)(0x3FD)));
String_to_PC_Basic("\t Previous user value    ");
Int_to_PC_Basic(eeprom_read_byte((uint8_t*)(0x3FF)));

waitforkeypress_Basic();

ASSR = (1 << AS2);
sei();

cal_mode = 5;   
Get_ready_to_calibrate;
OSCCAL_test = OSCCAL_WV - 20;                      //Compute cal error for 41 values of OSCCAL

for(int m = 0; m <= 40; m++){
  _delay_ms(25);
  OSCCAL = OSCCAL_test;
  cal_error = compute_error(1,cal_mode,1);    
OSCCAL = OSCCAL_WV;
String_to_PC_Basic("\r\n");
Int_to_PC_Basic(OSCCAL_test++); Char_to_PC_Basic('\t');
Int_to_PC_Basic(cal_error);
Char_to_PC_Basic('\t');
Int_to_PC_Basic(cal_error/625);}

close_calibration;
String_to_PC_Basic("\r\n");
  
String_to_PC_Basic("Enter User value");
OSCCAL_UV = Int_from_PC_Basic(digits);            

  
/*********************************************/
Get_ready_to_calibrate;                         //Test value of OSCCAL entered by user
if(OSCCAL_UV == 0xFF)OSCCAL = OSCCAL_WV;        //If 0xFF reinstate working value
else OSCCAL = OSCCAL_UV;                         //OSCCAL test value
calibrate_without_sign_plus_warm_up_time;               
close_calibration;
  
if(cal_error > 1750)                              //Error resulting from User OSCCAL exceeds 1750
{String_to_PC_Basic("\r\nError too large");
eeprom_write_byte((uint8_t*)0x3FE, 0xFF);         //Reset OSCCAL values storred in EEPROM
eeprom_write_byte((uint8_t*)0x3FF, 0xFF);
OSCCAL = OSCCAL_WV;}                               //Reinstate default value     
  
/*************************************************/
else{
  
eeprom_write_byte((uint8_t*)0x3FE, OSCCAL_UV);    //save user OSCCAL to EEPROM
eeprom_write_byte((uint8_t*)0x3FF, OSCCAL_UV); 
if(OSCCAL_UV == 0xFF) OSCCAL = OSCCAL_WV;       //Reinstate working value
else {OSCCAL = OSCCAL_UV;
OSCCAL_WV = OSCCAL;}  

String_to_PC_Basic("\r\nValues saved to EEPROM\t");
Int_to_PC_Basic(eeprom_read_byte((uint8_t*)0x3FE));
Char_to_PC_Basic('\t');
Int_to_PC_Basic(eeprom_read_byte((uint8_t*)0x3FF));}
wdt_enable(WDTO_15MS);
  while(1);

}

/*****************************************************************************************************************/
long compute_error(char local_error_mode, char local_cal_mode, char sign)            //char OSCCAL_test_value)   
    {long error;
    char Num_1, Num_2;
    
    if (local_cal_mode == 1){Num_1 = 2; Num_2 = 1;}
    if (local_cal_mode == 2){Num_1 = 6; Num_2 = 4;}
    if (local_cal_mode == 5){Num_1 = 15; Num_2 = 10;}
    
    EA_counter = 0;                         //Compute error for each value of OSCCAL 10 times
    error_SUM = 0;
    while(EA_counter < Num_1);EA_counter = 0;
    error = error_SUM;
    if ((!sign) && (error < 0)) error *= (-1);
   return error/Num_2;}


/******************************************************************************************************************/
void initialise_timers_for_cal_error(void){
TCNT1=0;TCCR1B = 0;                                 //Reset and halt T1
TCCR2B =  0x0;  while(ASSR & (1 << TCR2BUB));       //Halt T2
TCCR2A = 0; while(ASSR & (1 << TCR2AUB));           //Reset T2 
TCNT2=0; while(ASSR & (1 << TCN2UB)); }             //Reset TCNT2


void start_timers_for_cal_error(void)
{TCCR2B = 1;   
while(ASSR & (1 << TCR2BUB));
TCCR1B = 1;}
  
  
ISR(TIMER1_OVF_vect) {T1_OVF += 1;}


ISR(TIMER2_OVF_vect) {
long TCNT1_BKP;

TCCR1B = 0;                                     //Halt T1
TCNT1_BKP = TCNT1;                              //Copy the value of TCNT1
TCNT1 = 0;                                      //Clear TCNT1
TCCR1B = 1;                                     //Get T1 running again ASAP (Note T2 has not stopped running)
if(EA_counter < cal_mode)T1_OVF = 0;            //Ignore first 5 results
else
{switch(T1_OVF){
case 0: error_SUM = error_SUM + (TCNT1_BKP - 62500); break;
case 1: error_SUM = error_SUM + (TCNT1_BKP - 62500 + 65536); break;
case 2: error_SUM = error_SUM + (TCNT1_BKP - 62500 + 131072); break;}
T1_OVF = 0;}EA_counter++;}



/*******************************************************************************************************************/
  
