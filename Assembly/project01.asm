TITLE Project 1     (Project01.asm)

; Author: Brent Doil				Email: doilb@oregonstate.edu
; Project ID:   Program #1          Class: CS271-400		 Due Date: 07/09/2017
; Description: Introduce the programmer, prompt user for 2 numbers, then output sum, difference, product, quotient and remainder.

INCLUDE Irvine32.inc



.data

numberOne	DWORD	?			;1st integer to be entered by user
numberTwo	DWORD	?			;2nd integer to be entered by user

intro_1		BYTE	"Elementary Arithmetic by Brent Doil ", 0
intro_2		BYTE	"Enter 2 numbers, and I'll show you the sum, difference, product, quotient, and remainder. ", 0
prompt_1	BYTE	"Enter first number:  ", 0
prompt_2	BYTE	"Enter second number: ", 0
validate	BYTE	"The second number must be less than the first!", 0
sumPrompt	BYTE	" + ", 0
diffPrompt	BYTE	" - ", 0
prodPrompt	BYTE	" x ", 0
quotPrompt	BYTE	" / ", 0
remPrompt	BYTE	" remainder ", 0
eqPrompt	BYTE	" = ", 0



ec1			BYTE	"EC1: This program repeats until the user chooses to quit. ", 0
ec2			BYTE	"EC2: This program validates that the second number entered is less than the first. ", 0
ec3			BYTE	"EC3: This program calculates and displays the quotient as a floating point number, rounded to the nearest .001. ", 0
loopPrompt	BYTE	"EC3: Would you like to enter new numbers? Enter 1 for YES or 0 for NO: ", 0
loopRes		DWORD	?		;user input to trigger loop

thousand	DWORD	1000
sum 		DWORD	?
diff		DWORD	?
prod		DWORD	?
quot		DWORD	?
floatQuot	REAL4	?		;EC 2 floating point quotient
rem			DWORD	?		;remainder

goodBye		BYTE	"Impressed? Bye! ", 0

.code
main PROC

;Introduction
	mov		edx, OFFSET intro_1
	call	WriteString
	call	CrLf

	;Extra credit 1 description
	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLf
	;Extra credit 2 description
	mov		edx, OFFSET ec2
	call	WriteString
	call	CrLf
	;Extra credit 3 description
	mov		edx, OFFSET ec3
	call	WriteString
	call	CrLf

	call	CrLf
	mov		edx, OFFSET intro_2
	call	WriteString
	call	CrLf


	
;Get the data
start:
	mov		edx, OFFSET prompt_1
	call	WriteString
	call	ReadInt
	mov		numberOne, eax
	

	mov		edx, OFFSET prompt_2
	call	WriteString
	call	ReadInt
	mov		numberTwo, eax

;Validate 2nd number is less than 1st number, jump to numErr if not.
	mov		eax, numberOne
	mov		ebx, numberTwo
	cmp		ebx, eax
	jg		numErr
	jle		calc

; Display prompt that 2nd number is less than 1st number
numErr:
		mov	edx, OFFSET validate
		call WriteString
		call CrLf
		jg	Prompt
		

calc:		;Calculate values

;Calculate the sum
	mov		eax, numberOne
	mov		ebx, numberTwo
	add		eax, ebx
	mov		sum, eax

;Calculate the difference
	mov		eax, numberOne
	mov		ebx, numberTwo
	sub		eax, ebx
	mov		diff, eax


;Calculate the product
	mov		eax, numberOne
	mov		ebx, numberTwo
	mul		ebx
	mov		prod, eax

;Calculate the quotient and remainder integer
	
	mov		eax, numberOne
	cdq
	mov		ebx, numberTwo
	div		ebx
	mov		quot, eax
	mov		rem, edx


;Calculate the quotient floating point

	fild	numberOne	
	fidiv	numberTwo	
	fimul	thousand	;mult by 1000 to preserve 3 decimals
	frndint				;round to nearest integer
	fidiv	thousand	;divide by 1000
	fst		floatQuot	
	

;Display the sum

	mov		eax, numberOne
	call	WriteDec
	mov		edx, OFFSET sumPrompt
	call	WriteString
	mov		eax, numberTwo
	call	WriteDec
	mov		edx, OFFSET eqPrompt
	call	WriteString

	mov		eax, sum
	call	WriteDec
	call	CrLf

;Display the difference

	mov		eax, numberOne
	call	WriteDec
	mov		edx, OFFSET diffPrompt
	call	WriteString
	mov		eax, numberTwo
	call	WriteDec
	mov		edx, OFFSET eqPrompt
	call	WriteString

	mov		eax, diff
	call	WriteDec
	call	CrLf

;Display the product
	mov		eax, numberOne
	call	WriteDec
	mov		edx, OFFSET prodPrompt
	call	WriteString
	mov		eax, numberTwo
	call	WriteDec
	mov		edx, OFFSET eqPrompt
	call	WriteString

	mov		eax, prod
	call	WriteDec
	call	CrLf

	
;Display the quotient and remainder
	mov		eax, numberOne
	call	WriteDec
	mov		edx, OFFSET quotPrompt
	call	WriteString
	mov		eax, numberTwo
	call	WriteDec
	mov		edx, OFFSET eqPrompt
	call	WriteString

	mov		eax, quot
	call	WriteDec
	mov		edx, OFFSET remPrompt
	call	WriteString
	mov		eax, rem
	call	WriteDec
	call	CrLf


;Display float quotient
	mov		eax, numberOne
	call	WriteDec
	mov		edx, OFFSET quotPrompt
	call	WriteString
	mov		eax, numberTwo
	call	WriteDec
	mov		edx, OFFSET eqPrompt
	call	WriteString

	mov		eax, floatQuot
	call	WriteFloat
	call	CrLf
	


;Prompt user input to repeat until user chooses to quit
prompt:
	mov		edx, OFFSET loopPrompt
	call	WriteString
	call	ReadInt
	mov		loopRes, eax
	cmp		eax, 1
	je		start
		
	;Say Good-bye
	mov		edx, OFFSET goodBye
	call	WriteString
	call	CrLF

	exit	; exit to operating system
main ENDP



END main
