.data
newLine: .asciiz "\n"
x:   .word  20
z:   .word  1
t:   .word  3
test:   .word  3
product:   .word  NULL
result:   .word  0
msg0: .asciiz "x: "
msg1: .asciiz "test: "
result2:   .word  NULL
result1:   .word  0
msg2: .asciiz "result:"
msg3: .asciiz "result2:"

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


multiplyValue:
la $t0, product #get address
move $t1, $s1 #new value
sw $t1 0($t0) #save new value
lw $v1, product
jr $ra
.end multiplyValue


addValue:
move $t0, $a0
move $t1, $a1
add $s1, $t0, $t1
la $t0, result #get address
move $t1, $s1 #new value
sw $t1 0($t0) #save new value
lw $v1, result
jr $ra
.end addValue


