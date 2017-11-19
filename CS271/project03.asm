TITLE Project #3      (project3.asm)
;---------------------------------------------------------
; Author: Brent Doil				Email: doilb@oregonstate.edu
; Course: CS271-400                 Date: 7/31/2017
; Project ID: Program # 3
; Description: Introduces programmer, prompts user for number of composites to display, then prints list of composite numbers to console, 10 per line.
;---------------------------------------------------------
INCLUDE Irvine32.inc

;Constants
MINCOMP = 1
MAXCOMP = 400


.data

;Prompts
introPrompt		BYTE	"Welcome to Composite Numbers by Brent Doil. ",0
ec1				BYTE	"EC1: Numbers are displayed in aligned columns. ",0
userPrompt1		BYTE	"Enter the number of composite numbers you would like to see, up to 400 composites. ",0
userPrompt2		BYTE	"Enter the number of composites to display [1 - 400]:",0
userInvalid		BYTE	"Out of range, try again.",0
goodBye			BYTE	"Thank you for using my program. Goodbye.",0
threeSpace		BYTE	"   ",0
fourSpace		BYTE	"    ",0
fiveSpace		BYTE	"     ",0
sixSpace		BYTE	"      ",0

newLine			DWORD	0

compFound		DWORD	0
totalComp		DWORD	0
userNum			DWORD	?
curNum			DWORD	2	



.code
main PROC  
	call	intro
	call	getUserData
	call	showComposites
	call	farewell

	exit	; exit to operating system
main ENDP


;-----------------------------------
;Intro
;
;Introduces program and programmer
;
;-----------------------------------
intro	PROC 
	
	mov		edx, OFFSET introPrompt
	call	WriteString
	call	CrLf
	mov		edx, OFFSET ec1
	call	WriteString
	call	CrLf
	ret
intro ENDP


;-----------------------------------
;getUserData
;
;Prompts user for number and provides
;input validation MINCOMP < userNum < MAXCOMP
;-----------------------------------
getUserData PROC 
	mov		edx, OFFSET userPrompt1
	call	WriteString
	call	CrLF

	mov		edx, OFFSET userPrompt2
	call	WriteString
	call	CrLF

	validate:						;input validation 
		call	ReadInt
		mov		userNum, eax

		cmp		userNum, MINCOMP		;check for userNum < 1
		jb		invalid
	
		cmp		userNum, MAXCOMP		;check for userNum > 400
		ja		invalid

		call	CrLf
		ret

	invalid:						;prompts user to enter valid number

		mov		edx, OFFSET userInvalid
		call	WriteString
		call	CrLf
		jmp		validate 
		
getUserData ENDP

;-----------------------------------
;showComposites
;
; Prints composite number to console  when found. After 10 prints, new line
; created. Will loop until userNum = totalComp. (This is inefficient)
;-----------------------------------
showComposites PROC

	mov		eax, userNum

	findComp:
		mov		compFound, 0		;reset composite found flag
		call	isComposite
		cmp		compFound, 1		;was composite found?
		je		print				;print
		inc		curNum				
		mov		eax, totalComp	
		cmp		eax, userNum		;while totalComp < userNum, continue finding composites
		jl		findComp			
		jmp		found				

	print:
		mov		eax, curNum
		call	WriteDec
		cmp		eax, 10
		jl		space5
		cmp		eax, 100
		jl		space4		

		space3:			
		mov		edx, OFFSET threeSpace	
		call	WriteString
		jmp		checkLine

		space4:			
		mov		edx, OFFSET fourSpace	
		call	WriteString
		jmp		checkLine

		space5:			
		mov		edx, OFFSET fiveSpace	
		call	WriteString
		jmp		checkLine
		
		

	checkLine:
		inc		curNum
		inc		newLine
		cmp		newLine, 10			;every 10 lines, create new line with reset
		je		reset
		jmp		findComp			

	reset:
		call	CrLf
		mov		newLine, 0				
		jmp		findComp
		
		
	
	found:
		ret

showComposites ENDP

;-----------------------------------
;isComposite
;
; Performs composite check on current number. Sets compFound flag to 1 if curNum
; is comp, remains 0 otherwise. 
;-----------------------------------
isComposite PROC
	
	mov		ecx, curNum
	dec		ecx						;begin at curNum - 1

	checkComp:
		cmp		ecx, 1				;if ecx is 1, we are done	
		je		done					

		xor		edx,edx			;reset edx
		mov		eax, curNum		;eax/ecx
		div		ecx						
		cmp		edx, 0			;if no remainder, composite		
		je		found				
					
		loop checkComp			;otherwise loop

	found:
		mov compFound, 1		;set flag for compFound
		inc totalComp			;increment total composites found

	done:
		ret

isComposite ENDP

;-----------------------------------
;farewell
;
; Say farewell to the user
;-----------------------------------
farewell		PROC  
	call	CrLf
	mov		edx, OFFSET goodBye
	call	WriteString
	call	CrLF
	mov		edx,0
	ret
farewell	ENDP
END main
