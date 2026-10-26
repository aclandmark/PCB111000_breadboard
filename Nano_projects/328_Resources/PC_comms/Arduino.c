void real_divide(long, long, long *, long *) ;





/**********************************************************************************************************************************************************************************/
char isCharavailable_A (int m){int n = 0;								//Version of isCharavailable_Basic() that uses the Arduino library
while (!(Serial.available())){n++;	wdr();			
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}	
return 1;}	



/**********************************************************************************************************************************************************************************/
char waitforkeypress_A (void){											//Version of waitforkeypress_Basic() that uses the Arduino library
while (!(Serial.available()))wdr();	
return Serial.read(); }



/**********************************************************************************************************************************************************************************/
char wait_for_return_key_A(void){                  						//Returns key presses one at a time
char keypress,temp;
while(1){																//Remain in while loop until a character is received
if (isCharavailable_A(8)){												//Pauses but returns 1 immediately that a character is received
keypress = Serial.read();												//Skip if no character has been received 
break;}}																//Exit while loop when character has been read
if((keypress == '\r') || (keypress == '\n')){							//Detect \r\n, \r or \n and converts to \r
if (isCharavailable_A(1)){temp = Serial.read();}
keypress = '\r';}
return keypress;}



/**********************************************************************************************************************************************************************************/
void newline_A(void){Serial.write ("\r\n");}




/**********************************************************************************************************************************************************************************/
char decimal_digit_A (char data){											//Returns 1 if data is a character of 0 to 9 inclusive
if (((data > '9') || (data < '0')) )return 0;							//Otherwise return zero
else return 1;}



/*********************************************************************/
char hex_digit (char data){
switch(data){
case '0': case '1': case '2': case '3': case '4': case '5': case '6':
case '7': case '8': case '9': case 'A': case 'B': case 'C': case 'D':
case 'E': case 'F': return 1; break;
default: return 0; break;}}



/**********************************************************************************************************************************************************************************/
void Check_num_for_to_big_or_small(float num)											//Exits if the result of floating point arithmetic exceeds permitted limits 
{unsigned long * long_ptr;
long_ptr = (unsigned long *)&num;														//Enables floating point number to be read as a 32 bit integer 
if (*long_ptr == 0x7F800000){Serial.write("+ve Num too large\r\n"); eeprom_write_byte((uint8_t*)0x1FA, 0);SW_reset;}
if (*long_ptr == 0xFF800000){Serial.write("-ve Num too large\r\n"); eeprom_write_byte((uint8_t*)0x1FA, 0); SW_reset;}
if (*long_ptr == 0X0){Serial.write("+ve Num too small\r\n"); eeprom_write_byte((uint8_t*)0x1FA, 0); SW_reset;}
if (*long_ptr == 0X80000000){Serial.write("-ve Num too small\r\n"); eeprom_write_byte((uint8_t*)0x1FA, 0); SW_reset;}}



/**********************************************************************************************************************************************************************************/






long Real_Num_from_PC(char digits[], long* divisor, char * decimal_places){    
char keypress;
int digit_counter = 0;
newline_A();

*divisor = 0;
*decimal_places = 0;
while(1){
if ((keypress = wait_for_return_key_A())  =='\r')break; 
if (keypress == '.'){*divisor = 1;
Serial.write('.');}
if (decimal_digit_A(keypress))
{ Serial.write(keypress);
  digits[digit_counter++] = keypress;
if (*divisor) {*divisor *= 10;
*decimal_places += 1;}}}
if(!(*divisor))*divisor = 1;
digits[digit_counter] = '\0' ;                                                 
return atol (digits);}



/****************************************************************************************************/
void print_fpn_as_binary(float fpn, char sym){
  unsigned long mask = (unsigned long)0x80000000;
long int_num;

int_num = *(long*)&fpn; 
for (int m = 0; m <= 31; m++){

  switch(m)
 { case 1:
  case 5:
  case 9:
  case 13:
  case 17:
  case 21:
  case 25:
  case 29: Serial.write(' ');}  
  
  if ((unsigned long)int_num & (mask)) Serial.write('1'); else Serial.write('0');
 mask = mask >> 1;
  } Serial.write(sym);Serial.write('\t');}
  
  
  
  
  /******************************************************************************************/
void Int_Num_to_PC_A
(long Int_num, char * num_as_string, char next_char)			//Same as Unsigned_Int_to_PC()
{
ltoa(Int_num, num_as_string, 10);								//Long to askii
Serial.print(num_as_string);Serial.print(next_char);}
