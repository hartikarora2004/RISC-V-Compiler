.data
var1: .word 0x10000000
var2: .word 10
.text
auipc x3 0x10000
lw x3 0(x3)
auipc x4 0x10000
lw x4 -4(x4)
addi x1 x1 0


loop: beq x1 x4 next
add x2 x2 x3
sw x1 0(x2)
addi x1 x1 1
jal x0 loop


next:
addi x6 x6 0 #stores sum
addi x1 x0 0
loop1: beq x1 x4 store
add x2 x2 x3
lw x7 0(x2)
add x6 x6 x7
addi x1 x1 1
jal x0 loop1


store:
add x2 x2 x3
sw x6 0(x2)
exit: #FALL_THRU