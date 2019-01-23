//-----------------------------------------------------------------------------
// template.c
//-----------------------------------------------------------------------------
// HTBLA Steyr  -  Elektronik und Technische Informatik
// 
// Author:   Felix Hutsteiner
// Version:  1.0
// 
// Changes:  
//      		5.2.2014	created     
//
//
// Target:         C8051F330 Silabs
// Tool chain:     Keil µVision 4 
//
// Program Description:
//    	This program is a template for c51 subfunction modules
//


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <C8051F330.h>			// SFR declaration

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void  serielle_Eingabe (void);
void writeSerial (char out);
void writeInt(int out);
void printMainMenu();
void string_Print(char  mystring[]);

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

char uart_in;									//variable fuer das speichern des entgegengenommenen Char
sbit led_pin = P1^3;					//variable zum einschalten des Pins/LED
int max_lengh=100;						//laenge der Periode; 100 fuer 100%

int tempint;
int stellennr;



int setmenu = 0;
int freqmenu = 0;
char percentchar[3];
int percent = 100;

char tempintarr[9];

char mainMenChar[80] = "\nMain menu:\n[d] --> duty cycle setzen \n[f] --> pwm frequenz setzen";

//Interrupt fuer die UART
void  serielle_Eingabe (void) interrupt 4{
	if(RI0){
		uart_in = SBUF0;
		RI0 = 0;
		
		writeSerial(uart_in);
		if(setmenu == 1)
		{
			if(uart_in == 'c')
			{
				setmenu = 0;
				string_Print("Exited cycle menu!\n");
				printMainMenu();
			}else if(uart_in == 13){
			
			percent=0;
			if(percentchar[0] != 0 && percentchar[1] == 0 )
			{
				percent = percentchar[0]-'0';
				writeSerial(percentchar[0]);
			}else if(percentchar[0] != 0 && percentchar[1] != 0)
			{
				percent = (percentchar[0]-'0')*10+(percentchar[1]-'0');
			}
			percentchar[0]=0;
			percentchar[1]=0;
			percentchar[2]=0;
			
			string_Print("You selected: ");
			writeInt(percent);
			printMainMenu();
			setmenu =0;
			
		}else {
				
				if(percentchar[0] == 0)
				{
					percentchar[0] = uart_in;
				} else if(percentchar[1] == 0){
					percentchar[1] = uart_in;
				} else{
					percentchar[2] = uart_in;
					percent = (percentchar[0]-'0')*100+(percentchar[1]-'0')*10+(percentchar[2]-'0');
					percentchar[0]=0;
					percentchar[1]=0;
					percentchar[2]=0;
					
					if(percent > 100)
					{
						percent = 100;
					}
					
					string_Print("You selected: ");
					writeInt(percent);
					printMainMenu();
					
					setmenu =0;
				}
			}
			
		}else if(freqmenu == 1){ //todo frequency selection
			
			if(uart_in == 'c')
			{
				freqmenu = 0;
				string_Print("Exited cycle menu!\n");
				printMainMenu();
			}else if(uart_in == 13){
			string_Print("Exited cycle menu!\n");
			printMainMenu();
			freqmenu =0;
			
		}
		
		}else{
			if(uart_in == 'd')
			{
				setmenu=1;
				string_Print("\n Welcome to the duty cycle set menu: exit with c or set set in %\n:");
			}else if(uart_in == 'f')
			{
				freqmenu=1;
				string_Print("\n Welcome to the freqmenu menu: exit with c or set set in %\n:");
			}
		}
	}
}

void writeSerial (char out){
	while(!TI0){}
	SBUF0=out;
	TI0=0;
}

void printMainMenu()
{
	string_Print(mainMenChar);
}

void writeInt(int out){ // todo to print right order
	tempint = out;
	if(tempint == 0)
	{
		writeSerial(0+ '0');
	}
	while(tempint > 0){
		writeSerial((tempint%10) + '0');
		tempint = tempint/10;
	}
}

void string_Print(char  mystring[])
{
	int i =0;
	for(i=0;mystring[i] != 0 ;i++)
	{
		writeSerial(mystring[i]);
	}
}


int count;
void  Timer (void) interrupt 1{
	if(count < percent){
		led_pin = 1;
	}else if(count > percent){
		led_pin = 0;
	}
	count++;
	if(count > 100){
	count = 0;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------