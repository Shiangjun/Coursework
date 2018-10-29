# Achieve the equation (x^3)+3*(x^2)*y+3*x*(y^2)+9*(y^3), with the input x,y.
# First, the equation can be transfered into (x^2+3*(y^2))*(x+3*y) [ equation 2 ]

# ANALYSIS FOR ADDING OPERATION OVERFLOW:

# With the process of analysis, the left part is always greater than the right part in equation 2.
# So the overflow condition can be determined, x^2 is greater than or equal to zero, also 3*(y^2) is greater than or equal to zero. Neither are negative.
# So simply use this character to determine if it is an overflow ( a + b = c , a,b are positive but c is negative)
# First, the program calculate the greater elment, for the aim to determine the overflow
# If the greater one isn't an overflow, so the less one isn't an overflow either.

# ANALYSIS FOR MULTIPLICATION OPERATION OVERFLOW:

# Due to the storing room is limited, so the multiplication may cause overflow which is the actual result is more than 16 bits but it can only be stored its last 16 bits.
# So the result is being cut. It's obvious that we use the result of multiplication, and let it be divided by one factor, then determine if it's equal to the other factor.
# If they are equal, then there is no overflow in this process. Or, the multiplication causes an overflow.

       .data
	   
msg:   .asciiz "Overflow error!\n"    # Prepare the error message of overflow. When it's an overflow, the string "Overflow error!" will be displayed
inx:   .asciiz "Please input x: " 	  # Prepare the input prompt
iny:   .asciiz "Please input y: "     # Prepare the input prompt
lies:  .asciiz "\n"
       .text	   
       .globl main                   

main:
       la $a0, inx                    # prepare the user prompt "input the x value"
	   
	   li $v0, 4
	   
	   syscall                        # offering the user prompt in the screen
	        
       li $v0, 5
	   
	   syscall                        # input the value x, storing in v0
	   
	   move $t0, $v0                  # put the x value into the register t0
	   
	   la $a0, iny                    # prepare the user prompt "input the y value"
	   
	   li $v0, 4
	   
	   syscall                        # offering the user prompt in the screen
	   
	   li $v0, 5
	   
	   syscall                        # input the value y, storing in v0
	   
	   move $t1, $v0                  # put the y value into the register t1

	   mul $t3, $t0, $t0              # put the x^2 into the register t3
	   
	   mul $t4, $t1, $t1              # put the y^2 into the register t4
	   
	   mul $t5, $t4, 3                # put the 3*y^2 into the register t5
	   
	   add $s1, $t3, $t5              # calculate x^2 + 3*y^2, and storing into the register s1
	   
	   slt $t6, $s1, 0                # determine that if s1 is less than zero, if it is, then put 1 into the register t6 
	                                  # the methodology has been explained at the beginning of this file
	   beq $t6, 1, fout               # if the register t6 equals 1, then goto fout part(show the overflow error message)
	                                  # when the adding doesn't cause the overflow, doing next steps by continuing 
	   mul $t2, $t1, 3                # put the 3*y into the register t2
	   
	   add $s0, $t0, $t2              # calculate x + 3y, and storing into the register s0
	   
	   mul $a0, $s0, $s1              # calculate (x^2 + 3 * y^2)*(x + 3 * y), and storing into the register a0
	   
	   div $s2,$a0,$s0                # check if the multiplication cause the overflow, by using product to be divided by one factor
	   
	   bne $s2,$s1, fout              # if the result is not equal to the other factor, definitely it's an overflow, then goto fout part(show the overflow error message)
	   
	   j pout                         # if there is no overflow situation, goto pout part(show the final result of final calculation)
	   
fout:
       la $a0, msg                    # prepare the error message

       li $v0, 4                      

       syscall                        # offer the overflow error message in the screen

       li $v0, 10                     

       syscall                        # exit the program

pout:
	   li $v0, 1                      

	   syscall                        # print out the result of calculation
	    
	   la $a0, lies
	   
	   li $v0, 4
	   
	   syscall                        # have a line change to have a good user experience in next testing example

	   li $v0, 10                     

	   syscall                        # exit the program
