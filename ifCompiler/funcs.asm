
addValue:
move $t0, $a0
move $t1, $a1
add $s1, $t0, $t1
la $t0, result #get address
move $t1, $s1 #new value
sw $t1 0($t0) #save new value
lw $v1, result
jr  $ra
.end addValue

