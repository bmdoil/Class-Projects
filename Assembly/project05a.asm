TITLE Program #5      (project05.asm)

;---------------------------------------------------------
; Author: Brent Doil				Email: doilb@oregonstate.edu
; Course: CS271-400                 Date: 8/14/2017
; Project ID: Program # 5A
; Description: Introduces program and programmer. Asks user for MAX_NUMS (10) values. Converts these values to
; integers, displays a running subtotal, calculates the sum and average, then converts these numbers
; back to a string and displays the series, sum, and average to the user.
;---------------------------------------------------------

INCLUDE Irvine32.inc

MAX_LENGTH	= 15
MAX_NUMS = 10		
LOW_VAL = 48
HIGH_VAL = 57

;Taken from CS271 lecture slides
displayString	MACRO	buffer
	push	edx
	mov		edx, buffer
	call	WriteString
	pop		edx
ENDM

;Adapted from CS271 lecture slides
readStr MACRO	var
	push	ecx
	push	edx
	mov		edx, var
	mov		ecx, MAX_LENGTH
	call	ReadString
	pop		edx
	pop		ecx
ENDM

getString	MACRO	userPrompt, val	
	displayString	userPrompt
	readStr	val
ENDM

.data
introPrompt1	BYTE	"Welcome to Project 5A, Designing low-level I/O procedures. Written by Brent Doil.",0
introPrompt2	BYTE	"Please provided 10 unsigned decimal integers. Each number needs to be small enough to fit inside a 32 bit register.",0
introPrompt3	BYTE	"After you have finished inputting the numbers I'll display a list of the integers, their sum, and average value.",0 
userInvalid		BYTE	"ERROR: You did not enter an unsigned number or your number was too big.",10,0	
userPrompt1		BYTE	". Please enter an unsigned number: ",0
numsPrompt		BYTE	"You entered the following numbers: ",0  
subtotPrompt	BYTE	"Subtotal: ",0
sumPrompt		BYTE	"The sum of these numbers is: ", 10,0			
avePrompt		BYTE	10,"The average is: ",0
comma			BYTE	", ",0
ec1				BYTE	"EC1: Number each line of user input and display a running subtotal of the user's numbers.",0
ec3				BYTE	"EC3: readVal and writeVal procedures are recursive.",0
farewell		BYTE	"Thanks for playing! ",0
	
userVal			BYTE	MAX_LENGTH	DUP(?)
parsedArr		BYTE	MAX_LENGTH	DUP(?)
numArr			DWORD	MAX_NUMS	DUP(?)

maxInputs		DWORD	MAX_NUMS
lineNum			DWORD	1	
subTot			DWORD	0


.code


main PROC
	push	OFFSET ec1				;24
	push	OFFSET ec3				;20
	push	OFFSET introPrompt1		;16
	push	OFFSET introPrompt2		;12
	push	OFFSET introPrompt3		;8
	call	intro

	push	OFFSET userInvalid		;36
	push	OFFSET userPrompt1		;32
	push	OFFSET subtotPrompt		;28
	push	maxInputs				;24
	push	subTot					;20
	push	lineNum					;16
	push	OFFSET userVal			;12
	push	OFFSET numArr			;8
	call	readVal

	push	OFFSET numsPrompt		;24
	push	OFFSET comma			;20
	push	OFFSET parsedArr		;16
	push	OFFSET numArr			;12
	push	LENGTHOF numArr			;8
	call	writeVal
	call	CrLf

	push	OFFSET sumPrompt		;24
	push	OFFSET avePrompt		;20
	push	OFFSET parsedArr		;16
	push	OFFSET numArr			;12
	push	subTot					;8
	call	analyze

	push	OFFSET	farewell		;8
	call	goodBye

   exit
main ENDP

;---------------------------------------------------
;intro
;
;Introduces program and programmer

;Receives: 
;	OFFSET	ec1				[ebp+24]
;	OFFSET	ec3				[ebp+20]
;	OFFSET	introPrompt1	[ebp+16]
;	OFFSET	introPrompt2	[ebp+12] 
;	OFFSET	introPrompt3	[ebp+8]	
;	
;Return: none
;Preconditions: none
;Registers modified: none
;---------------------------------------------------
intro PROC
	push	ebp
	mov		ebp, esp
	

	displayString	[ebp+16]	
	call	CrLf
	displayString	[ebp+12]	
	call	CrLf
	call	CrLf
	displayString	[ebp+8]		
	call	CrLf
	displayString	[ebp+24]
	call	CrLf
	displayString	[ebp+20]
	call	CrLf
	
	pop		ebp
	ret		12
intro ENDP

;---------------------------------------------------
;readVal
;
;Gets series of values from user as string and parses it into integer, stores in an array
;Also prints running sum of values as they are entered. 
;This runs recursively until base case is reached.
;
;Receives: 
;	OFFSET userInvalid		[ebp+36]
;	OFFSET userPrompt1		[ebp+32]  
;	OFFSET subtotPrompt		[ebp+28]  
;	maxInputs				[ebp+24]  
;	subTot					[ebp+20]  
;	lineNum					[ebp+16]  
;	OFFSET userVal			[ebp+12]  
;	OFFSET numArr			[ebp+8]	
;
;Return: none
;Preconditions: Parameters (values and array) must be initialized and passed in correct order
;Registers modified: eax, ebx, ecx, edx, esi, edi
;---------------------------------------------------
readVal PROC

	push	ebp
	mov		ebp, esp
	pushad

readUserVal:

	mov		ebx, [ebp+24]				;maxInputs
	cmp		ebx, 0						;if maxInputs is 0, base case is reached. End procedure.
	je		endRead
	mov		eax, [ebp+16]				;lineNum
	call	WriteDec
	getString		[ebp+32], [ebp+12]	;userPrompt1	userVal	
	cmp		eax, 10
	jge		invalid
	mov		ecx, eax					;set loop ctr to str length
	mov		esi, [ebp+12]				;userNum
	mov		edi, [ebp+8]				;numArr
	mov		ebx, 10						;to multiply by 10
	mov		edx, 0						;clear edx
	cld
beginLoop:

	lodsb
	cmp		al, LOW_VAL					;use
	jl		invalid
	cmp		al, HIGH_VAL
	jg		invalid
	sub		al, LOW_VAL					;if valid, get integer representation
	movzx	eax,al						;move to 32 bit reg
	add		eax, edx
	mul		ebx							;eax * 10
	mov		edx, eax					;store in edx, loop will build number from 1's place upward
	loop	beginLoop

	mov		eax, edx
	mov		edx, 0
	div		ebx

	displayString	[ebp+28]			;subtotPrompt
	push	eax							;save eax to do some math
	add		[ebp+20], eax				;subTot
	mov		eax, [ebp+20]			
	mov		[ebp+20], eax
	call	WriteDec
	call	CrLf
	pop		eax

	
	push	eax
	push	edi
	call	saveToArr					;save eax to location edi in numArr

	mov		ebx, [ebp+24]				;decrement maxInputs, continue toward base case
	dec		ebx
	mov		[ebp+24], ebx

	add		edi, 4						;increment pointer to next place in numArr
	mov		eax, [ebp+16]
	inc		eax							;increment line number
	mov		[ebp+16], eax

	;recursion time
	push	[ebp+36]
	push	[ebp+32]
	push	[ebp+28]
	push	ebx							;current maxInputs
	push	[ebp+20]  
	push	eax							;current lineNum
	push	[ebp+12]
	push	edi							;current offset of numArr
	call	readVal

endRead:

	popad
	pop		ebp
	ret		32

invalid:	

	displayString	[ebp+36]			;userInvalid
	jmp		readUserVal

readVal ENDP

;---------------------------------------------------
;writeVal
;
;Converts integers stored in an array into a string and displays to screen.
;This runs recursively until base case is reached
;
;Receives: 
;	OFFSET numsPrompt		[ebp+24] 
;	OFFSET space			[ebp+20] 
;	OFFSET parsedArr		[ebp+16] 
;	OFFSET numArr			[ebp+12] 
;	LENGTHOF numArr			[ebp+8] 
;
;Return: none
;Preconditions: Parameters (values and array) must be initialized and passed in correct order
;Registers modified: eax, ebx, ecx, edx, esi, edi
;---------------------------------------------------
writeVal PROC
	push	ebp
	mov		ebp, esp
	pushad

	mov		ebx, [ebp+8]
	cmp		ebx, 10
	jl		writeUserVal

	displayString	[ebp+24]

writeUserVal:
	mov		edi, 0
	mov		ebx, 0

	mov		esi, [ebp+12]			;points to first value in numArr
	mov		ecx, [ebp+8]			;LENGTHOF array, used for loop (base case is 1)
	
	push	[ebp+16]				;push @first value in parsedArr to stack
	push	[esi]					;push first value of numArr onto stack
	call	convertInt				;converts from string to int
	cmp		ecx, 1					;check for base case
	je		endWrite

	displayString	[ebp+20]		 ;just a comma and space
	add		esi, 4					 ;move to next value
	mov		ecx, [ebp+8]
	dec		ecx						 ;dec toward base case

	;recursion time
	push	[ebp+24]
	push	[ebp+20]
	push	[ebp+16]
	push	esi			;current offset of numArr
	push	ecx			;current LENGTHOF numArr	
	call	writeVal
endWrite:
		popad
		pop		ebp
		ret		20

writeVal ENDP

;---------------------------------------------------
;saveToArr
;
;Helper function that saves a number to the address of an array location.
;Assist the recursion implementation.
;
;Receives: 
;	userVal			[ebp+12] 
;	OFFSET	numArr	[ebp+8]	
;	
;Return: none
;Preconditions: Value must be initialized and numArr must point to valid location in an array
;Registers modified: eax, edi
;---------------------------------------------------
saveToArr PROC
	push	ebp
	mov		ebp, esp
	pushad

		mov		edi, [ebp+8]		;point to first value of numArr	
		mov		eax, [ebp+12]		;move userVal into eax
		mov		[edi], eax			;saves userVal into location @edi (numArr)

	popad
	pop		ebp
	ret		8
saveToArr	ENDP

;---------------------------------------------------
;convertInt
;
;Helper function used to do the work of converting values from int to string
;Reverses action of readVal. Saves having to recopy this code in several places.
;
;Receives: 	
;	OFFSET parsedArr		[ebp+12] 
;	numArr					[ebp+8] 
;	
;Return: A parsed string to print to console
;Preconditions: Parameters (value and array) must be initialized and passed in correct order
;Registers modified: eax, ebx, ecx, edx, edi
;---------------------------------------------------
convertInt PROC
		push	ebp
		mov		ebp, esp
		pushad

		mov		ecx, 0	
		mov		edi, [ebp+12]
		mov		eax, [ebp+8]

	onesDigit:
		mov		edx, 0
		mov		ebx, 10
		div		ebx
		cmp		eax, 0
		je		lastDigit
		inc		ecx
		jmp		onesDigit

	lastDigit:
		inc		ecx
		add		edi, ecx
		std
		mov		edx, 0
		mov		al, 0
		stosb
		mov		eax, [ebp+8]
	string:
		mov		edx, 0
		div		ebx
		add		edx, LOW_VAL
		push	eax
		mov		al, dl
		stosb
		pop		eax
		loop	string

		displayString	[ebp+12]
		
		popad
		pop		ebp
		ret		8
convertInt ENDP

;---------------------------------------------------
;analyze
;
;Analyzes parsed array and displays average and sum of values.
;
;Receives: 
;	OFFSET sumPrompt		[ebp+24]	
;	OFFSET avePrompt		[ebp+20]	
;	OFFSET parsedArr		[ebp+16]	
;	OFFSET numArr			[ebp+12]	
;	subTot					[ebp+8]		
;Return: none
;Preconditions: Parameters (values and array) must be initialized and passed in correct order
;Registers modified: eax, ebx, ecx, edx, esi, edi
;---------------------------------------------------
analyze PROC
	push	ebp
	mov		ebp, esp
	pushad

	displayString	[ebp+24]

	mov		eax, 0			;set up registers
	mov		ebx, eax
	mov		ecx, 10
	mov		edx, eax
	
	mov		edi, [ebp+12]

summation:					;loops through values and adds them together
	add		eax, [edi]
	add		edi, 4
	loop	summation

	push	[ebp+16]		;convert it to display sum
	push	eax
	call	convertInt
	call	CrLf

	displayString	[ebp+20]

	mov		ebx, MAX_NUMS	
	div		ebx

	push	[ebp+16]		;convert it to display average
	push	eax
	call	convertInt
	call	CrLf

	popad
	pop		ebp
	ret		8	
analyze	ENDP
;---------------------------------------------------
;goodBye
;
;Displays farewell message to user
;
;Receives: 
;	OFFSET	farewell		[ebp+8]
;	
;Return: none
;Preconditions: none
;Registers modified: none
;---------------------------------------------------
goodBye PROC
	push	ebp
	mov		ebp, esp
	
	displayString	[ebp+8]

	pop		ebp
	ret		4

goodBye ENDP

END main

