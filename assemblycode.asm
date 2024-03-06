addi x8, x0, 3
add x9, x0, x8 
addi x10, x0, 0 
jal x0, EXIT
case2:
add x10, x10, x7
lw x11, 0(x10)
EXIT:
