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

//Timerberechnung
	//Oszillatorfrequenz = 24,5MHz
	//24,5MHz / 12 = 2,04MHz
	//2,04MHz ^= 490ns
	//Zählschritte = 10ms / 490ns = 20416,66
	//Reloadwert = 65536 - 20416,66 = 45119,33 ^= 0xB03F


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
extern void string_Print(char  mystring[]);
extern void writeInt(int out);
extern void printMainMenu();
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
	
	printMainMenu();
	
	while (1) {
		// main loop code
		// wie im ASM das JMP $
	}
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------