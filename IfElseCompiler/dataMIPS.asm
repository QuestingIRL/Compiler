.data
newLine: .asciiz "\n"
x:   .word  5
result:   .word  0
result1:   .word  0
msg0: .asciiz "result:"
msg1: .asciiz "This Shouldnt Print"
msg2: .asciiz "Hello"
msg3: .asciiz "Hello World"

.text
# -----------------------

main:
lw $t0, x
li $t1, 0
# --- CONDITION --- #
blt $t0, $t1, false0
lw $a0, x
li $a1, 5
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
# --- JUMP PAST ELSE --- #
beq $0, $0, jumpElse0

# --- ELSE STMT --- #
false0:
li $v0, 4
la $a0, msg1
syscall
# --- PAST ELSE --->
jumpElse0:
lw $t0, x
li $t1, 0
# --- CONDITION --- #
bgt $t0, $t1, false1
li $v0, 4
la $a0, msg2
syscall
# --- JUMP PAST ELSE --- #
beq $0, $0, jumpElse1

# --- ELSE STMT --- #
false1:
# PRINTING NEW LINE ---->
li $v0, 4
la $a0, newLine
syscall
li $v0, 4
la $a0, msg3
syscall
# --- PAST ELSE --->
jumpElse1:
# -----------------
# Done, terminate program.

li $v0,10   # call code for terminate
syscall      # system call (terminate)
.end main


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


