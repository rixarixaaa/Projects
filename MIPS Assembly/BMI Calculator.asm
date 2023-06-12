.data
	height: .word 0
	weight: .word 0
	bmi: .float 0
	undBmi: .float 18.5
	norBmi: .float 25
	oveBmi: .float 30
	name: .space 20
	namePrompt: .asciiz "What is your name? "
	heightPrompt: .asciiz "Enter your height in inches: "
	weightPrompt: .asciiz "Enter your weight in pounds (round to a whole number): "
	bmiOutput: .asciiz "Your bmi is: "
	underOutput: .asciiz "\nThis is considered underweight."
	norOutput: .asciiz "\nThis is a normal weight."
	overOutput: .asciiz "\nThis is considered overweight."
	obeseOutput: .asciiz "\nThis is considered obese."
.text
main:
	#output namePrompt
	li $v0, 4
	la $a0, namePrompt
	syscall
	
	#user input name
	li $v0, 8
	li $a1, 20
	la $a0, name
	syscall
	
	#output heightPrompt
	li $v0, 4
	la $a0, heightPrompt
	syscall
	
	#user input height
	li $v0, 5
	syscall
	sw $v0, height
	
	#output weightPrompt
	li $v0, 4
	la $a0, weightPrompt
	syscall
	
	#user input weight
	li $v0, 5
	syscall
	sw $v0, weight
	
	lw $t1, weight
	lw $t2, height
	li $t3, 703

	#adjust height and weight for equation
	mul $t1, $t1, $t3 #weight *= 703, store in weight
	sw $t1, weight
	mul $t2, $t2, $t2 #height *= height, store in height
	sw $t2, height
	
	#static cast weight to double
	lw $t0, weight
	mtc1 $t0, $f4
	cvt.s.w $f4, $f4
	
	#static case height to double
	lw $t1, height
	mtc1 $t1, $f6
	cvt.s.w $f6, $f6
	
	#calculate bmi
	div.s $f4, $f4, $f6 # weight = weight / height
	swc1 $f4, bmi
	
	#output name
	li $v0, 4
	la $a0, name
	syscall
	
	#output bmiOutput
	li $v0, 4
	la $a0, bmiOutput
	syscall
	
	#output bmi
	li $v0, 2
	lwc1 $f12, bmi
	syscall
	
	lwc1 $f1, bmi
	lwc1 $f3, undBmi
	lwc1 $f5, norBmi
	lwc1 $f7, oveBmi
	#Output bmi status
	c.lt.s $f1, $f3 #check if bmi < undBmi
	bc1t underMessage
	
	c.lt.s $f1, $f5 #check if bmi < norBmi
	bc1t normalMessage
	
	c.lt.s $f1, $f7 #check if bmi < oveBmi
	bc1t overMessage
	
	li $v0, 4 #Print obese message if conditions aren't branched
	la $a0, obeseOutput
	syscall
	
exit:
	li $v0, 10
	syscall
	
underMessage:
	li $v0, 4
	la $a0, underOutput
	syscall
	j exit
	
normalMessage:
	li $v0, 4
	la $a0, norOutput
	syscall
	j exit
	
overMessage:
	li $v0, 4
	la $a0, overOutput
	syscall
	j exit

obeseMessage:
	li $v0, 4
	la $a0, obeseOutput
	syscall
	j exit