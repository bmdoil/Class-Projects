TITLE Program #4      (project04.asm)

;---------------------------------------------------------
; Author: Brent Doil				Email: doilb@oregonstate.edu
; Course: CS271-400                 Date: 8/6/2017
; Project ID: Program # 4
; Description: Introduces programmer and generates list of random numbers into a user specified size array. 
; Displays the unsorted list, median, then sorts the list and displays the sorted list.
;---------------------------------------------------------

INCLUDE Irvine32.inc

; (insert constant definitions here)
MIN = 10
MAX = 200
LO = 100
HI = 999

.data
introPrompt1	BYTE	"Welcome to Sorting Random Numbers by Brent Doil. ",0
introPrompt2	BYTE	"This program generates random numbers in the range [100 - 999], displays the original list, sorts the list,",0
introPrompt3	BYTE	"calculates the median, then displays the list in descending order.",0 
userInvalid		BYTE	"Out of range, try again.",0
userPrompt1		BYTE	"How many numbers should be generated? [10 - 200] ",0
unsorted		BYTE	"The unsorted random numbers: ",0 
median			BYTE	"The median is ",0
sorted			BYTE	"The sorted list: ",0
space3			BYTE	"   ",0


numArr			DWORD	MAX		DUP(?)
userNum			DWORD	?
leftArr			DWORD	0
newLine			DWORD	0

.code

main PROC
	call	Randomize				;seed RNG

	push	OFFSET introPrompt1
	push	OFFSET introPrompt2
	push	OFFSET introPrompt3
	call	introduction			
	

	push	OFFSET userPrompt1
	push	OFFSET userInvalid
	push	OFFSET userNum
	call	getData


	push	OFFSET numArr
	push	userNum
	call	fillArray

	push	OFFSET space3
	push	OFFSET unsorted
	push	OFFSET numArr
	push	userNum
	call	printList


	push	OFFSET numArr
	push	userNum
	call	sortList

	push	OFFSET	median
	push	OFFSET	numArr
	push	userNum
	call	printMed

	push	OFFSET space3
	push	OFFSET sorted
	push	OFFSET numArr
	push	userNum
	call	printList
	exit	; exit to operating system

main ENDP



;---------------------------------------------------
;introduction
;
;Introduces program and programmer
;
;	introPrompt1 (ref) [ebp+16]
;	introPrompt2 (ref) [ebp+12] 
;	introPrompt3 (ref) [ebp+8]
;Return: none
;Preconditions: none
;Registers modified: eax, edx
;---------------------------------------------------
introduction PROC
	push	ebp
	mov		ebp, esp
	
	mov		edx, [ebp+16]
	call	WriteString
	call	CrLf

	mov		edx, [ebp+12]
	call	WriteString
	call	CrLf

	mov		edx, [ebp+8]
	call	WriteString
	call	CrLf

	pop		ebp	
	ret		12

introduction ENDP

;---------------------------------------------------
;getData
;
;Gets integer from user and validates input is integer MIN < userNum < MAX
;
;Receives: 
;	userPrompt1 (ref) [ebp+16]
;	userInvalid (ref) [ebp+12]
;	userNum	    (ref) [ebp+8]
;Return: User value for number of randoms to generate (userNum)
;Preconditions: none
;Registers modified: eax, ebx, edx
;---------------------------------------------------
getData PROC

	push	ebp
	mov		ebp, esp
	mov		edx, [ebp+16]
	call	WriteString
	call	CrLF



	validate:						;input validation 
		mov		ebx, [ebp+8]
		call	ReadInt
		

		cmp		eax, MIN			
		jb		invalid
	
		cmp		eax, MAX		
		ja		invalid

		call	CrLf

		mov		[ebx], eax
		pop		ebp	
		ret		12

	invalid:						;prompts user to enter valid number

		mov		edx, [ebp+12]
		call	WriteString
		call	CrLf
		jmp		validate 

getData ENDP

;---------------------------------------------------
;fillArray
;
;Fills passed array with random numbers in range [LO...HI]
;
;Receives: 
;	numArr	(ref)	[ebp+12]	
;	userNum	(val)	[ebp+8]
;Return: Address of numArr, filled with user specified number of random values
;Preconditions: userNum initialized
;Registers modified: eax, ebx, ecx, edx, edi
;---------------------------------------------------
fillArray PROC
		push	ebp	
		mov		ebp, esp

		mov		edi, [ebp+12]		;start of array
		mov		ecx, [ebp+8]		;number of values to generate, sets up loop

		mov		ebx, LO				
		mov		edx, HI
		inc		edx
		sub		edx, ebx			;range = (HI + 1) - LO

getRand:
		mov		eax, edx
		call	RandomRange
		add		eax, LO				;add LO to generated number to get lower bound
		mov		[edi], eax			;move value into edi
		add		edi, 4				;increment edi
		loop	getRand				

		pop		ebp	
		ret		12

fillArray ENDP

;---------------------------------------------------
;sortList
;
;Uses selection sort to sort passed array in descending order. 
;
;Receives: 
;	numArr		(ref) [ebp+12]
;	userNum		(val) [ebp+8]
;	
;Return: Address of numArr, sorted. 
;Preconditions: userNum initialized, numArr values initialized
;Registers modified: eax, ebx, edx, esi, edi
;---------------------------------------------------
sortList PROC
	push	ebp						;set up stack frame
	mov		ebp, esp
	xor		ecx, ecx				;clear ecx register		
	mov		edi, [ebp+12]			;set edi to beginning address of numArr	

start:
	mov		eax, ecx				;smallest element in ecx				
	mov		ebx, ecx				

loopOne:
	inc		ebx						
	cmp		ebx, [ebp+8]			;compare ebx to last element	
	je		loopTwo					;if equal, move to 2nd loop
	mov		edx, [edi+ebx*4]		;compare the two numArr values
	cmp		edx, [edi+eax*4]
	jl		loopOne					;if first value is less, jmp back to loopOne (inc ebx and continue)
									;otherwise, continue to swap arithmetic
	pushad							;save register values		
	mov		esi, [ebp+12]			;set esi to beginning address of numArr	
	mov		ecx, 4					
	mul		ecx						;eax * 4 is address of current smallest value
	add		esi, eax				;add to esi
	push	esi						;save to stack
	mov		eax, ebx				;move ebx (new smallest value) into eax and repeat
	mul		ecx
	add		edi, eax				
	push	edi						;save to stack
	call	swapEle					;swap current smallest with new smallest value
	popad							;reset register values			
	jmp		loopOne

loopTwo:							;checks each value to confirm correct sort, if no, continue to top
	inc		ecx						
	cmp		ecx, [ebp+8]			
	je		return				
	jmp		start

return:
	pop		ebp
	ret		8
sortList		ENDP


;---------------------------------------------------
;swapEle
;
;Swaps two array elements, in place. Attributed to CS271-400 lecture 20 slides.
;
;Receives: 
;	first		(ref) [ebp+12]
;	second		(ref) [ebp+8]
;	
;Return: Values of swapped elements 
;Preconditions: Array with 2 elements
;Registers modified: ecx, edx, esi, edi
;---------------------------------------------------
swapEle	 PROC
	push	ebp
	mov		ebp, esp

	mov		esi, [ebp+12]
	mov		edi, [ebp+8]
	mov		edx, [edi]
	mov		ecx, [esi]
	mov		[edi], ecx
	mov		[esi], edx

	pop		ebp
	ret 8


swapEle	 ENDP

;---------------------------------------------------
;printMed
;
;Displays the median of a set of array values to the screen. If odd, selects middle value. If even, adds two middle values / 2, then displays
;
;Receives: 
;	median		(ref) [ebp+16]
;	numArr		(ref) [ebp+12]
;	userNum     (val) [ebp+8]
;Return: Displays median value 
;Preconditions: numArr initialized, array values (>=1) initialized
;Registers modified: eax, ebx, ecx, edx, edi
;---------------------------------------------------
printMed PROC
	push	ebp							
	mov		ebp, esp
	mov		edi, [ebp+12]		
				
	mov		edx, [ebp+16]				
	call	WriteString

	mov		eax, [ebp+8]				
	cdq										;convert to quadword for division into eax:edx		
	mov		ebx, 2
	div		ebx								;finds middle of array
	cmp		edx, 0						
	je		eve								;no remainder means it's even
odd:
	mov		ebx, [edi+eax*4]				;if it's odd
	mov		eax, ebx						;print the middle element
	call	WriteDec
	jmp		return
eve:
	dec		eax								;eax is middle of array
	mov		ebx, [edi+eax*4]			
	inc		eax
	mov		ecx, [edi+eax*4]				;adds together the 2 middle elements
	mov		eax, ebx
	add		eax, ecx
	mov		ebx, 2							;divides by 2
	div		ebx								
	call	WriteDec
	
return:
	call	CrLf
	pop		ebp
	ret		12

printMed ENDP
;---------------------------------------------------
;printMed
;
;Displays array elements to the console, 10 elements to a line
;
;Receives: 
;	listName	(ref) [ebp+16]
;	numArr		(ref) [ebp+12]
;	userNum     (val) [ebp+8]
;Return: Displays array elements to console
;Preconditions: numArr initialized, array values (>=1) initialized
;Registers modified: eax, edx, esi
;---------------------------------------------------
printList PROC
	push	ebp	
	mov		ebp, esp
	mov		newLine, 0			
	mov		edx, [ebp+16]
	call	WriteString
	call	CrLf

	mov		esi, [ebp+12]
	mov		ecx, [ebp+8]

next:
	mov		eax, [esi]
	call	WriteDec
	mov		edx, [ebp+20]
	call	WriteString

	checkLine:
		
		inc		newLine
		cmp		newLine, 10			;every 10 lines, create new line with reset
		je		reset
		jmp		continue			

	reset:
		call	CrLf
		mov		newLine, 0			;reset newLine to 0
		jmp		continue
continue:							;moves numArr pointer to next location
	add		esi,4
	loop	next

done:
	call	CrLf
	pop		ebp	
	ret		16
printList ENDP

END main