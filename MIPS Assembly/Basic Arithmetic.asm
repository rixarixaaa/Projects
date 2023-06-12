.data
	a: .word 0
	b: .word 0
	c: .word 0
	ans1: .word 0
	ans2: .word 0
	ans3: .word 0
	userName: .space 20
	namePrompt: .asciiz "Give me your name: "
	intPrompt: .asciiz "Please enter an integer between 1 and 100: "
	resMsg: .asciiz "Your results are: "
	
.text
main:
	#output namePrompt
	li $v0, 4
	la $a0, namePrompt
	syscall
	
	#input name from console
	li $v0, 8
	li $a1, 20
	la $a0, userName
	syscall
	
	#output intPrompt for a
	li $v0, 4
	la $a0, intPrompt
	syscall
	
	#input a from console
	li $v0, 5
	syscall
	sw $v0, a 

	#output intPrompt for b
	li $v0, 4
	la $a0, intPrompt
	syscall
	
	#input b from console
	li $v0, 5
	syscall
	sw $v0, b
	
	#output intPrompt for c
	li $v0, 4
	la $a0, intPrompt
	syscall
	
	#input c from console
	li $v0, 5
	syscall
	sw $v0, c
	
	#calculate ans1 = 2a - c + 4 and store it in ans1
	lw $t1, a
	add $t0, $t1, $t1 # 2a, or a + a
	
	lw $t2, c
	sub $t0, $t0, $t2 # 2a - c
	
	addi $t0, $t0, 4 # 2a - c + 4
	sw $t0, ans1 # store to ans1
	
	#calculate ans2 = b - c + (a - 2)
	subi $t4, $t1, 2 # a - 2
	
	lw $t3, b
	sub $t0, $t3, $t2 # b - c
	
	add $t0, $t0, $t4 # b - c + (a - 2)
	sw $t0, ans2 # store to ans2
	
	#calculate ans3 = (a + 3) - (b - 1) + (c + 3)
	addi $t4, $t1, 3 # a + 3
	subi $t5, $t3, 1 # b - 1
	addi $t6, $t2, 3 # c + 3
	
	sub $t0, $t4, $t5 # (a + 3) - (b - 1)
	add $t0, $t0, $t6 # (a + 3) - (b - 1) + (c + 3)
	sw $t0, ans3 #store to ans3
	
	#Print userName
	li $v0, 4
	la $a0, userName
	syscall
	
	#Print resMsg
	li $v0, 4
	la $a0, resMsg
	syscall
	
	#Print ans1
	li $v0, 1
	lw $a0, ans1
	syscall
	
	#Print space
	li $v0, 11
	li $a0, 32
	syscall 
	
	#Print ans2
	li $v0, 1
	lw $a0, ans2
	syscall
	
	#Print space
	li $v0, 11
	li $a0, 32
	syscall

	#Print ans3
	li $v0, 1
	lw $a0, ans3
	syscall
		
exit:
	li $v0, 10
	syscall

# 1st test
	# a = 50, b = 60, c = 70
	# ans1 = 34, ans2 = 38, ans3 = 67
#2nd test
	# a = 4, b = 5, c = 7
	# ans1 = 3, ans2 = 0, ans3 = 13
