#Instructions:
#	set pixel dim to 4x4
#	set display dim to 256x256
#	connect keyboard and run
#	w (up), s (down), a (left), d (right), space (exit)

#constants
	.eqv width 64	#width of pixels
	.eqv height 64	#height of pixels
	
#colors
	.eqv red	0x00FF0000
	.eqv green	0x0000FF00
	.eqv blue	0x000000FF
	.eqv white	0x00FFFFFF
	.eqv yellow	0x00FFFF00
	.eqv cyan	0x0000FFFF
	.eqv magenta	0x00FF00FF

.data
	colors: .word magenta, cyan, yellow, white, blue, green, red	#color array to loop through

.text
main:
	li $t1, 0 #i = 0, pixels
	li $t2, 7 #number of pixels per loop
	
	la $s0, colors #load color array
	li $t0, 0	#i = 0, colors
	li $t3, 7	#color array numbers
	
	#top left pixel location
	addi $a0, $0, width	#a0 = x = width / 2 (start)
	sra $a0, $a0, 1
	addi $a1, $0, height	#a1 = y = height / 2 (start)
	sra $a1, $a1, 1
	
	jal draw_pixel

loop:		#loop to draw the square
	lw $t9, ($s0)		#load color
	addi $t0, $t0, 1	#increment index
	addi $s0, $s0, 4	#increment array 
	add $a2, $0, $t9	#add color to argument
	jal draw_pixel
	
topLoop:	#draw the top pixels
	beq $t1, $t2, rightLoopStart	#if i = 7, go to rightLoopStart
	addi $a0, $a0, 1	#move one position to the right
	
	lw $t9, ($s0)		#load color from array into register
	addi $t0, $t0, 1	#increment color array index
	addi $s0, $s0, 4	#increment color array byte
	add $a2, $0, $t9	#add color from array to argument	
	jal draw_pixel		#draw pixel
	
	addi $t1, $t1, 1	#increment pixel counter
	
	j topLoop		#restart loop
	
rightLoopStart:	#start rightLoop	
	li $t1, 0 # reset pixel counter i = 0
	
rightLoop: #draw the right pixels
	beq $t1, $t2, botLoopStart	#if i = 7, go to botLoopStart
	addi $a1, $a1, 1		#move one position down
	
	lw $t9, ($s0)			#load color from array into register
	addi $t0, $t0, 1		#increment color array index			
	addi $s0, $s0, 4		#increment color array byte
	add $a2, $0, $t9		#add color from array to argument
	jal draw_pixel			#draw pixel
	
	addi $t1, $t1, 1		#increment pixel counter
	
	j rightLoop			#restart loop
	
botLoopStart:	#start botLoop
	li $t1, 0 # reset pixel counter i = 0
	
botLoop: #draw the bottom pixels
	beq $t1, $t2, leftLoopStart	#if i = 7, go to leftLoopStart
	addi $a0, $a0, -1		#move one position to the left
	
	lw $t9, ($s0)			#load color from array into register
	addi $t0, $t0, 1		#increment color array index
	addi $s0, $s0, 4		#increment color array byte
	add $a2, $0, $t9		#add color from array to argument
	jal draw_pixel
	
	addi $t1, $t1, 1		#increment pixel counter
	
	j botLoop			#restart loop
	
leftLoopStart: #start leftLoop
	li $t1, 0 # reset pixel counter i = 0
	
leftLoop: #draw the left pixels
	beq $t1, $t2, cont	#if i = 7, go to cont
	addi $a1, $a1, -1	#move one position up
	
	lw $t9, ($s0)		#load color from array into register
	addi $t0, $t0, 1	#increment color array index
	addi $s0, $s0, 4	#increment color array byte
	add $a2, $0, $t9	#add color from array to argument
	jal draw_pixel

	addi $t1, $t1, 1	#increment pixel counter
	
	j leftLoop		#restart loop

cont:
	li $t1, 0 # reset pixel counter i = 0
	
	# check for user keyboard input
	lw $t4, 0xffff0000	#t1 holds if input available
	beq $t4, 0,loop		#if no input, keep displaying
	
	# process keyboard input
	lw 	$s2, 0xffff0004
	beq	$s2, 32, exit	#input space
	beq	$s2, 119, up 	#input w
	beq	$s2, 115, down 	#input s
	beq	$s2, 97, left  	#input a
	beq	$s2, 100, right	#input d
	
	j loop			#restart marquee loop

#################################################
up:	#loop to move up square
	addi $t7, $a0, 0	#save a0 to t7
	addi $t8, $a1, 0	#save a1 to t8
	
	jal clear_canvas	#blackout current square
	
	addi $a0, $t7, 0 	#save t7 to a0
	addi $a1, $t8, 0 	#save t8 to a1
	addi $a1, $a1, -1 	#move square up
	jal draw_pixel		#redraw square
	
	j loop			#go back to marquee loop
	
down:	#loop to move down square
	addi $t7, $a0, 0	#save a0 to t7
	addi $t8, $a1, 0	#save a1 to t8
	
	jal clear_canvas	#blackout current square
	
	addi $a0, $t7, 0 	#save t7 to a0
	addi $a1, $t8, 0 	#save t8 to a1
	addi $a1, $a1, 1	#move square down
	jal draw_pixel		#redraw square
	
	j loop			#go back to marquee loop
	
left:
	addi $t7, $a0, 0 	#save a0 to t7
	addi $t8, $a1, 0 	#save a1 to t8
	
	jal clear_canvas	#blackout current square
	
	addi $a0, $t7, 0 	#save t7 to a0
	addi $a1, $t8, 0 	#save t8 to a1
	addi $a0, $a0, -1	#move square left
	jal draw_pixel		#redraw square
	
	j loop			#go back to marquee loop
	
right:
	addi $t7, $a0, 0 	#save a0 to t7
	addi $t8, $a1, 0 	#save a1 to t8
	
	jal clear_canvas	#blackout current square
	
	addi $a0, $t7, 0 	#save t7 to a0
	addi $a1, $t8, 0 	#save t8 to a1
	addi $a0, $a0, 1	#move square right
	jal draw_pixel		#redraw square
	
	j loop			#go back to marquee loop
		
exit:
	li $v0, 10
	syscall

#################################################
#$a0 = x
#$a1 = y
#$a2 = color

draw_pixel:	#draw pixel on bitmap
	#s1 = address = $gp + 4*(x + y*width)
	mul $s1, $a1, width	# y * width
	add $s1, $s1, $a0	# add x
	mul $s1, $s1, 4		# *4 to get word offset
	add $s1, $s1, $gp 	# add to base address
	sw $a2, 0($s1) 		#store color at memory location
	
	bne $t0, $t3, continue #if color index has not been completely gone through, continue
	li $t0, 0 		#reset color index to i = 0
	addi $s0, $s0, -28 	#start color array pointer all over

continue:	#continue the loop
	add $t5, $a0, $0 	#save current width
	
	li $v0, 32		#syscall for sleep
	li $a0, 5 		#5 ms timer delay
	syscall
	
	add $a0, $t5, $0 	#push back the old width to register
	jr $ra
	
######################################################

clear_canvas:	#black out the entire current canvas
	add $a2, $0, $zero	#set color to black
	
	#s1 = address = $gp + 4*(x + y*width)
	mul $s1, $a1, width 	# y * width
	add $s1, $s1, $a0 	# add x
	mul $s1, $s1, 4 	# *4 to get word offset
	add $s1, $s1, $gp 	# add to base address
	sw $a2, 0($s1) 		#store color at memory location
	
clearTopLoop:	#black out top pixels
	beq $t1, $t2, clearRightLoopStart	#if i = 7, move to clearRightLoop
	
	addi $a0, $a0, 1			#move one to the left
	add $a2, $0, $zero 			#set color to black
	addi $t1, $t1, 1			#increment pixel counter
	
	mul $s1, $a1, width 			# y * width
	add $s1, $s1, $a0 			# add x
	mul $s1, $s1, 4 			# *4 to get word offset
	add $s1, $s1, $gp 			# add to base address
	sw $a2, 0($s1) 				#store color at memory location
	
	j clearTopLoop				#restart loop
	
clearRightLoopStart:	#start of clearRightLoop
	li $t1, 0 	#reset pixel counter to i = 0
	
clearRightLoop:	#black out right pixels
	beq $t1, $t2, clearBotLoopStart	#if i = 7, move to clearBotLoop
	
	addi $a1, $a1, 1			#move one down
	add $a2, $0, $zero 			#set color to black
	addi $t1, $t1, 1			#increment pixel counter
	
	mul $s1, $a1, width 			# y * width
	add $s1, $s1, $a0 			# add x
	mul $s1, $s1, 4 			# *4 to get word offset
	add $s1, $s1, $gp 			# add to base address
	sw $a2, 0($s1) 				#store color at memory location
		
	j clearRightLoop			#restart loop
	
clearBotLoopStart:	#start of clearBotLoop
	li $t1, 0 	#reset pixel counter to i = 0
	
clearBotLoop: #black out bottom pixels
	beq $t1, $t2, clearLeftLoopStart	#if i = 7, move to clearLeftLoop
	
	addi $a0, $a0, -1			#move one left
	add $a2, $0, $zero 			#set color to black
	addi $t1, $t1, 1			#increment pixel counter

	mul $s1, $a1, width 			# y * width
	add $s1, $s1, $a0 			# add x
	mul $s1, $s1, 4 			# *4 to get word offset
	add $s1, $s1, $gp 			# add to base address
	sw $a2, 0($s1) 				#store color at memory location
	
	j clearBotLoop				#restart loop
	
clearLeftLoopStart:	#start of clearLeftLoop
	li $t1, 0 # i = 0
	
clearLeftLoop: #black out left pixels
	beq $t1, $t2, clearCont		#if i = 7, continue
	
	addi $a1, $a1, -1			#move one up
	add $a2, $0, $zero 			#set color to black
	addi $t1, $t1, 1			#increment pixel counter
	
	mul $s1, $a1, width 			# y * width
	add $s1, $s1, $a0 			# add x
	mul $s1, $s1, 4 			# *4 to get word offset
	add $s1, $s1, $gp 			# add to base address
	sw $a2, 0($s1) 				#store color at memory location

	j clearLeftLoop				#restart loop
	
clearCont:					#finish clearing the square
	li $t1, 0 				#restart pixel counter to i = 0
	jr $ra					#return to linked address
