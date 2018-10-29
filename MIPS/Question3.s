# To achieve the functions, we first input a string, then having a char input,
# then doing the loop from the start to the end, once we find a character is the
# same as the input char, we add the counter, until it reaches the end of the string.
# Finally, we output the counter. In addition, if it's zero, we need to output another
# prompt, which is "(Not found)".
    .data  
buf: .space 1024 
inst:.asciiz "Please input a string:"           
inch:.asciiz "Please input a character:"        # prepare user prompt
lies:.asciiz "\n"
nfid:.asciiz "(Not found)"
    .text  
    .globl main  
main:   
    la $a0,inst                                 # prepare the prompt information
	
	li $v0, 4
	
	syscall                                     # show the prompt in the screen
    
	la $a0, buf                                 # load buf address into a0
    
	li $v0, 8                                     
    
	syscall                                     # input the target string
 
	la $a0,inch                                 # prepare the prompt information
	
	li $v0, 4
	
	syscall                                     # show the prompt in the screen
    
	li $v0, 12    
    
	syscall                                     # input a char, and storing in the v0
    
	la $s1, buf                                 # load buf address into s0  
	
	li $s2, 0                                   # set s2 = 0 and use it as a counter

loop_initial:   
	lb $s0, 0($s1)                              # selecting one char from the string which is stored in address s1
    
	sub $t1, $v0, $s0                           # doing the ASCII character calculation to determine if they are the same
	
find_loop:    
    beq $t1, $0, found_count                    # if they are the same, goto found_count to do the counting job
    
	beq $s0, $zero, output                      # if the bit is the end of the string, then goto output
    
	addi $s1, $s1, 1                            # continuing for next bit, prepare by adding one to the address for loading next bit
    
	j loop_initial                              # then continue the loop, starting with the loop_initial

found_count:  
    addi $s2, $s2,1                             # once we found the eqaul one, first adding one into the counter
	
	addi $s1, $s1, 1                            # then, we need to move to next bit, so doing the address adding.
	
	j loop_initial                              # once we finished all the preparation, we can continue the loop, starting with the loop_initial
	 
output:  
    la $a0,lies                                 # prepare a lie change symbol
	
	li $v0, 4
	
	syscall                                     # having a lie change to give a good user experience
	
	move $a0,$s2                                # put the counter's value into a0, ready to output
    
	li $v0, 1      
     
	syscall                                     # print out the counter's value
	
	bne $s2, $zero , exit                       # determine if the counter is zero, if it's non-zero, goto exit
	
	la $a0,nfid                                 # if it's zero, preapre the "Not found" user prompt
	
	li $v0, 4
    
	syscall                                     # print out the "Not found" for user
	
	j exit                                      # goto exit
	
exit:
	la $a0, lies                                # prepare a lie change symbol
	
	li $v0, 4
	
	syscall                                     # having a lie change to give a good user experience
	
    li $v0, 10    
    
	syscall                                     # exit the program