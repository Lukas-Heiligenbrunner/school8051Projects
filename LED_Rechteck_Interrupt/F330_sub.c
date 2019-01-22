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
void serielle_Ausgabe (char out);
//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

char uart_in;									//variable fuer das speichern des entgegengenommenen Char
sbit led_pin = P1^3;					//variable zum einschalten des Pins/LED
int max_lengh=100;						//laenge der Periode; 100 fuer 100%
 
//Interrupt fuer die UART
void  serielle_Eingabe (void) interrupt 4{
	if(RI0){
		uart_in = SBUF0;
		RI0 = 0;
		
		serielle_Ausgabe(uart_in);
		
		dutycycle=uart_in-'0';
		dutycycle=dutycycle*10;
	}
}

void serielle_Ausgabe (char out){
	while(!TI0){}
	SBUF0=out;
	TI0=0;
}


int count;
void  Timer (void) interrupt 1{
	if(tempCycle<=count){
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