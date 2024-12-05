.text
# -----------------------

main:
lw $a0, x
li $a1, 5
jal  addValue
la $t0, result1 #get address
move $t1, $v1 #new value
sw $t1 0($t0) #save new value
li $v0, 4
la $a0, msg0
syscall
# Printing -----------
li $v0, 1
lw $a0, result1
syscall
# -----------------
#  Done, terminate program.

li $v0,10   # call code for terminate
syscall      # system call (terminate)
.end main
