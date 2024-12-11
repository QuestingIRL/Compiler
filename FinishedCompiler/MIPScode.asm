.text
# -----------------------

main:
lw $t0, x
li $t1, 10
blt $t1, $t0, while0
# -----------------
# Done, terminate program.

li $v0,10   # call code for terminate
syscall      # system call (terminate)
.end main
