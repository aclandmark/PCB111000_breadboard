
#define F_CPU 8000000

#include "Atmega_328_bootloader_header.h"	

#include <util/delay.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdint.h>
#include <stdio.h>

char User_response;
char watch_dog_reset;

#define T0_delay_5ms 5,220

#define T1_delay_200ms 	3, 0x9E62
	void Hex_verification (void);

		void Verify_Flash (char);


#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}






	



		int main (void){									//Loaded at address 0x3580, just ahead of the boot loader section

			if(!(MCUSR & 2)) 								//For EXTRF skip the jmp 0x0000 command
			{asm("jmp 0x0000");}							//Jump to application code for POR and WDTout
			
			MCUSR &= (~(1 << EXTRF));						//Clear EXTRF
			
			setup_watchdog;
			ADMUX |= (1 << REFS0);
			cal_device;
			Initialise_I_O;
			USART_init(0,16);
			for(char p = 0; p<= 100; p++){asm("nop");}
			
			while(1){
				do{sendString("p/r    ");}  while((isCharavailable (250) == 0));
				User_response = receiveChar();
				switch(User_response){
					case 'p': break;
					case 'r': eeprom_write_byte((uint8_t*)0x3EF,0b11111011);
					asm("jmp 0x0000");break;
				default: sendString("?\r\n");continue; break;}
			if(User_response =='p')break;}
			
			sendString("\r\nSend_Atmega 328 Hex file\r\n");

eeprom_write_byte((uint8_t*)0x3EF,0b11111101);
MCUSR = 0;

			MCUCR = (1<<IVCE);  								//Select the interrupt vector table starting at start of boot section
			MCUCR = (1<<IVSEL);
		PageSZ = 0x40; PAmask = 0x3FC0;										//Define flash memory parameters for Atmega 168

		record_length_old=0;
		Flash_flag = 0;  HW_address = 0;
		w_pointer = 0; r_pointer = 0; short_record=0;

		UCSR0B |= (1<<RXCIE0); sei();										//Receive interrupts now active

		new_record();  														//Start reading first record which is being downloaded to array "store"
		start_new_code_block(); 											//Initialize new programming block (usually starts at address zero but not exclusively so)
		Program_record();													//Copy commands from array "store" to the page_buffer
		
		while(1){
			new_record();														//Continue reading subsequent records
			if (record_length==0)break; 										//Escape when end of hex file is reached
			
			switch(short_record){
				case 0: if (space_on_page == (PageSZ - line_offset))				//If starting new page
				{page_address = (Hex_address & PAmask);}break;			//get new page address
				

				case 1:	start_new_code_block();										//Short line with no break in file (often found in WinAVR hex files).
			short_record=0;break;}
			
		Program_record();}											//Continue filling page_buffer

		UCSR0B &= (~(1<<RXCIE0));	cli();							//download complete, disable UART Rx interrupt
		
		UCSR0B &= (~(1 << RXEN0));									//disable Rx module
		DDRD &= (~(1 << DDD0)); PORTD |= (1 << DDD0);				//Set Rx pins to week pull up
		Timer_T0_sub(T0_delay_5ms);									//Time to download spurious characters (i.e. 0000000FF)
		
		
		if((Flash_flag) && (!(orphan))){write_page_SUB(page_address);}	//Burn final contents of page_buffer to flash
		if(orphan) {write_page_SUB(page_address + PageSZ);}cli();


		clear_read_block();											//Subroutine provided in assembly file
	
	Hex_verification();
		
	wdt_enable(WDTO_15MS);
	while(1);
	return 1;}											//Jump to verification routine




	/***********************************************************************************************************************************/
	ISR(USART_RX_vect){
		
		unsigned char Rx_askii_char;
		
		unsigned char Rx_Hex_char=0;
		int local_pointer;
		
		Rx_askii_char = receiveChar();
		
		if (Rx_askii_char == ':')counter = 0;									//First char of hex file is ':'
		else {if (Rx_askii_char <= '9')
			Rx_Hex_char = Rx_askii_char - '0'; 										//Convert chars '0' to '9' to numbers 0 to 9
		else Rx_Hex_char = Rx_askii_char - '7';}								//and chars 'A' to 'F' to numbers 0xA to 0xF

		switch (counter){
			case 0x0:  	break;														//Detect -:- at start of new line
			case 0x1: 	tempInt1 = Rx_Hex_char<<4;  break;							//Acquire first digit
			case 0x2: 	tempInt1 += Rx_Hex_char;  									//Acquire second digit and combine with first to obtain number of commands in line
			char_count = 9 + ((tempInt1) *2); 										//Calculate line length in terms of individual characters
			local_pointer = w_pointer++; 											//Update pointer to array "store"
			store[local_pointer] = tempInt1; break;									//Save the number of commands in the line to the array
			case 0x3: 	tempInt1 = Rx_Hex_char<<4;  break;							//Next 4 digits give the address of the first command in the line
			case 0x4:	tempInt1 += Rx_Hex_char; tempInt1=tempInt1<<8;
			break;																	//Acquire second digit and combine it with first
			case 0x5:	tempInt1 += Rx_Hex_char<<4;  break;							//Continue for third digit
			case 0x6: 	tempInt1 += Rx_Hex_char; 									//Acquire final digit and calculate address of next command
			local_pointer = w_pointer++; 											//Update pointers to array "store"
			store[local_pointer] = tempInt1; break;									//Save address of next command to array "store"
			case 0x7: 	break;														//chars 7 and 8 are not used
			case 0x8: 	break;
		default: 	break;}

		if ((counter > 8)&&(counter < char_count)){								//Continue to acquire, decode and store commands
			if ((counter & 0x03) == 0x01){tempInt1 = Rx_Hex_char<<4;}				//Note: Final two chars at the end of every line are ignored
			if ((counter & 0x03) == 0x02)  {tempInt1 += Rx_Hex_char;}
			if ((counter & 0x03) == 0x03)  {tempInt2 = Rx_Hex_char<<4;}
			if ((counter & 0x03) == 0x0)  	{tempInt2+= Rx_Hex_char;
				tempInt2=tempInt2<<8;tempInt1+=tempInt2;
				local_pointer = w_pointer++;
			store[local_pointer] = tempInt1; }}

			counter++;
		w_pointer = w_pointer & 0x1F;	}  											//Overwrites array after 32 entries




		/*********************************************************************/
		

		
		void Hex_verification (void){
			char mode;
			
			sendString("\r\nVerification: 0 to skip, 1 for full or 2 for basic\r\n");
			
			Timer_T1_sub(T1_delay_200ms);
			
			UCSR0B |= (1 << RXEN0);										//Turn receiver back on again
			
			mode = waitforkeypress() - '0';
			if (mode)
			{	prog_counter = FlashSZ;
				Verify_Flash(mode - 1);
				
				sendString("Hex_file_size:	0x");								//Confirm file sizes are all identical
				Hex_to_PC(read_ops*2);

				sendString("\r\nFuses E, H, L and lock:\t");						//Print out device configuration bytes
				address_in_flash = 0;
				for(int m = 0; m<4; m++){
					switch(m){
						case 0: address_in_flash = 2; break;						//Print Fuse byte Extended
						case 1: address_in_flash = 3; break;						//Print Fuse byte High
						case 2: address_in_flash = 0; break;						//Print Fuse byte
					case 3: address_in_flash = 1; break;}							//Print lock byte

					Prog_mem_address_H = address_in_flash >> 8;
					Prog_mem_address_L = address_in_flash;
					read_config_bytes();
				short_num_to_PC(Flash_readout);	sendChar('\t');	}}
				
				newline(); newline();											//Jump to here if verification not required

				
				}
		
		
		
		void Verify_Flash (char print_mode){
			int  line_counter = 0;												//Controls printing of hex file
			int line_no;														//Refers to the .hex file
			signed int phys_address;											//Address in flash memory
			signed int prog_counter_mem;										//Initialized with size of .hex file used for programming
			
			phys_address = 0;  read_ops=0;
			line_no = 0; prog_counter_mem = prog_counter;


			while(1){if((prog_counter_mem <= 0))break;								//print out loop starts here, exit when finished
				Hex_cmd = readCMD(phys_address);
				phys_address++;
				
				if (print_mode){
					if(!(line_no%10))sendChar('*');
				Timer_T0_sub(T0_delay_5ms);}
				
				else															//Print out required: Print all lines or just a selection
				{newline(); Hex_to_PC ((phys_address-1)*2);
					sendString("   "); line_counter++;
				Hex_to_PC (Hex_cmd); 	}									//Print first command in askii or hex
				
				
				read_ops++;														//Value to be sent to PC for comparison with the hex filer size
				prog_counter_mem--;												//"prog_counter_mem" decrements to zero when the end of the file is reached
				for(int m=0; m<7; m++){    										//Read the next seven locations in the flash memory
					Hex_cmd = readCMD(phys_address);
					phys_address++;
					if(Hex_cmd == 0xFFFF)break;									//Read 0xFFFF: return to start of print out loop
					prog_counter_mem--;
					if(!(print_mode))
					{Timer_T0_sub(T0_delay_5ms);								//5ms delay prevents PC from getting overwhelmed with characters
					Hex_to_PC (Hex_cmd);}
					read_ops++;
				if((phys_address >= FlashSZ))break;}
				if ( (!(print_mode)) && (!(line_counter%8)))sendString("\r\n");
				
				line_no++;
			if ((phys_address >= FlashSZ) || (Hex_cmd == 0xFFFF))break;}
		newline(); }
		
		
		


