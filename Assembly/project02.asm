TITLE Program #2      (project02.asm)

; Author: Brent Doil				Email: doilb@oregonstate.edu
; Project ID:   Program #2          Class: CS271-400		 Due Date: 07/16/2017
; Description: Introduces programmer, asks for user name and number of fibonacci terms to display, validates input and displays aligned results in console window.

INCLUDE Irvine32.inc

; constants
MINFIB = 1
MAXFIB = 46
TABCHANGE = 35

.data


intro		BYTE	"Welcome to Fibonacci Numbers by Brent Doil. ",0
ec1			BYTE	"EC1: Numbers are displayed in aligned columns. ",0
getUserName	BYTE	"What is your name? ",0
userName	BYTE	25 DUP(?)
byteCount	DWORD	?			;string buffer
greeting	BYTE	"Hello, ",0
fibPrompt	BYTE	"Enter the number of Fibonacci terms you would like displayed from 1 term to 46 terms (Enter 1-46): ",0
fibInvalid	BYTE	"Please enter a number between 1 - 46 to proceed. ",0
farewell1	BYTE	"Farewell, ",0
farewell2	BYTE	"! Thank you for using my program. ",0

printTab	BYTE	9	;prints TAB to console using WriteChar

userNum		DWORD	?	;user inputs # of fibonacci terms
fibPrev		DWORD	?	;previous fibonacci term
fibVal		DWORD	?	;current fibonacci term
fibTot		DWORD	?	;total fibonacci value
counter		DWORD	?	;counts iteration # of loop 
newLine		DWORD	0	;tracks when to create a new line in console

.code
main PROC

;introduction to program
introduction:
	mov		edx, OFFSET intro
	call	WriteString
	call	CrLF

	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLF

;userInstructions
userInstructions:

	;get string input userName
	mov		edx, OFFSET getUserName
	call	WriteString
	call	CrLF
	mov		edx, OFFSET userName
	mov		ecx, SIZEOF	userName
	call	ReadString
	mov		byteCount, eax	

	;greet user
	mov		edx, OFFSET greeting
	call	WriteString
	mov		edx, OFFSET userName
	call	WriteString
	call	CrLf

;getUserData

getUserData:						;get user fibonacci # of terms and validate data

	mov		edx, OFFSET fibPrompt
	call	WriteString
	call	CrLF

	validate:						;input validation 
		call	ReadInt
		mov		userNum, eax

		cmp		userNum, MINFIB		;check for userNum < 1
		jb		invalid
	
		cmp		userNum, MAXFIB		;check for userNum > 46
		ja		invalid

		call	CrLf
		jmp		displayFibs

	invalid:						;prompts user to enter valid number

		mov		edx, OFFSET fibInvalid
		call	WriteString
		call	CrLf
		jmp		validate


displayFibs:						;calculate the fibonacci number using loop instructions
		
		mov		ecx, userNum		;set loop counter register to userNum

		;load starting values (it works)
		mov		fibVal, 2
		mov		fibPrev, 1	
		mov		counter, 0	
		mov		eax, 1

		;loop to print first 2 terms
		firstLoop:		
		inc		counter				
		cmp		counter, 2		;if counter > 2, jump out of firstLoop and to checkLoop
		ja		checkLoop
		jmp		printFib		;print to console
		L1:	
		loop	firstLoop

		checkLoop:				;jump to farewell message and skip mainLoop if ecx < 1, otherwise continue to mainLoop
		cmp		ecx, 1
		jb		farewell	
		
		mainLoop: 	

		mov		ebx, fibVal		;move current term into ebx
		add		ebx, fibPrev	;add previous term to ebx

		mov		fibTot, ebx		;store in fibTot

		;set fibPrev to fibVal for next iteration 
		mov		ebx, fibVal		
		mov		fibPrev, ebx

		mov		eax, fibTot		;move fibTot to eax for printing
		mov		fibVal, eax		;store in fibVal for next iteration
		jmp		printFib		
		loop	mainLoop	

;prints fib term to console and aligns TAB delimited				
printFib:
		
		call	WriteDec		
		mov		al, printTab		;use al register to print the TAB char
		call	WriteChar
		cmp		counter, TABCHANGE	;change from 2 TABS to 1 TAB when counter > TABCHANGE (larger #'s displayed)
		jb		P1
		inc		newLine
		cmp		newLine, 5			;if newLine = 5, jump to create CrLf and reset newLine to 0
		je		P2
		mov		eax, 1				;reset eax to 1
		jmp		L1					;jumps back into firstLoop

		P1:							;writes a 2nd TAB char to console
		mov		al, printTab
		call	WriteChar
		inc		newLine
		cmp		newLine, 5
		je		P2
		mov		eax, 1				;reset eax to 1
		jmp		L1					;jumps back into firstLoop

		P2:							;creates new line and resets newLine counter to 0
		call	CrLf
		mov		edx, newLine
		sub		edx, 5
		mov		newLine, edx
		mov		eax, 1				;reset eax to 1
		jmp		L1					;jumps back into firstLoop

;farewell message
farewell:
		call	CrLf
		mov		edx, OFFSET farewell1
		call	WriteString
		mov		edx, OFFSET userName
		call	WriteString
		mov		edx, OFFSET farewell2
		call	WriteString
		call	CrLF


	exit	; exit to operating system
main ENDP



END main
 