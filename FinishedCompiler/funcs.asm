
addValue:
move $t0, $a0
move $t1, $a1
add $s1, $t0, $t1
la $t0, result # Get address of variable
move $t1, $s1 # Load new value into $t1
sw $t1, 0($t0) # Store new value at the address
lw $v1, result
jr $ra
.end addValue

# --- CONDITION --- #

while0:
lw $a0, x
li $a1, 1
jal  addValue
la $t0, result1 # Get address of variable
move $t1, $v1 # Load new value into $t1
sw $t1, 0($t0) # Store new value at the address
li $v0, 4
la $a0, msg0
syscall
# Printing -----------
li $v0, 1
lw $a0, result1
syscall
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
lw $t0, x
li $t1, 1
sub $s1, $t0, $t1
la $t0, x # Get address of variable
move $t1, $s1 # Load new value into $t1
sw $t1, 0($t0) # Store new value at the address
li $v0, 4
la $a0, msg1
syscall
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
lw $t0, x
li $t1, 10
blt $t1, $t0, while0
.end while0
