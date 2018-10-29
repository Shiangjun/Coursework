# To achieve palindrome determination, we put two pointers, one of them is from the start, the other
# is from the end. Each time they both load a byte, and check if they are numbers or letters. Particularly,
# if the byte stores a uppercase letter, use the ASCII character rule to transfer it into lowercase letter
# by adding 32. If they are not numbers or letters, we just skip them and load the next byte.
# Once these two bytes are different, we just go out and determine it's not a palindrome.
# Til the pointer from the start is greater than the pointer from the end, which means
# the evaluation is over, so the string should be a palindrome.
    .data
strs: .space 1024
ism:  .asciiz "The string is a palindrome.\n"
npm:  .asciiz "The string is not a palindrome.\n"
prp:  .asciiz "Please input a string to determine if it is palindrome:\n"
lie:  .asciiz "\n"                              # prepare user prompt
    .text
    .globl main
main:
    la $a0, prp                                 # prepare the prompt information
	
	li $v0, 4
	
	syscall                                     # show the prompt in the screen
 
    la $a0, strs                                # load strs address into a0

	li $v0, 8

	syscall                                     # input the target string

	la $t1, strs                                # load strs address into t1 

	la $t2, strs                                # load strs address into t2 
	
	li $s0, 47                                  # load immediate in s0, which represents '0'-1
	
	li $s1, 58                                  # load immediate in s0, which represents '9'+1
	
	li $s2, 64                                  # load immediate in s0, which represents 'A'-1
	
	li $s3, 91                                  # load immediate in s0, which represents 'A'+1
	
	li $s4, 96                                  # load immediate in s0, which represents 'a'-1
	
	li $s5, 123                                 # load immediate in s0, which represents 'z'+1

located_final: 
    lb $t3, 0($t2)                              # load a byte from address t2, stored in t3
	
	beqz $t3, determine_loop_initial            # if t3 reaches the end symbol of the string, move to next part

	addu $t2, $t2, 1                            # otherwise, add 1 into t2

	j located_final                             # repeat, until t2 points to the end of the string

determine_loop_initial:
    subu $t2, $t2, 2                            # because the last two characters represents the end, to make sure
	                                            # t2 points to the last element in the string, so sub t2 by 2
	
	j determine_loop                            # Start the determine_loop, once initialization was finished

determine_loop:
    bge $t1, $t2, ispal                         # if t1 > t2, which means it comes to the end, so the string is palindrome
	                                            # and go to the output part for the situation which the string is palindrome

	j byte_f_in                                 # otherwise, there are still pairs to compare with, move to byte_f_in
	
byte_f_in:
	lb $t3, 0($t1)                              # load a byte into t3 stored in address t1

	slt $t5, $t3, $s1                           # determine if t3 is less than '9'+1, storing the result in t5
	
	slt $t6, $s0, $t3                           # determine if t3 is greater than '0'-1, storing the result in t6                           
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t3 is a number
	
	beq $t7, 1, byte_e_in                       # so we can go on, move to byte_e_in part
	                                            # otherwise, continue to determine if it's a letter
	slt $t5, $t3, $s3                           # determine if t3 is less than 'Z'+1, storing the result in t5 
	
	slt $t6, $s2, $t3                           # determine if t3 is greater than 'A'-1, storing the result in t6 
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t3 is an uppercase letter
	
	beq $t7, 1, up_to_low_f                     # so we can go to the part up_to_low_f
		                                        # otherwise, continue to determine if it's a lowercase letter
	slt $t5, $t3, $s5                           # determine if t3 is less than 'z'+1, storing the result in t5
	
	slt $t6, $s4, $t3                           # determine if t3 is greater than 'a'-1, storing the result in t6
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t3 is a lowercase letter
	
	beq $t7, 1, byte_e_in                       # so we can go on, move to byte_e_in part 
	                                            # otherwise, this byte are neither a letter nor a number
	addi $t1, $t1, 1                            # move the pointer t1 to next byte by adding 1 in t1
	
	j byte_f_in                                 # repeat, until this byte satisfies the condition to be compared with

up_to_low_f:
    addi $t3, $t3, 32                           # transfer it from a lowercase letter to an uppercase letter by adding 32 
	
	j byte_e_in                                 # then goto next part byte_e_in
	
byte_e_in:
	lb $t4, 0($t2)                              # load a byte into t4 stored in address t2

	slt $t5, $t4, $s1                           # determine if t4 is less than '9'+1, storing the result in t5
	
	slt $t6, $s0, $t4                           # determine if t4 is greater than '0'-1, storing the result in t6 
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t4 is a number
	
	beq $t7, 1, loop_compare                    # so we can go on, move to loop_compare
	                                            # otherwise, continue to determine if it's a letter	
	slt $t5, $t4, $s3                           # determine if t4 is less than 'Z'+1, storing the result in t5
	
	slt $t6, $s2, $t4                           # determine if t4 is greater than 'A'-1, storing the result in t6
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t4 is an uppercase letter
	
	beq $t7, 1, up_to_low_e                     # so we can go to the part up_to_low_e
		                                        # otherwise, continue to determine if it's a lowercase letter	
	slt $t5, $t4, $s5                           # determine if t4 is less than 'z'+1, storing the result in t5
	
	slt $t6, $s4, $t4                           # determine if t4 is greater than 'a'-1, storing the result in t6
	
	and $t7, $t5, $t6                           # if both t5 and t6 are true, then the byte stored in t4 is a lowercase letter
	
	beq $t7, 1, loop_compare                    # so we can go on, move to loop_compare part
	                                            # otherwise, this byte are neither a letter nor a number
	sub $t2, $t2, 1                             # move the pointer t2 to next byte by substracting 1 in t2          
	
	j byte_e_in                                 # repeat, until this byte satisfies the condition to be compared with

up_to_low_e:
    addi $t4, $t4, 32                           # transfer it from a lowercase letter to an uppercase letter by adding 32
	
	j loop_compare                              # then goto next part loop_compare
	
loop_compare:
	bne $t3, $t4, notpal                        # if t3 is not equal to t4, then the string is not palindrome
	                                            # go for the output "notpal"
												# otherwise
	addi $t1, $t1, 1                            # move the start pointer to next by adding 1 in t1

	sub $t2, $t2, 1                             # move the final pointer to next by substracting 1 in t2

	j determine_loop                            # repeat, until the start pointer is greater than the end pointer

ispal:
    la $a0, ism                                 # load the address of "ism" in a0

	li $v0, 4

	syscall                                     # print out the message "The string is a palindrome."

	j exit                                      # go to the exit part

notpal:
    la $a0, npm                                 # load the address of "npm" in a0

	li $v0, 4

	syscall                                     # print out the message "The string is not a palindrome."

	j exit                                      # go to the exit part 

exit:
    li $v0, 10 

	syscall                                     # exit the program

