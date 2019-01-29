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
//
//			This program is a template for c51 main modules
//


//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F330.h>			// SFR declaration
#include <stdio.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

sbit motor_r = P0^0;			// 1: Motoranschluss für Rechtslauf an +UB, 0: ... Masse
sbit motor_l = P0^1;			// 1: Motoranschluss für Linkslauf an +UB, 0: ... Masse
sbit fb_inh = P1^2;				// 1: Motorbrücke aktiviert, 0: Motorbrücke gesperrt

// Achtung: für Rechtslauf muss motor_l auf 0 sein, und umgekehrt !!!!!!!!!



//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------

extern void init_device();
extern void writeSerial(char out);
extern void string_Print(char mystring[]);



//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------

void main (void) small {
	
	PCA0MD &= 0xbf;					// Watchdogtimer abschalten

  init_device();					// Init laut Config-Tool
	
	EA=1;										//alle interrupts aktivieren
	ET0=1;									//enable Timer 0
	ES0=1;			
	TR0=1;									//TimerRunflag setzen um den Timer zu starten
	TI0=1; //Timer Interrupt aktivieren
	
	
	//fb_inh = 1;
	//motor_r = 1;
	//motor_l = 0;
	
	string_Print("[l] --> links laufen 100%\n[r] --> rechts laufen 100% \n[p] --> auslaufen lassen\n[s] --> hart stoppen\n[d] --> duty cicle optionen");
	
	while (1) {
		// main loop code
   }
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------