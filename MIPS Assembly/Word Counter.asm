.data
	intPrompt: .asciiz "Enter text: "
	wordOutput: .asciiz " words "
	charOutput: .asciiz " characters \n"
	gbyeString: .asciiz "Goodbye!"
	dialogSpace: .asciiz " "
	txtStore: .space 50	
	wordCount: .word 0
	charCount: .word 0
		
.text
main:
loop:
	#output intPrompt and input string from console
	li $v0, 54
	la $a0, intPrompt
	#store user input into txtStore
	la $a1, txtStore
	li $a2, 50
	syscall

	#condition: user inputs blank string
	bnez $a1, exit
	
	#go to the function to count words and characters
	jal countCharWord
	
	#store the character and word returns of the function
	sw $v0, charCount
	sw $v1, wordCount
	
	#output txtStore
	li $v0, 4
	la $a0, txtStore
	syscall
	
	#output wordCount
	li $v0, 1
	lw $a0, wordCount
	syscall
	#output wordOutput
	li $v0, 4
	la $a0, wordOutput
	syscall
	
	#output charCount
	li $v0, 1
	lw $a0, charCount
	syscall
	#output charOutput
	li $v0, 4
	la $a0, charOutput
	syscall
	
	#repeat until user is done
	j loop	
	
countCharWord:
	#push on the stack for the word and character counts
	addi $sp, $sp, -8
	sw $s1, 4($sp)
	sw $ra, 0($sp)
	
	la $t0, txtStore #load the user string
	li $t1, 0 #character incrementer
	li $t2, 0 #word incrementer
	
counter:
	#point to sentence address and go through characters
	lb $t3, ($t0)
	beqz $t3, done #if end of string, pop the stack and return to PC
	beq $t3, ' ', wordInc #compare if character is a space
	addi $t1, $t1, 1 #increase character increment
	addi $t0, $t0, 1 #increase character index
	j counter
	
wordInc:
	#increment word count by 1 if it's a space
	addi $t2, $t2, 1 #increase word increment
	addi $t1, $t1, 1 #increase character increment
	addi $t0, $t0, 1 #increase character index
	j counter

done:
	addi $t2, $t2, 1 #add +1 to words to account for spaces
	addi $t1, $t1, -1 #fix the character count
	
	move $v0, $t1 #store character count into return value
	move $v1, $t2 #store word count into character value
	
	#restore stack, pop the stack
	lw $s1, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	
	#return to original address in loop
	jr $ra
	
exit:
	#output gbyeString
	li $v0, 59
	la $a0, gbyeString
	la $a1, dialogSpace
	syscall
	
	li $v0, 10
	syscall
	

