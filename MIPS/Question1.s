# Achieve the sum from 0 to n (n is non-negative), n is read by input

      .data
msg:  .asciiz "Please enter a non-negative number: "
err:  .asciiz "Input error.\n"
lies: .asciiz "\n"
      .text
	  .globl main
main:                        # Finishing the initial parts for the program
      la $a0, msg
	  
	  li $v0, 4              # offering the prompt information in the screen
	  
	  syscall
	  
      li $v0, 5              # select the functionality of inputting an integer by setting value 5 in v0, which is inputting a integer

	  syscall                # input n stored in v0
	  
	  blt $v0,$zero,prpt
	  
      move $s0, $zero
	  
	  move $t0, $zero
	  
	  j loop                 # jump to the loop

prpt:
      la $a0, err            # prepare the error message
	  
	  li $v0, 4              # offering the error message in the screen
	  
	  syscall
	 	 
	  j main                 # back to have another input until n is non-negative

loop:                        # Finishing the aim of this program
							 
      add $s0, $s0, $t0      # store the sum in a0, each time the program is doing the loop, add different value
	                         # in $a0, when it ends, value in $a0 is the sum from 1 to n.
 
	  beq $t0, $v0, outp     # The condition for detemining if the calculation ends, 
	                         # when counter and value equals v0, definitely, its the end so program goes to output 

	  addi $t0, $t0, 1       # Each time after the adding, the counter and the value should add one until it 
	                         # reached n
							 
	  j loop	             # Keeping doing loop until the out condition is satisfied

outp:                        # Finishing the output and exit parts for the program
 
      move $a0, $s0          # Because of the sum stored in the a0, the program can directly doint the output process
 
      li $v0, 1              # select the functionality of outputting an integer by setting value 1 in v0
	  
	  syscall                # output the sum from 1 to n
	 
      la $a0, lies

	  li $v0, 4              # have a line change to have a good user experience in next testing example
	  
      syscall
	  
	  li $v0, 10             # select the functionality of exiting the program by setting value 1 in v0
	  
	  syscall                # exit