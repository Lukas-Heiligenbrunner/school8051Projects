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

#include <C8051F330.h>			// SFR declaration
#include <stdio.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define PWM_period 100



//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

sbit motor_r = P0^0;			// 1: Motoranschluss für Rechtslauf an +UB, 0: ... Masse
sbit motor_l = P0^1;			// 1: Motoranschluss für Linkslauf an +UB, 0: ... Masse
sbit fb_inh = P1^2;				// 1: Motorbrücke aktiviert, 0: Motorbrücke gesperrt

char uart_in;

int setmenu = 0;
int currpercent = 0;
int temp = 0;

int tempint = 0;


// Achtung: für Rechtslauf muss motor_l auf 0 sein, und umgekehrt !!!!!!!!!



//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

void writeSerial(char out);
void  T0_interrupt (void);
void serial_interrupt (void);
void string_Print(char mystring[]);
void writeInt(int out);

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------


void writeSerial (char out){
	while(!TI0){}
	SBUF0=out;
	TI0=0;
}

void writeInt(int out){
	tempint = out;
	while(tempint > 0){
				tempint = tempint/10;
		writeSerial((tempint%10) + '0');
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

void  T0_interrupt (void) interrupt 1 using 1 {
	
	if(temp <= currpercent)
	{
		//turn on motor
	}else{
		
	}
	
	temp++;

}

void serial_interrupt (void) interrupt 4 using 1 {
	if(RI0){
		uart_in = SBUF0;
		RI0 = 0;
		//writeSerial(uart_in);
		if(setmenu == 1)
		{
			writeSerial(uart_in);
			if(currpercent == 0)
			{
				currpercent = uart_in-30;
			}else if(currpercent/10 < 10)
			{
				currpercent += (uart_in-30)*10;
			}else{
				currpercent += (uart_in-30)*100;
			}
			writeInt(42);
			
			if(uart_in == 'c')
			{
				string_Print("exiting from menu\n");
				setmenu = 0;
			}
		}else{
			if(uart_in == 'l')
			{
				string_Print("links laufen\n");
				fb_inh = 1;
				motor_r = 0;
				motor_l = 1;
				
			}else if(uart_in == 'r')
			{
				string_Print("rechts laufen\n");
				
				fb_inh = 1;
				motor_l = 0;
				motor_r = 1;
			}else if(uart_in == 's')
			{
				string_Print("STOP Motor\n");
				fb_inh = 1;
				motor_r = 0;
				motor_l = 0;
			}else if(uart_in == 'p')
			{
				string_Print("Motor auslaufen lassen\n");
				fb_inh = 0;
				motor_r = 0;
				motor_l = 0;
			}else if(uart_in == 'd')
			{
				string_Print("You are in speed setup with c\nExit withPlease enter speed:\n");
				setmenu = 1;
			}
		}
		
		
		
		
	}
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------