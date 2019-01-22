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

//extern void testfunction (void);
extern void Init_Device();
extern void serielle_Eingabe (void);
//-----------------------------------------------------------------------------
// main() Routine
//-----------------------------------------------------------------------------


void main (void) {

  PCA0MD &= 0xbf;					// Watchdogtimer abschalten
  Init_Device();

	EA=1;										//alle interrupts aktivieren
	ET0=1;									//enable Timer 0
	ES0=1;			
	TR0=1;									//TimerRunflag setzen um den Timer zu starten
	TI0=1;									//Timer Interrupt aktivieren
	
	
	while (1) {
		// main loop code
		// wie im ASM das JMP $
	}
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------