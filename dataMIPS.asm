.data
newLine: .asciiz "\n"
x:   .word  20
z:   .word  5
t:   .word  3
test:   .word  3
result:   .word  0
result1:   .word  0
msg0: .asciiz "result:"

.text
# -----------------------

main:
# Printing -----------
li $v0, 1
lw $a0, x
syscall
lw $a0, x
li $a1, 5
li $a2, 3
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


