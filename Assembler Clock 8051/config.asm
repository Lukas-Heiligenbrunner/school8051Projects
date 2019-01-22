;------------------------------------
;-  Generated Initialization File  --
;------------------------------------

$include (C8051F330.inc)

public  Init_Device

INIT SEGMENT CODE
    rseg INIT

; Peripheral specific initialization functions,
; Called from the Init_Device label
Timer_Init:
    mov  TCON,      #040h
    mov  TMOD,      #021h
    mov  CKCON,     #008h
    mov  TL0,       #02Fh
    mov  TH0,       #0B0h
    mov  TH1,       #096h
    ret

UART_Init:
    mov  SCON0,     #010h
    ret

Port_IO_Init:
    ; P0.0  -  Unassigned,  Open-Drain, Digital
    ; P0.1  -  Unassigned,  Open-Drain, Digital
    ; P0.2  -  Unassigned,  Open-Drain, Digital
    ; P0.3  -  Unassigned,  Open-Drain, Digital
    ; P0.4  -  TX0 (UART0), Open-Drain, Digital
    ; P0.5  -  RX0 (UART0), Open-Drain, Digital
    ; P0.6  -  Unassigned,  Open-Drain, Digital
    ; P0.7  -  Unassigned,  Open-Drain, Digital

    ; P1.0  -  Unassigned,  Open-Drain, Digital
    ; P1.1  -  Unassigned,  Open-Drain, Digital
    ; P1.2  -  Unassigned,  Open-Drain, Digital
    ; P1.3  -  Skipped,     Open-Drain, Digital
    ; P1.4  -  Unassigned,  Open-Drain, Digital
    ; P1.5  -  Unassigned,  Open-Drain, Digital
    ; P1.6  -  Skipped,     Open-Drain, Analog
    ; P1.7  -  Unassigned,  Open-Drain, Digital

    mov  P1MDIN,    #0BFh
    mov  P1SKIP,    #048h
    mov  XBR0,      #001h
    mov  XBR1,      #040h
    ret

Oscillator_Init:
    mov  OSCICN,    #083h
    ret

Interrupts_Init:
    mov  IE,        #002h
    ret

; Initialization function for device,
; Call Init_Device from your main program
Init_Device:
    lcall Timer_Init
    lcall UART_Init
    lcall Port_IO_Init
    lcall Oscillator_Init
    lcall Interrupts_Init
    ret

end
