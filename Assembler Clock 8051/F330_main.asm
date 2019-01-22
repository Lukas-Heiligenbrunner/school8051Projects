;-----------------------------------------------------------------------------
; template_main.asm
;-----------------------------------------------------------------------------
; HTBLA Steyr  -  Elektronik und Technische Informatik
;
; Author:   Felix Hutsteiner
; Version:  1.0
;
; Changes:
;      		17.3.2014	created
;
;
; Target:         C8051F330 Silicon Labs
; Tool chain:     Keil µVision 4
;
; Program Description:
;    		Base project for F330 interrupt application
;

;------------------------------------------------------------------------------
; PROCESSOR definition for assembler (SFR names)
;------------------------------------------------------------------------------
$INCLUDE (C8051F330.INC)	; Remove checkbox "Define 8051 SFR names" in project options A51 !!!


;------------------------------------------------------------------------------
; SYMBOL definitions, EXTRN references, PUBLIC definitions
;------------------------------------------------------------------------------
EXTRN	code (Init_Device)
EXTRN	code (isr_T0)
EXTRN	code (isr_UART)

;------------------------------------------------------------------------------
; RESET and INTERRUPT VECTORS (absolute code segment)
;------------------------------------------------------------------------------
	; Reset Vector
	cseg AT 0
	ljmp MAIN			; Jmp to the main routine

	cseg AT 0x000B ; Timer 0 interrupt service vector
	ljmp isr_T0 ; jump to the interrupt service routine

	cseg AT 0x0023 ; UART interrupt servie vector
	ljmp isr_UART

;------------------------------------------------------------------------------
; STACK segment
;------------------------------------------------------------------------------
?STACK 		segment IDATA ; defining stack segment

	rseg	?STACK
	ds		10			; reserve 10 bytes for stack


;------------------------------------------------------------------------------
; Data segments
;------------------------------------------------------------------------------



;------------------------------------------------------------------------------
; CODE segments
;------------------------------------------------------------------------------
MAIN		segment	CODE ; defining main segment

	rseg	MAIN
	using	0			; switch to register bank 0

  anl PCA0MD, #1011$1111B   	; disable the watchodog timer
	mov		sp,#?STACK-1	;init stack pointer

	call	Init_Device		;init Peripherals
;-----------------------------------------------------------------------------

	ANL TMOD,#0xF0
	ORL TMOD,#0x01

	MOV TH0,#HIGH(45119)
	MOV TL0,#LOW(45119)				; set timer reload value (10ms)

	SETB ET0					//timer0 interrupt enabled
	SETB TR0					; set Timer 0 run flag
	SETB EA						; Enable all flag

	CLR TR1 					; timer 1 run flag
	ANL TMOD,#0x2f		; setting timer mode
	MOV TH1,#0xfd			; Timer 1 High byte
	MOV SCON0,#0x52		; set uart mode
	SETB TR1					; start timer1
	SETB ES0					; UART interrupt enabled
	jmp		$
;------------------------------------------------------------------------------
; End of file.
;------------------------------------------------------------------------------
END
