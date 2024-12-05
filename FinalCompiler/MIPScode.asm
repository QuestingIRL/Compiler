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
# --- JUMP PAST ELSE --- #
beq $0, $0, jumpElse0

# --- ELSE STMT --- #
false0:
li $v0, 4
la $a0, msg1
syscall
# ---PAST ELSE--->
jumpElse0:
# -----------------
#  Done, terminate program.

li $v0,10   # call code for terminate
syscall      # system call (terminate)
.end main
