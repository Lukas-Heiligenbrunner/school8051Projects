/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

//#include "compiler_defs.h"
//#include "C8051F330_defs.h"
#include <C8051F330.h>

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Timer_Init()
{
    TCON      = 0x40;
    TMOD      = 0x21;
    CKCON     = 0x08;
    TL0       = 0x2F;
    TH0       = 0xB0;
    TH1       = 0x96;
}

void UART_Init()
{
    SCON0     = 0x10;
}

void Port_IO_Init()
{
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Unassigned,  Open-Drain, Digital
    // P0.2  -  Unassigned,  Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  TX0 (UART0), Open-Drain, Digital
    // P0.5  -  RX0 (UART0), Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Skipped,     Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Skipped,     Open-Drain, Analog
    // P1.7  -  Unassigned,  Open-Drain, Digital

    P1MDIN    = 0xBF;
    P1SKIP    = 0x48;
    XBR0      = 0x01;
    XBR1      = 0x40;
}

void Oscillator_Init()
{
    OSCICN    = 0x83;
}

void Interrupts_Init()
{
    IE        = 0x02;
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Timer_Init();
    UART_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}
