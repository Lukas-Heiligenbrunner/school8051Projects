;-----------------------------------------------------------------------------
; template_sub.asm
;-----------------------------------------------------------------------------
; HTBLA Steyr  -  Elektronik und Technische Informatik
;
; Author:   Lukas Heiligenbrunner
; Version:  1.0
;
; Target:         C8051F330 Silicon Labs
; Tool chain:     Keil µVision 4
;
; Program Description:
;    		This program is a clock written in assembler
;

;------------------------------------------------------------------------------
; PROCESSOR definition for assembler (SFR names)
;------------------------------------------------------------------------------
$INCLUDE (C8051F330.INC)	; Remove checkbox "Define 8051 SFR names" in project options A51 !!!


;------------------------------------------------------------------------------
; SYMBOL definitions, EXTRN references, PUBLIC definitions
;------------------------------------------------------------------------------
public isr_T0
public isr_UART

;------------------------------------------------------------------------------
; Data segments
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
; CODE segments
;------------------------------------------------------------------------------
SUBROUTINES	segment	CODE

	rseg	SUBROUTINES	; Switch to SUBROUTINES segment
	using	0			; Define Symbols AR0 ... AR7.
						; ATTENTION: Bank switching code is not generated

; timer calculation:
; frequency of the crystal = 24,5MHz
; 24,5MHz / 12 = 2,04MHz
; 2,04MHz ≙ 490ns
; count steps every 10ms / 490ns = 20416,66 steps
; reload value = 65536 - 20416,66 = 45122


isr_T0:

		MOV TH0,#HIGH(45122)			; set high byte of timer reload value
		MOV TL0,#LOW(45122)			; set low byte of timer reload value

		; info: R7 --> time ms  R6 --> time sec  R5 --> time minutes R4 --> time hours

		INC R7 ;--> every 10ms increased by 1
		MOV A,R7

		CJNE A, #100 , done ; detection for one second if not skip...
		MOV R7,#0
		INC R6 ;seconds
		; print uart info every second

		call printhours	; printing the hours
		MOV A,#':'
		call writeuart

		call printminutes ; printing the minutes
		MOV A,#':'
		call writeuart

		call printseconds 	; printing the seconds
		call writenewLine	; printing carriage return new line feed


		MOV A,R6
		CJNE A, #60 , done ; detection for one minute if not skip...

		MOV R6,#0
		INC R5 ;minutes


		MOV A,R5
		CJNE A, #60 , done ; detection for one hour if not skip...

		MOV R5,#0
		INC R4 ;hours



		done:

		reti	; reti because of isr
		;----------------------------------
		writeuart:	; function for writing A to uart
		MOV SBUF0, A	; move a to sbuf0
		clr TI0		; clr transmit interrupt flag
		JNB TI0, waituart
		ret

		writenewLine:	; function for printing new line
		MOV A, #13 ; carriage return
		call writeuart

		MOV A, #10 ; new line
		call writeuart
		ret

		printseconds:	; printseconds
		MOV A,R6
		MOV B,#10
		DIV AB		; divide A / B --> result in a and remain in B
		ADD A,#0x30	; add 30 for beiing a ascii char
		call writeuart	; call writing to uart
		MOV A,B
		ADD A,#0x30
		call writeuart	; write second position to uart
		ret

		printminutes:	; printminutes
		MOV A,R5
		MOV B,#10
		DIV AB	; divide A / B --> result in a and remain in B
		ADD A,#0x30	; calc to ascii letter
		call writeuart	; print 10th seconds to uart
		MOV A,B
		ADD A,#0x30
		call writeuart
		ret

		printhours:	;printhours --> same as above with hours
		MOV A,R4
		MOV B,#10
		DIV AB
		ADD A,#0x30
		call writeuart
		MOV A,B
		ADD A,#0x30
		call writeuart
		ret

isr_UART:		; service routine for recognizing chars typed into the uart --> not complete!

		JNB RI0, done 	; jump to the end if interrupt was triggered by program print to uart
		CLR RI0 	; clear interrupt bit
		MOV A,SBUF0 	; move the char to the Accumulator

		CJNE A,#'s', done ; only do something when typing s

		; TODO set time by following chars

		done:
		CLR TI0 ; clear interrupt flag
		reti

;------------------------------------------------------------------------------
; End of file.
;------------------------------------------------------------------------------
END
