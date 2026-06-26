



#include "UNO_AVR_programmer.h"
#define Version "UNO_programmes_328_prototype\r\n" 

int main (void){ 

setup_328_HW;                                                         //Reduces clock to 8MHz"

Reset_L;                                                              //Put target in reset state to dissable UART

while(1){
do{sendString("s  ");} 
while((isCharavailable(255) == 0));                                   //User prompt 
if(receiveChar() == 's')break;}
sendString("\r\n");

Atmel_powerup_and_target_detect;                                      //Leave target in programming mode                              


sendString(" detected.\r\n\r\nTo program flash:  press -P- for bootloader or \
-p-  for other routines,\r\n\
Press -r- to run target program,\r\n");

while(1){
op_code = waitforkeypress();
switch (op_code){

case 'r':                                //Wait for UNO reset
sendString("Set BR to 57600 then press AK\r\n");
USART_init(0,16);
waitforkeypress();
Exit_programming_mode; break;


case 'e': Prog_EEPROM(); SW_reset; break;

case 'd':                                                             //Delete contents of the EEPROM
sendString("\r\nReset EEPROM! D or AOK to escape");                   //but leave cal data.
newline();
if(waitforkeypress() == 'D'){
sendString("5 sec wait");
for (int m = 0; m < EE_top; m++)  
{Read_write_mem('I', m, 0xFF);}                                       //Write 0xFF to all EEPROM loactions bar the top 3
sendString(" Done. \r\nPress D to delete cal bytes or AOK\r\n");
if(waitforkeypress() == 'D')
{for (int m = EE_top; m < EE_top + 3; m++)Read_write_mem('I', m, 0xFF);}
}
SW_reset;break;

case 'x': SW_reset; break;
default: break;} 

if ((op_code == 'p')||(op_code == 'P')) break;} 
sendString("Send hex file (or x to escape).\r\n");

Program_Flash_Hex();
Verify_Flash_Hex();

sendString("\r\nProgrammming completed\r\n");
cli();
sendString (Version);
newline();

Read_write_mem('I', EE_size - 4, \
(Atmel_config(signature_bit_2_h, signature_bit_2_l)));                  //Define target type on target device
Read_write_mem('I', EE_size - 5, \
(Atmel_config(signature_bit_3_h, signature_bit_3_l)));       

Read_write_mem('I', 0x3F4, 0xF3);                                          //Initialise EEP locations for PRN use

sendString("Set BR to 57600 then press AK\r\n");
USART_init(0,16);
waitforkeypress();
{Exit_programming_mode; }                                               //Wait for UNO reset

return 1;}



/***************************************************************************************************************************************************/
ISR(USART_RX_vect){
switch (op_code){
case 'p':
case 'P': upload_hex(); break;}}



/***************************************************************************************************************************************************/
