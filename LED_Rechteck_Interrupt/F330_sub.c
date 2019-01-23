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
int dutycycle =50;
int tempCycle =50;

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void  serielle_Eingabe (void);
void writeSerial (char out);
void writeInt(int out);
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
				string_Print("Exited cycle menu!\n\nMain menu:\n[d] --> duty cycle setzen \n[f] --> pwm frequenz setzen");
			}
			
		}else
		{
			if(uart_in == 'd')
			{
				setmenu=1;
				string_Print("You are in the duty cycle set menu! Exit with c \nplease set the cycle in %\n");
			}
		}
		
		dutycycle=uart_in-'0';
		dutycycle=dutycycle*10;
	}
}

void writeSerial (char out){
	while(!TI0){}
	SBUF0=out;
	TI0=0;
}

void writeInt(int out){
	tempint = out;
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
	if(tempCycle==count){
		led_pin = 1;
		count++;
	}else if(count==max_lengh){
		tempCycle = dutycycle;
		led_pin = 0;
		count=0;
	}else{
	count++;
	}
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------