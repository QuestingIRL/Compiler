.text
# -----------------------

main:
li $v0, 4
la $a0, msg0
syscall
# Printing identifier -----------
li $v0, 1
lw $a0, x
syscall
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
li $v0, 4
la $a0, msg1
syscall
# Printing identifier -----------
li $v0, 1
lw $a0, test
syscall
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
lw $a0, x
li $a1, 0
jal  multiplyValue
la $t0, result2 #get address
move $t1, $v1 #new value
sw $t1 0($t0) #save new value
lw $a0, x
li $a1, 5
jal  addValue
la $t0, result1 #get address
move $t1, $v1 #new value
sw $t1 0($t0) #save new value
li $v0, 4
la $a0, msg2
syscall
# Printing identifier -----------
li $v0, 1
lw $a0, result1
syscall
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
li $v0, 4
la $a0, msg3
syscall
# Printing identifier -----------
li $v0, 1
lw $a0, result2
syscall
# -----------------
#  Done, terminate program.

li $v0,10   # System call for program termination
syscall
.end main
