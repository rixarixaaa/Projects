#Bitmap Project: Etch-a-Sketch
#Instructions:
#	connect bitmap display:
#		set pixel to 4x4
#		set diplay dim to 256x256
#		use $gp as base address
#	connect keyboard, then run
#	use w(up), s(down), a(left), d(right), space(exit)
#	***CHECK RUN I/O CONSOLE OUTPUT WHILE PLAYING (MAXIMIZE CONSOLE SIZE)***

#Constants
	.eqv WIDTH	64 #Width
	.eqv HEIGHT	64 #Height
	.eqv let_w	5 #Width of alphabet letters
	.eqv let_h	5 #Height of alphabet letters
#Colors
	.eqv	red 0x00E89B9B		#Hex for red
	.eqv	blue 0x009BC3E8		#Hex for blue
	.eqv	green 0x009BE8B5	#Hex for green
	.eqv	yellow 0x00E2E89B	#Hex for yelloq
	.eqv	orange 0x00F2D083	#Hex for orange
	.eqv	black 0x000000		#Hex for black
	.eqv	wh 0x00FFFDD0		#Hex for white
	
.data
	colors:		.word	red, blue, green, yellow, orange	#Array of possible colors user can choose
	saveX:		.word	0 					#Saves $a0, or the X value
	saveY:		.word	0 					#Saves $a1, or the Y value
	saveColor:	.word	0 					#Saves $a2, or the color value

#Console outputs
	intro1: 	.asciiz	"Etch-a-Sketch\n\n"
	intro2: 	.asciiz	"Press 'Enter' to start or 'Space' to exit\n\n"
	
	menuPrompt:	.asciiz	"Select one of the following, or press 'space' to exit:\n"
	menuSingle:	.asciiz	"1. Single pixel brush (p)\n"
	menuDouble:	.asciiz	"2. Double pixel brush (o)\n"
	menuLetter:	.asciiz "3. Letter Stamps(l)\n"
	menuColor:	.asciiz "4. Color change (j)\n"
	menuErase:	.asciiz "5. Eraser (c)\n"
	menuClear:	.asciiz "6. Wipe board (r) \n\n"
	
	singleIntro:	.asciiz "Single brush mode enabled, use w, a, s, d to move\n\n"
	doubleIntro:	.asciiz "Double brush mode enabled, use w, a, s, d to move\n\n"
	letterIntro1:	.asciiz "Letter stamp mode enabled, use 'SHIFT' + alphabet to pick stamp \n"
	letterIntro2:	.asciiz "Use w, a, s, d to move, 'l' to stamp\n"
	colorIntro:	.asciiz "Color changing, use 'q' to change color until console shows desired (red default) \n"
	eraserIntro:	.asciiz "Eraser enabled, use w, a, s, d to move\n\n"
	clearIntro:	.asciiz "Canvas has been cleared!\n\n"
	
	redPicked:	.asciiz "Color red loaded \n"
	bluePicked:	.asciiz "Color blue loaded \n"
	greenPicked: 	.asciiz "Color green loaded \n"
	yellowPicked: 	.asciiz "Color yellow loaded \n"
	orangePicked: 	.asciiz "Color orange loaded \n"
	
	drawPrompt: 		.asciiz "Start drawing!\n\n"
	PixelPlacementPrompt:	.asciiz "Select 'x' to start top right or 'c' for center\n\n"
	diffLetterPrompt:	.asciiz "Select 'k' to pick a different letter\n\n"
	returnMenuPrompt:	.asciiz "Press 'r' to return to the main menu\n\n"
	clearPrompt: 		.asciiz "Would you like to clear? (y) for yes, (n) for no\n"
	
	coordIntro: 		.asciiz "Now at: ("
	coordMid:		.asciiz ", "
	coordIntroFinish:	.asciiz ")\n"
	
#Alphabet matrices for intro and outro titles and the stamps
	letA: .word	0, 0, wh, 0, 0,	
		 	0, wh, 0, wh, 0, 
		 	0, wh, wh, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0
		 	
	letB: .word 	0, wh, wh, 0, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, wh, 0, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, 0, 0
		 	
	letC: .word	0, 0, wh, wh, 0, 
			0, wh, 0, 0, 0, 
			0, wh, 0, 0, 0,
			0, wh, 0, 0, 0,
			0, 0, wh, wh, 0
			
	letD:.word	0, wh, wh, 0, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, 0, 0
		
	letE: .word	0, wh, wh, wh, 0, 
			0, wh, 0, 0, 0, 
			0, wh, wh, 0, 0,
			0, wh, 0, 0, 0,
			0, wh, wh, wh, 0
			
	letF: .word 	0, wh, wh, wh, 0,
		 	0, wh, 0, 0, 0, 
		 	0, wh, wh, 0, 0,
		 	0, wh, 0, 0, 0,
		 	0, wh, 0, 0, 0
		 	
	letG: .word 	0, wh, wh, wh, 0,
		 	wh, 0, 0, 0, 0, 
		 	wh, 0, 0, wh, 0,
		 	wh, 0, 0, wh, 0,
		 	0, wh, wh, wh, 0
		 	
	letH: .word	0, wh, 0, wh, 0,
			0, wh, 0, wh, 0,
			0, wh, wh, wh, 0,
			0, wh, 0, wh, 0,
			0, wh, 0, wh, 0
			
	letJ: .word 	0, wh, wh, wh, 0,
		 	0, 0, 0, wh, 0, 
		 	0, 0, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, 0, 0
		 	
	letI: .word 	0, wh, wh, wh, 0,
		 	0, 0, wh, 0, 0, 
		 	0, 0, wh, 0, 0,
		 	0, 0, wh, 0, 0,
		 	0, wh, wh, wh, 0
	
		 	
	letK: .word	0, wh, 0, wh, 0,
			0, wh, wh, 0, 0,
			0, wh, 0, 0, 0,
			0, wh, wh, 0, 0,
			0, wh, 0, wh, 0
	
	letL: .word 	0, wh, 0, 0, 0,
		 	0, wh, 0, 0, 0, 
		 	0, wh, 0, 0, 0,
		 	0, wh, 0, 0, 0,
		 	0, wh, wh, wh, 0
		 	
	letM: .word 	0, wh, 0, wh, 0,
		 	0, wh, wh, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0
		 	
	letN: .word 	wh, 0, 0, 0, wh,
			wh, wh, 0, 0, wh,
			wh, 0, wh, 0, wh,
			wh, 0, 0, wh, wh,
			wh, 0, 0, 0, wh
	
	letO: .word 	0, wh, wh, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, wh, 0
		 	
	letP: .word 	0, wh, wh, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, wh, wh, 0,
		 	0, wh, 0, 0, 0,
		 	0, wh, 0, 0, 0
	
	letQ: .word 	0, wh, wh, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, wh, 0,
		 	0, 0, 0, 0, wh
	
	letR: .word 	0, wh, wh, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, wh, 0, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0
		 	
	letS: .word	0, wh, wh, wh, 0,
			0, wh, 0, 0, 0, 
			0, wh, wh, wh, 0,
			0, 0, 0, wh, 0,
			0, wh, wh, wh, 0
			
	letT: .word	0, wh, wh, wh, 0, 
			0, 0, wh, 0, 0, 
			0, 0, wh, 0, 0, 
			0, 0, wh, 0, 0,
			0, 0, wh, 0, 0
			
	letU: .word 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, wh, wh, wh, 0
		 	
	letV: .word 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0, 
		 	0, wh, 0, wh, 0,
		 	0, wh, 0, wh, 0,
		 	0, 0, wh, 0, 0
		 	
	letW: .word 	wh, 0, 0, 0, wh,
		 	wh, 0, 0, 0, wh, 
		 	wh, 0, wh, 0, wh,
		 	wh, wh, 0, wh, wh,
		 	wh, 0, 0, 0, wh
		 	
	letX: .word 	wh, 0, 0, 0, wh,
		 	0, wh, 0, wh, 0, 
		 	0, 0, wh, 0, 0,
		 	0, wh, 0, wh, 0,
		 	wh, 0, 0, 0, wh
		 	
	letY: .word 	wh, 0, 0, 0, wh,
		 	0, wh, 0, wh, 0, 
		 	0, 0, wh, 0, 0,
		 	0, 0, wh, 0, 0,
		 	0, 0, wh, 0, 0
		 	
	letZ: .word 	wh, wh, wh, wh, wh,
		 	0, 0, 0, wh, 0, 
		 	0, 0, wh, 0, 0,
		 	0, wh, 0, 0, 0,
		 	wh, wh, wh, wh, wh		 			
.text
main:
	#Intro title
	li	$v0, 4  
	la	$a0, intro1	#"Etch-a-Sketch\n"
	syscall	
	
	li	$v0, 4  
	la	$a0, intro2	#"Press 'Enter' to start or 'Space' to exit\n"
	syscall	

	li 	$a0, 19		#X value
	li 	$a1, 10		#Y value
	la 	$s3, letE	#Prints E
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letT 	#Prints T
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letC 	#Prints C
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letH 	#Prints H
	jal 	drawLetter
	
	li	$a0, 26 	#X value
	addi 	$a1, $a1, 10 	#Y value increments by 10 pixels
	la 	$s3, letA 	#Prints A
	jal 	drawLetter
	
	li 	$a0, 14 	#X value
	addi	$a1, $a1, 10 	#Y value increments by 10 pixels
	la	$s3, letS 	#Prints S
	jal 	drawLetter
	
	addi	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letK 	#Prints K
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letE 	#Prints E
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letT 	#Prints T
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letC 	#Prints C
	jal 	drawLetter
	
	addi 	$a0, $a0, 5 	#X value increments by 5 pixels
	la 	$s3, letH 	#Prints H
	jal 	drawLetter
	
enterBuffer: #enterBuffer is the buffer for the user so that they can pick
	     #the key to either continue to exit the program
	
	lw 	$t0, 0xffff0000		#Check whether input in keyboard
    	beq 	$t0, 0, enterBuffer	#If no input, keep on the same screen
    	
    	#Process what user input
	lw 	$s1, 0xffff0004
	beq	$s1, 10, enterCanvas 	#Input 'enter' to start the simulator
	beq	$s1, 32, exit		#Input 'space' to exit the program
	
	j	enterBuffer 		#Jump protection 

enterCanvas:	#enterCanvas is when the user is taken to the screen 
		#where they are able to use the program	
	jal 	blackoutScreen	#Blackout whole screen to give a clear slate
	
	addi	$a0, $0, WIDTH	#$a0 = X = WIDTH/2
	sra 	$a0, $a0, 1
	addi 	$a1, $0, HEIGHT	#$a1 = Y = HEIGHT/2
	sra 	$a1, $a1, 1
	addi 	$a2, $0, red 	#$a2 = red (default color)
	
	la 	$s4, colors 	#Load colors array into $s4 to use in colorChanger
	li 	$t3, 0 		#Colors array i = 0
	li 	$t8, 5 		#Colors array maximum length = 5
	
menu:	#Menu starts the menu list in console output and
	#lets the user select menu options
	li 	$v0, 4
	la 	$a0, menuPrompt	#"Select one of the following, or press 'space' to exit:\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuSingle	#"1. Single pixel brush (p)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuDouble	#"2. Double pixel brush (o)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuLetter	#"3. Letter Stamps(l)\n"
	syscall

menuBuffer: #menuBuffer keeps looping until user selects option
	lw	$t0, 0xffff0000		#Check whether input in keyboard
    	beq 	$t0, 0, menuBuffer	#If no input, keep on the same screen
    	
    	lw 	$s1, 0xffff0004 	#Process user input
	beq	$s1, 112, single 	#Input 'p' to go to single brush mode
	beq	$s1, 111, double	#Input 'o' to go to double brush mode
	beq 	$s1, 108, letterInit 	#Input 'l' to go to letter stamp mode
	beq	$s1, 32, exit		#Input 'space' to exit
	
	j 	menuBuffer 		#Jump protection
	
contMenu: #contMenu is the menu options after the user has
	  #selected something for the first time
	sw 	$a0, saveX	#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, menuPrompt	#"Select one of the following, or press 'space' to exit:\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuSingle	#"1. Single pixel brush (p)\n"
	syscall
	
	li	$v0, 4
	la 	$a0, menuDouble	#"2. Double pixel brush (o)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuLetter	#"3. Letter Stamps(l)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuColor	#"4. Color change (j)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuErase	#"5. Eraser (c)\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, menuClear	#"6. Wipe board (r) \n\n"
	syscall
	
	lw 	$a0, saveX 	#Load X back to $a0
	
menuContBuffer: #menuContBuffer loops until user selects an option
	lw 	$t0, 0xffff0000			#Check whether input in keyboard
    	beq 	$t0, 0, menuContBuffer		#If no input, keep on the same screen
    	
    	lw 	$s1, 0xffff0004 		#Process user input
	beq	$s1, 112, singleStartDrawing 	#Input 'p' to go to single brush with current location
	beq	$s1, 111, doubleStartDrawing 	#input 'o' to go to double brush with current location
	beq 	$s1, 108, letter 		#Input 'l' to go to letter stamp with current location
	beq 	$s1, 106, color 		#Input 'j' to go to color change mode
	beq	$s1, 99, erase 			#Input 'c' to go to eraser with current location
	beq 	$s1, 114, clear 		#Input 'r' to go to clear canvas 
	beq	$s1, 32, exit			#Input 'space' to exit
	
	j 	menuContBuffer 			#Jump protection
	
single:	#Beginning of the single pixel brush options
	li 	$v0, 4
	la 	$a0, singleIntro	#"Single brush mode enabled, use w, a, s, d to move\n\n"
	syscall
	
singlePixelPositionIntro: #Single pixel introduction
	li 	$v0, 4
	la 	$a0, PixelPlacementPrompt	#"Select 'x' to start top right or 'c' for center\n\n"
	syscall
	
singlePixelPositionBuffer: #Loop until the user selects position of single pixel
	lw 	$t0, 0xffff0000				#Check whether input in keyboard
    	beq 	$t0, 0, singlePixelPositionBuffer	#If no input, keep on the same screen
    	
    	lw 	$s1, 0xffff0004 			#Process user input
	beq	$s1, 120, singleTopLeftPixelInit 	#Input 'x' to place pixel top left
	beq	$s1, 99, singleCenterPixelInit 	#Input 'c' to place pixel center
	beq	$s1, 32, exit				#Input 'space' to exit
	
	j 	singlePixelPositionBuffer		#Jump protection

singleTopLeftPixelInit: #Initializes single pixel at (0,0)
	addi	$a0, $0, 0		#$a0 = X = WIDTH/2
	addi	$a1, $0, 0		#$a1 = Y = HEIGHT/2
	jal 	drawPixel 
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#$a0 = x
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#", "
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#$a0 = y
	syscall
	
	li 	$v0, 4
	la 	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back to $a0
	lw 	$a1, saveY		#Load Y back to $a1
	
	j	singleStartDrawing	#Skip over singleCenterPixelInit
	
singleCenterPixelInit:	#Initializes single pixel at (32, 32)
	addi 	$a0, $0, WIDTH    	# a0 = X = WIDTH/2
	sra 	$a0, $a0, 1
	addi 	$a1, $0, HEIGHT   	# a1 = Y = HEIGHT/2
	sra 	$a1, $a1, 1
	jal 	drawPixel 
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#$a0 = x
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#", "
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#$a0 = y
	syscall
	
	li 	$v0, 4
	la 	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw	$a0, saveX		#Load X back to $a0
	lw	$a1, saveY		#Load Y back to $a1

singleStartDrawing: #Initialization of single pixel brush
	sw 	$a0, saveX		#Save X to use $a0
	
	li	$v0, 4  
	la	$a0, drawPrompt		#"Start drawing!\n"
	syscall	
	
	li 	$v0, 4
	la 	$a0, returnMenuPrompt	#"Press 'r' to return to the main menu\n"
	syscall
	
	lw 	$a0, saveX 		#Load Y back to $a1

singleDrawBuffer: #Loop until the user decides how to draw with single pixel brush
	lw 	$t0, 0xffff0000			#Check whether input in keyboard
    	beq 	$t0, 0, singleDrawBuffer	#If no input, keep on the same screen
    	
	lw 	$s1, 0xffff0004
	beq	$s1, 119, singleUp 		#Input 'w' to draw up
	beq	$s1, 100, singleRight 		#Input 'd' to draw right
	beq	$s1, 115, singleDown 		#Input 's' to draw down
	beq 	$s1, 97, singleLeft 		#Input 'a' to draw left
	beq	$s1, 114, contMenu 		#Input 'r' to return to menu
	beq	$s1, 32, exit			#Input 'space' to exit

	j	singleDrawBuffer 		#Jump protection

double:	#Beginning of the double pixel brush options
	li 	$v0, 4
	la 	$a0, doubleIntro	#"Double brush mode enabled, use w, a, s, d to move\n\n"
	syscall
	
doublePixelPositionIntro:	#Double pixel introduction
	li 	$v0, 4
	la 	$a0, PixelPlacementPrompt	#"Select 'x' to start top right or 'c' for center\n"
	syscall
	
doublePixelPositionBuffer:	#Loop until the user selects position of double pixel
	lw 	$t0, 0xffff0000				#Check whether input in keyboard
    	beq 	$t0, 0, doublePixelPositionBuffer	#If no input, keep on the same screen
    	
    	lw 	$s1, 0xffff0004 			#Process user input
	beq	$s1, 120, doubleTopLeftPixelInit 	#Input 'x' to place double pixel top left
	beq	$s1, 99, doubleCenterPixelInit 	#Input 'c' to place double pixel center
	beq	$s1, 32, exit				#Input space
	
	j 	doublePixelPositionBuffer
	
doubleTopLeftPixelInit:	#Initializes double pixel at (0,0)
	addi 	$a0, $0, 0		#$a0 = X 
	addi 	$a1, $0, 0		#$a1 = Y
	jal 	drawDoublePixel

	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#$a0 = x
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#", "
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#$a0 = y
	syscall
	
	li 	$v0, 4
	la 	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw	$a0, saveX		#Load X back to $a0
	lw	$a1, saveY		#Load Y back to $a1
	
	j doubleStartDrawing
	
doubleCenterPixelInit:	#Initializes pixel at (32, 32)
	addi 	$a0, $0, WIDTH    	#$a0 = X = WIDTH/2
	sra 	$a0, $a0, 1
	addi 	$a1, $0, HEIGHT   	#$a1 = Y = HEIGHT/2
	sra 	$a1, $a1, 1	
	jal 	drawDoublePixel 
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#$a0 = x
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#", "
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#$a0 = y
	syscall
	
	li 	$v0, 4
	la 	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw	$a0, saveX		#Load X back to $a0
	lw	$a1, saveY		#Load Y back to $a1
	
doubleStartDrawing:	#Initialization of double pixel brush
	sw 	$a0, saveX		#Save X to use $a0
	
	li	$v0, 4  
	la	$a0, drawPrompt 	#"Start drawing!\n"
	syscall	
	
	li	$v0, 4
	la 	$a0, returnMenuPrompt #"Press 'r' to return to the main menu\n"
	syscall
	
	lw	$a0, saveX 		#Load back X to $a0
	
doubleDrawBuffer:	#Loop until the user decides how to draw with double pixel brush
	lw 	$t0, 0xffff0000			#Check whether input in keyboard
    	beq 	$t0, 0, doubleDrawBuffer	#If no input, keep on the same screen

	lw 	$s1, 0xffff0004
	beq	$s1, 119, doubleUp		#Input 'w' to draw double pixel up
	beq	$s1, 100, doubleRight 		#Input 'd' to draw double pixel right
	beq	$s1, 115, doubleDown		#Input 's' to draw double pixel down
	beq 	$s1, 97, doubleLeft 		#Input 'a' to draw double pixel left
	beq	$s1, 114, contMenu		#Input 'r' to return to menu
	beq	$s1, 32, exit			#Input 'space' to return to menu

	j	doubleDrawBuffer 		#Jump protection 
	
letterInit:	#Position initialization for letter stamp when selected through initial menu
	addi 	$a0, $0, 0	#X = 0
	addi 	$a1, $0, 0	#Y = 0
	
letter:		#Actual continuation of letter section
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, letterIntro1	#"Letter stamp mode enabled, use 'SHIFT' + alphabet to pick stamp \n"
	syscall
	
	lw $a0, saveX			#Load X back to $a0

letterPickerBuffer:	#Loop until user decides which alphabetical letter to use
	lw 	$t0, 0xffff0000			#Check whether input in keyboard
    	beq 	$t0, 0, letterPickerBuffer	#If no input, keep on the same screen

	lw 	$s1, 0xffff0004
	beq	$s1, 65, storeA 		#Input 'A' to load A
	beq	$s1, 66, storeB 		#Input 'B' to load B
	beq	$s1, 67, storeC 		#Input 'C' to load C
	beq	$s1, 68, storeD 		#Input 'D' to load D
	beq	$s1, 69, storeE			#Input 'E' to load E
	beq	$s1, 70, storeF 		#Input 'F' to load F
	beq	$s1, 71, storeG 		#Input 'G' to load G
	beq	$s1, 72, storeH 		#Input 'H' to load H
	beq	$s1, 73, storeI 		#Input 'I' to load I
	beq	$s1, 74, storeJ 		#Input 'J' to load J
	beq	$s1, 75, storeK 		#Input 'K' to load K
	beq	$s1, 76, storeL 		#Input 'L' to load L
	beq	$s1, 77, storeM 		#Input 'M' to load M
	beq	$s1, 78, storeN 		#Input 'N' to load N
	beq	$s1, 79, storeO 		#Input 'O' to load O
	beq	$s1, 80, storeP 		#Input 'P' to load P
	beq	$s1, 81, storeQ 		#Input 'Q' to load Q
	beq	$s1, 82, storeR 		#Input 'R' to load R
	beq	$s1, 83, storeS 		#Input 'S' to load S
	beq	$s1, 84, storeT 		#Input 'T' to load T
	beq	$s1, 85, storeU 		#Input 'U' to load U
	beq	$s1, 86, storeV 		#Input 'V' to load V
	beq	$s1, 87, storeW 		#Input 'W' to load W
	beq	$s1, 88, storeX 		#Input 'X' to load X
	beq	$s1, 89, storeY 		#Input 'Y' to load Y
	beq	$s1, 90, storeZ 		#Input 'Z' to load Z
	beq	$s1, 114, contMenu		#Input 'r' to return to menu
	beq	$s1, 92, exit			#Input 'space' to exit
	
	j	letterPickerBuffer 		#Jump protection

storeA:	#Stores matrix A into the byte array to use in the letter functions
	la 	$s3, letA	#Loads A into register
	j 	letterIntro	
	
storeB:	#Stores matrix B into the byte array to use in the letter functions
	la 	$s3, letB	#Loads B into register
	j	letterIntro	
	
storeC:	#Stores matrix C into the byte array to use in the letter functions
	la 	$s3, letC	#Loads C into register
	j 	letterIntro

storeD:	#Stores matrix D into the byte array to use in the letter functions
	la 	$s3, letD	#Loads D into register
	j 	letterIntro
	
storeE:	#Stores matrix E into the byte array to use in the letter functions
	la 	$s3, letE	#Loads E into register
	j 	letterIntro

storeF:	#Stores matrix F into the byte array to use in the letter functions
	la 	$s3, letF	#Loads F into register
	j 	letterIntro
	
storeG:	#Stores matrix G into the byte array to use in the letter functions
	la 	$s3, letG	#Loads G into register
	j 	letterIntro

storeH:	#Stores matrix H into the byte array to use in the letter functions
	la 	$s3, letH	#Loads H into register
	j 	letterIntro

storeI:	#Stores matrix I into the byte array to use in the letter functions
	la 	$s3, letI	#Loads I into register
	j 	letterIntro

storeJ:	#Stores matrix J into the byte array to use in the letter functions
	la 	$s3, letJ	#Loads J into register
	j 	letterIntro

storeK:	#Stores matrix K into the byte array to use in the letter functions
	la 	$s3, letK	#Loads K into register
	j 	letterIntro

storeL:	#Stores matrix L into the byte array to use in the letter functions
	la 	$s3, letL	#Loads L into register
	j 	letterIntro

storeM:	#Stores matrix M into the byte array to use in the letter functions
	la 	$s3, letM	#Loads M into register
	j 	letterIntro

storeN:	#Stores matrix N into the byte array to use in the letter functions
	la 	$s3, letN	#Loads N into register
	j 	letterIntro

storeO:	#Stores matrix O into the byte array to use in the letter functions
	la 	$s3, letO	#Loads O into register
	j 	letterIntro

storeP:	#Stores matrix P into the byte array to use in the letter functions
	la 	$s3, letP	#Loads P into register
	j 	letterIntro

storeQ:	#Stores matrix Q into the byte array to use in the letter functions
	la 	$s3, letQ	#Loads Q into register
	j 	letterIntro

storeR:	#Stores matrix R into the byte array to use in the letter functions
	la 	$s3, letR	#Loads R into register
	j 	letterIntro

storeS:	#Stores matrix S into the byte array to use in the letter functions
	la 	$s3, letS	#Loads S into register
	j 	letterIntro

storeT:	#Stores matrix T into the byte array to use in the letter functions
	la 	$s3, letT	#Loads T into register
	j 	letterIntro

storeU:	#Stores matrix U into the byte array to use in the letter functions
	la	$s3, letU	#Loads U into register
	j 	letterIntro

storeV:	#Stores matrix V into the byte array to use in the letter functions
	la 	$s3, letV	#Loads V into register
	j 	letterIntro

storeW:	#Stores matrix W into the byte array to use in the letter functions
	la	$s3, letW	#Loads W into register
	j 	letterIntro

storeX:	#Stores matrix X into the byte array to use in the letter functions
	la 	$s3, letX	#Loads X into register
	j 	letterIntro

storeY:	#Stores matrix Y into the byte array to use in the letter functions
	la 	$s3, letY	#Loads Y into register
	j 	letterIntro

storeZ:	#Stores matrix Z into the byte array to use in the letter functions
	la 	$s3, letZ	#Loads Z into register

letterIntro:	#Intro output to the letter stamp function
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, letterIntro2	#"Use w, a, s, d to move, l to stamp\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, diffLetterPrompt	#"Select 'k' to pick a different letter\n\n"
	syscall
	
	li 	$v0, 4
	la 	$a0, returnMenuPrompt	#"Would you like to clear? (y) for yes, (n) for no\n"
	syscall
	
	lw $a0, saveX			#Load X back to $a0
	
letterBuffer:	#Loop until user decides how to proceed with letter stamp function
	lw 	$t0, 0xffff0000			#Check whether input in keyboard
    	beq	$t0, 0, letterBuffer		#If no input, keep on the same screen
    	
	lw 	$s1, 0xffff0004
	beq	$s1, 119, letterUp 		#Input 'w' to move up
	beq	$s1, 100, letterRight 		#Input 'd' to move right
	beq	$s1, 115, letterDown 		#Input 's' to move down
	beq 	$s1, 97, letterLeft 		#Input 'a' to move left
	beq	$s1, 108, letterStamp 		#Input 'l' to stamp a letter
	beq	$s1, 107, letter 		#Input 'k' to return to pick a different alphabet
	beq	$s1, 114, contMenu		#Input 'r' to return to menu
	beq	$s1, 32, exit			#Input 'space' to exit

	j	letterBuffer 			#Jump protection
	
color:	#Start of the color changing function
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, colorIntro		#"Color changing, use 'q' to change color until console shows desired (red default) \n"
	syscall
	
	li 	$v0, 4
	la 	$a0, returnMenuPrompt #"Press 'r' to return to the main menu\n"
	syscall
	
	lw 	$a0, saveX		#Load X back to $a0
	
colorBuffer:	#Loops until user decides whether to change color or not
	lw 	$t0, 0xffff0000  	#Check whether input in keyboard
    	beq 	$t0, 0, colorBuffer   	#If no input, keep on the same screen
    	
	lw 	$s1, 0xffff0004
	beq	$s1, 113, colorOptions	#Input 'q' to change color
	beq	$s1, 114, contMenu	#Input 'r' to return to menu
	beq	$s1, 32, exit		#Input 'space' to exit

	j	colorBuffer		#Jump protection
	
erase:		#Start of the erase function
	sw 	$a0, saveX 		#Save X to use $a0	
	
	li 	$v0, 4
	la 	$a0, eraserIntro	#"Eraser enabled, use w, a, s, d to move\n\n"	
	syscall
	
	li 	$v0, 4
	la 	$a0, returnMenuPrompt 	#"Press 'r' to return to the main menu\n"
	syscall
	
	lw 	$a0, saveX 		#Load X back to $a0
	
eraseBuffer:	#Loop until user decides how to proceed with eraser
	lw 	$t0, 0xffff0000		#Check whether input in keyboard
    	beq 	$t0, 0, eraseBuffer	#If no input, keep on the same screen
    	
	lw 	$s1, 0xffff0004
	beq	$s1, 119, eraseUp 	#Input 'w' to erase up
	beq	$s1, 100, eraseRight 	#Input 'd' to erase right
	beq	$s1, 115, eraseDown 	#Input 's' to erase down
	beq 	$s1, 97, eraseLeft 	#Input 'a' to erase left
	beq	$s1, 114, contMenu	#Input 'r' to return to menu
	beq	$s1, 32, exit		#Input 'space' to exit

	j	eraseBuffer 		#Jump protection
	
clear:	#Start of clear canvas function
	sw 	$a0, saveX		#Save X to use $a0
	
	li	$v0, 4
	la 	$a0, clearPrompt	#"Would you like to clear? (y) for yes, (n) for no\n"
	syscall
	
	lw 	$a0, saveX		#Load X back to $a0
	
clearQuestionBuffer:	#Loop until user decides to clear canvas or not
	lw 	$t0, 0xffff0000  		#Check whether input in keyboard
    	beq 	$t0, 0, clearQuestionBuffer   #If no input, keep on the same screen
    	
	lw 	$s1, 0xffff0004
	beq	$s1, 121, cleared 		#Input 'y' to clear canvas
	beq	$s1, 110, contMenu 		#Input 'n' to return to menu
	beq	$s1, 32, exit			#Input 'space' to exit

	j	clearQuestionBuffer 		#Jump protection
	
cleared:	#Clears the canvas
	jal 	blackoutScreen		#Blacks out the whole bitmap screen
	
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, clearIntro		#"Canvas has been cleared!\n\n"
	syscall
	
	lw 	$a0, saveX		#Load X back to $a0
	
	j 	menu			
	
exit:	#Exit of the program
	jal 	blackoutScreen	#Blacks out the whole bitmap screen
	
	li 	$a0, 15 	#X value
	li 	$a1, 10 	#Y value
	la 	$s3, letT	#Prints T
	jal 	drawLetter
	
	addi	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letH	#Prints H
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letA	#Prints A
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letN	#Prints N
	jal	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letK	#Prints K
	jal 	drawLetter
	
	li 	$a0, 20		#X value
	addi 	$a1, $a1, 10	#Y value increments by 10 pixels
	la 	$s3, letY	##Prints Y
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letO	#Prints O
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letU	#Prints U
	jal 	drawLetter
	
	li 	$a0, 21		#X value
	addi 	$a1, $a1, 10	#Y value increments by 10 pixels
	la 	$s3, letF	#Prints F
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la	$s3, letO	#Prints O
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letR	#Prints R
	jal 	drawLetter
	
	li 	$a0, 10		#X value
	addi 	$a1, $a1, 10	#Y value increments by 10 pixels
	la 	$s3, letP	#Prints P
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letL	#Prints L
	jal 	drawLetter	
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letA	#Prints A
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letY	#Prints Y
	jal 	drawLetter
	
	addi	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letI	#Prints I
	jal 	drawLetter
	
	addi 	$a0, $a0, 5	#X value increments by 5 pixels
	la 	$s3, letN	#Prints N
	jal 	drawLetter
	
	addi 	$a0, $a0, 6	#X value increments by 6 pixels
	la 	$s3, letG	#Prints G
	jal 	drawLetter
	
	li	$v0, 10     	#Syscall for exit
	syscall	
###################### FUNCTIONS #############################
drawPixel:	#drawPixel draws a single pixel in the memory
	#$a0 = X, $a1 = Y, $a2 = color
	#s1 = address = $gp + 4*(x + y*width)
	mul	$t9, $a1, WIDTH		#y * WIDTH
	add	$t9, $t9, $a0		#Add X
	mul	$t9, $t9, 4	  	#Multiply by 4 to get word offset
	add	$t9, $t9, $gp	 	#Add to base address
	sw	$a2, ($t9)	 	#Store color at memory location
	jr 	$ra

################# BLACKOUT FUNCTIONS ##############################
blackoutScreen: #blackoutScreen wipes the whole screen of all the user actions
		#to create a blank slate
	sw 	$a2, saveColor		#Save color to use $a2
	
	addi 	$t1, $0, WIDTH 		#Maximum width index
	addi 	$t2, $0, HEIGHT 	#Maximum height index
	addi 	$a2, $0, black		#Load black into $a2
	
	li 	$a0, 0 			#X = 0
	li 	$a1, 0 			#Y = 0

blackoutLoop:	#blackoutLoop loops until every canvas pixel is black
	beq 	$a1, $t2, blackoutXIncrement	#When Y = maximum height index
	
	mul	$t9, $a1, WIDTH   		#y * WIDTH
	add	$t9, $t9, $a0	  		#Add X
	mul	$t9, $t9, 4	  		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp	  		#Add to base address
	sw	$a2, ($t9)	  		#Store color at memory location
	
	addi 	$a1, $a1, 1			#Y++
	
	j 	blackoutLoop			

blackoutXIncrement:	#blackoutXIncrement increments X value of outer loop
	beq 	$a0, $t1, exitBlackout		#When X = maximum width index
	
	li 	$a1, 0				#Reset to Y = 0
	addi 	$a0, $a0, 1 			#X++
	
	j 	blackoutLoop
	
exitBlackout: #exitBlackout exits the blackoutScreen function
	lw 	$a2, saveColor			#Load color back into $a2
	jr 	$ra
	
######################## ERASE FUNCTIONS ###############################
eraseUp:	#eraseUp erases one pixel up
	sw	$a2, saveColor		#Save color to use $a2
	addi 	$a2, $0, black		#$a2 = black
	addi	$a1, $a1, -1		#Move one up
	jal	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	lw 	$a2, saveColor		#Load color back into $a2
	
	j 	eraseBuffer
	
eraseRight:	#eraseRight erases one pixel right
	sw	$a2, saveColor		#Save color to use $a2
	addi 	$a2, $0, black		#$a2 = black
	addi	$a0, $a0, 1		#Move one right
	jal	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	lw 	$a2, saveColor		#Load color back into $a2
	
	j 	eraseBuffer
	
eraseDown:	#eraseDown erases one pixel down
	sw	$a2, saveColor		#Save color to use $a2
	addi 	$a2, $0, black		#$a2 = black
	addi	$a1, $a1, 1		#Move one down
	jal	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	lw 	$a2, saveColor		#Load color back into $a2
	
	j 	eraseBuffer
	
eraseLeft:	#eraseLeft erases one pixel left
	sw	$a2, saveColor		#Save color to use $a2
	addi 	$a2, $0, black		#$a2 = black
	addi	$a0, $a0, -1		#Move one left
	jal	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	lw 	$a2, saveColor		#Load color back into $a2
	
	j 	eraseBuffer

################ SINGLE PIXEL BRUSH FUNCTIONS #######################
singleUp: #singleUp draws one pixel up
	addi	$a1, $a1, -1		#Move one up
	jal	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	
	j 	singleDrawBuffer
	
singleRight:	#singleRight draws one pixel right
	addi	$a0, $a0, 1		#Move one right
	jal 	drawPixel 
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	
	j 	singleDrawBuffer
	
singleDown:	#singleDown draws one pixel down
	addi	$a1, $a1, 1		#Move one down
	jal 	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	
	j 	singleDrawBuffer
	
singleLeft:	#singleLeft draws one pixel left
	addi	$a0, $a0, -1		#Move one left
	jal 	drawPixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	
	j 	singleDrawBuffer

######################### DOUBLE PIXEL BRUSH FUNCTIONS ####################
drawDoublePixel:	#drawDoublePixel draws a double pixel brush stroke
	mul	$t9, $a1, WIDTH		#y * WIDTH
	add	$t9, $t9, $a0		#Add X
	mul	$t9, $t9, 4		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp		#Add to base address
	sw	$a2, ($t9)		#Store color at memory location
	
	addi 	$a0, $a0, 1		#Move one right
	
	mul	$t9, $a1, WIDTH		#y * WIDTH
	add	$t9, $t9, $a0		#Add X
	mul	$t9, $t9, 4		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp		#Add to base address
	sw	$a2, ($t9)		#Store color at memory location
	
	addi 	$a1, $a1, 1		#Move one down
	
	mul	$t9, $a1, WIDTH		#y * WIDTH
	add	$t9, $t9, $a0		#Add X
	mul	$t9, $t9, 4		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp		#Add to base address
	sw	$a2, ($t9)		#Store color at memory location
	
	addi 	$a0, $a0, -1		#Move one left
	
	mul	$t9, $a1, WIDTH		#y * WIDTH
	add	$t9, $t9, $a0		#Add X
	mul	$t9, $t9, 4		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp		#Add to base address
	sw	$a2, ($t9)		#Store color at memory location
	
	addi 	$a1, $a1, -1		#Move one up
	
	jr 	$ra
	
doubleUp:	#doubleUp draws one double pixel up
	addi	$a1, $a1, -1		#Move one up
	jal 	drawDoublePixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	doubleDrawBuffer
	
doubleRight:	#doubleRight draws one double pixel right
	addi	$a0, $a0, 1		#Move one right
	jal 	drawDoublePixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	doubleDrawBuffer
	
doubleDown:	#doubleDown draws one double pixel down
	addi	$a1, $a1, 1		#Move one down
	jal 	drawDoublePixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1
	
	j 	doubleDrawBuffer
	
doubleLeft:	#doubleLeft draws one double pixel left
	addi	$a0, $a0, -1		#Move one left
	jal 	drawDoublePixel
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	doubleDrawBuffer
	
######################### LETTER FUNCTIONS #############################
letterUp:	#letterUp moves the letter coordinate up
	addi	$a1, $a1, -1		#Move one up
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	letterBuffer
	
letterRight:	#letterRight moves the letter coordinate right
	addi	$a0, $a0, 1
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	letterBuffer
	
letterDown:	#letterDown moves the letter coordinate down
	addi	$a1, $a1, 1
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	letterBuffer
	
letterLeft:	#letterLeft moves the letter coordinate left
	addi	$a0, $a0, -1
	
	sw 	$a0, saveX		#Save X to use $a0
	sw 	$a1, saveY		#Save Y to use $a1
	
	li 	$v0, 4
	la 	$a0, coordIntro		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveX		#Print X value
	syscall
	
	li 	$v0, 4
	la 	$a0, coordMid		#"Now at: ("
	syscall
	
	li 	$v0, 1
	lw 	$a0, saveY		#Print Y value
	syscall
	
	li 	$v0, 4
	la	$a0, coordIntroFinish	#")\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	lw 	$a1, saveY		#Load Y back into $a1

	j 	letterBuffer
	
letterStamp:	#letterStamp stamps a letter in the current coordinate
	jal	drawLetter
	j	letterBuffer
	
drawLetter:	#drawletter draws a letter in the memory location
	add 	$t4, $a0, $0		#$t4 holds current X for incrementation
	add 	$t5, $a1, $0		#$t5 holds current Y for incrementation
	
	addi	$t6, $t4, let_w 	#$t6 holds letter width
	addi 	$t7, $t5, let_h 	#$t7 holds letter height
	
drawLetterLoop:	#drawLetterLoop traverses through the whole letter matrix
	lw 	$s2, 0($s3) 			#Load first byte of letter matrix
	addi 	$s3, $s3, 4 			#Increment 4 bytes in letter matrix
	addi 	$t4, $t4, 1 			#Increment width index by 1
	
	mul	$t9, $t5, WIDTH			#y * WIDTH
	add	$t9, $t9, $t4	  		#Add X
	mul	$t9, $t9, 4	  		#Multiply by 4 to get word offset
	add	$t9, $t9, $gp	  		#Add to base address
	sw	$s2, ($t9)	  		#Store color at memory location
	
	bne 	$t4, $t6, drawLetterLoop	#Loop until width index hits maximum width
	
	addi 	$t5, $t5, 1			#Increment height index by 1
	add 	$t4, $a0, $0 			#Reset X index for the next line
	
	beq 	$t5, $t7, exitLetterLoop	#Loop until height index hits maximum height
	
	j 	drawLetterLoop
	
exitLetterLoop:
	addi 	$s3, $s3, -100			#Reset the byte counter back to 0
	jr 	$ra
######################## COLOR FUNCTIONS ###############################
colorOptions:	#colorOptions changes color by one color
	jal 	changeColor	
	j 	colorBuffer	
	
changeColor:	#changeColor moves over pointer in the colors array
	addi 	$t3, $t3, 1	#Increment color array index by 1
	addi 	$s4, $s4, 4	#Increment color memory by 4
	
	j 	resetColor
	
resetColor:	#resetColor resets the color array if it hits the end
	bne 	$t3, $t8, colorOutput	#Proceed to colorOutput if color index isn't equal to maximum
	
	li	$t3, 0			#Reset color array index
	addi 	$s4, $s4, -20		#Reset color memory to beginning of array
	
	j 	colorOutput		
	
colorOutput:	#colorOutput outputs color based on the one pointed at in array
	lw 	$a2, 0($s4)		#Load current color to $a2 for use
	
	beq 	$t3, 0, redMode		#If index is 0, color is red
	beq 	$t3, 1, blueMode	#If index is 1, color is blue
	beq 	$t3, 2, greenMode	#If index is 2, color is green
	beq 	$t3, 3, yellowMode	#If index is 3, color is yellow
	beq 	$t3, 4, orangeMode	#If index is 4, color is orange
	
redMode:	#redMode gives console output for enabling red
	sw 	$a0, saveX	#Save X to use $a0
	
	li 	$v0, 4
	la	$a0, redPicked	#"Color red loaded \n"
	syscall
	
	lw 	$a0, saveX	#Load X back into $a0
	
	j 	exitColorLoop
	
blueMode:	#blueMode gives console output for enabling blue
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, bluePicked		#"Color blue loaded \n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	
	j 	exitColorLoop
	
greenMode:	#greenMode gives console output for enabling green
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, greenPicked	#"Color green loaded \n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	
	j 	exitColorLoop
	
yellowMode:	#yellowMode gives console output for enabling yellow
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, yellowPicked 	#"Color yellow loaded \n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	
	j 	exitColorLoop
	
orangeMode:	#orangeMode gives console output for enabling orange
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, orangePicked	#"Color orange loaded \n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	
	j 	exitColorLoop
	
exitColorLoop:	#exitColorLoop exits color array loop
	sw 	$a0, saveX		#Save X to use $a0
	
	li 	$v0, 4
	la 	$a0, colorIntro		#"Color changing, use 'q' to change color until console shows desired (red default) \n"
	syscall
	
	li 	$v0, 4
	la 	$a0, returnMenuPrompt	#"Press 'r' to return to the main menu\n"
	syscall
	
	lw 	$a0, saveX		#Load X back into $a0
	
	jr 	$ra
