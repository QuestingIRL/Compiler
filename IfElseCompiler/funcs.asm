
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

