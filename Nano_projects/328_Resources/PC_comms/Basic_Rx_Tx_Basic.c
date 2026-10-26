

void String_to_PC_B(const char*);
char wait_for_return_key_B(void);


void display_real_num(char*);
void invert_num_string(char *);


#define char_present 	UCSR0A & (1 << RXC0)

/*********************************************************************/
void setup_PC_comms_B (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
UCSR0B = 0;
UBRR0H = UBRROH_N;  									
UBRR0L = UBRR0L_N;  								
UCSR0A = (1 << U2X0);
UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);}



/*********************************************************************/
char isCharavailable_B (int m){int n = 0;
while (!(UCSR0A & (1 << RXC0)))											//Return 1 immediately that a character is received
{n++; wdr();															//No character yet: Increment counter											
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}							//Counter overflows before a character has been received: return zero
return 1;}



/*********************************************************************/
char waitforkeypress_B (void){										//Wait here indefinitely but prevent WDTime-out
while (!(UCSR0A & (1 << RXC0)))wdr();	
return UDR0;}		



/*********************************************************************/
char Char_from_PC_B(void)											//Return character detected by "isCharavailable()"
{return UDR0;}



/**********************************************************************************************************************************************************************************/
void Char_to_PC_B(char data){														
while (!(UCSR0A & (1 << UDRE0)));										//Wait for transmit buffer to be ready to accept new data
UDR0 = data;}															//Load data register with "data" and it will immediately be transmitted



/**********************************************************************************************************************************************************************************/
void newline_B(void){String_to_PC_B ("\r\n");}



/**********************************************************************************************************************************************************************************/
void String_to_PC_B(const char s[]){								//Transmits a sequence (string) of characters and requires the address in program memory of the first one
int i = 0;																//"i" gives the relative address of the next character to be transmitted
while(i < 200){															//Transmits up to 200 characters using "Char_to_PC()" or untill the null (\0) character is detected
if(s[i] == '\0') break;
Char_to_PC_B(s[i++]);}}												//Transmit character and increment "i" so that it addresses (points to) the next one.



/**********************************************************************************************************************************************************************************/
void Num_string_to_PC_B(char s[]){
{int m = 0;while(1)
{if(!(s[m]))break; 
else Char_to_PC_B(s[m++]);}}}



/**********************************************************************************************************************************************************************************/
char decimal_digit_B (char data){											//Returns 1 if data is a character of 0 to 9 inclusive
if (((data > '9') || (data < '0')) )return 0;							//Otherwise return zero
else return 1;}




/**********************************************************************************************************************************************************************************/
void Int_to_PC_B (long number)
{ int i = 0;
  char s[12];
   do
  { s[i++] = number % 10 + '0';
  }
  while ((number = number / 10) > 0);
  s[i] = '\0';
  for (int m = i; m > 0; m--)Char_to_PC_B(s[m - 1]);
  Char_to_PC_B(' ');
}



/**********************************************************************************************************************************************************************************/
long Int_from_PC_B(char digits[]){
char keypress;
for(int n = 0; n<=11; n++) digits[n] = 0; 

do
{keypress =  waitforkeypress_B();} 
while (!(decimal_digit_B(keypress)));                                      //(non_decimal_char(keypress));  //Not -,0,1,2,3,4,5,6,7,8 or 9
digits[0] = keypress;

while(1){
if ((keypress = wait_for_return_key_B())  =='\r')break;
if (decimal_digit_B (keypress))                                           //012345678or9  :Builds up the number one keypress at a time
{for(int n = 7; n>=1; n--)
digits[n] = digits[n-1];                                                //Shifts display left for each keypress
digits[0] = keypress;}}
invert_num_string(digits);           
return atol(digits);
}


/***********************************************************************************************************************************************************************************/
void Hex_and_Int_to_PC_B (char radix, int number)
{ int i = 0;
 char sign = '+';
  unsigned char s[12];
unsigned int num;
  
if ((number < 0) && (radix == 10)){sign = '-'; number *= -1;}
    num = (unsigned)number;  
   
   do  { s[i] = num % radix;// + '0';
if (s[i] < 10)s[i] += '0'; else s[i] += '7';
   i += 1;  }
  while ((num = num / radix) > 0);
  s[i] = '\0';
  if ((sign == '-') && (radix == 10)){Char_to_PC_B('-');}
  for (int m = i; m > 0; m--)Char_to_PC_B(s[m - 1]);
  Char_to_PC_B(' ');}



/***********************************************************************************************************************************************************************************/
void Long_Hex_and_Int_to_PC_B (char radix, long number)
{ int i = 0;
 char sign = '+';
  unsigned char s[12];
unsigned long num;
  
if ((number < 0) && (radix == 10)){sign = '-'; number *= -1;}
    num = (unsigned long)number;  
   
   do  { s[i] = num % radix;// + '0';
if (s[i] < 10)s[i] += '0'; else s[i] += '7';
   i += 1;  }
  while ((num = num / radix) > 0);
  s[i] = '\0';
  if ((sign == '-') && (radix == 10)){Char_to_PC_B('-');}
  for (int m = i; m > 0; m--)Char_to_PC_B(s[m - 1]);
  Char_to_PC_B(' ');}



/**********************************************************************************************************************************************************************************/
char wait_for_return_key_B(void){                  						//Returns key presses one at a time
char keypress,temp;
while(1){																//Remain in while loop until a character is received
if (isCharavailable_B(8)){												//Pauses but returns 1 immediately that a character is received
keypress = Char_from_PC_B();												//Skip if no character has been received 
break;}}																//Exit while loop when character has been read
if((keypress == '\r') || (keypress == '\n')){							//Detect \r\n, \r or \n and converts to \r
if (isCharavailable_B(1)){temp = Char_from_PC_B();}
keypress = '\r';}
return keypress;}



/**********************************************************************************************************************************************************************************/
void invert_num_string(char * s){
int c, i, j;

for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
c = s[i];
s[i] = s[j]; s[j] = c;
}}





void Real_num_from_PC_B(char display_buffer[]){              //Operation is similar to that of Int_KBD_to_display()
char keypress;
char cr_keypress;

cr_keypress = 0;                                                //Set to one when carriage return keypress terminates the string
for(int n = 0; n<=11; n++) display_buffer[n] = 0;              	//Clear the buffer used to the string

while(1){														//Remain in loop until a valid character is received
keypress = waitforkeypress_B();
if ((!(decimal_digit_B(keypress)))
&& (keypress != '-')
&& (keypress != '.'))continue;                                	//Ignore keypress if it is not OK
display_buffer[0] = keypress;
break;}

if (keypress == '.')display_buffer[0] = '0' | 0x80;				//Bit 7 is set if the digit includes the decimal point

display_real_num(display_buffer);                                      //Update display with the first key press

while(1){
if ((keypress = wait_for_return_key_B())  =='\r')break;           //Stay in loop until return key press is detected

if ((decimal_digit_B(keypress)) || (keypress == '.')				//Check for valid keypresses
|| (keypress == '\b')|| (keypress == '-'))

{if(keypress == '\b'){for (int n = 0; n < 7; n++)				//Backspace keypress
display_buffer[n] = display_buffer[n + 1];
display_buffer[7] = 0;}

else

{if(keypress != '.')
{for(int n = 7; n>=1; n--)                                    	//Shift display for each new keypress except '.'
display_buffer[n] = display_buffer[n-1];
display_buffer[0] = keypress;}                                  //Add new keypress           
else display_buffer[0] |= 0x80;}                				//Integrate decimal point with its parent digit

display_real_num(display_buffer);}}}
