# Assembly To Machine Code 
A C++ program which can convert a RISC – V assembly code to its corresponding Machine Code along with Data Memory. Here is the link for RISC – V simulator https://venus.cs61c.org/ . All conversion is based on formats present in RISC – V Reference Sheet available in Project.
# Support 
Project currently supports below mentioned instructions:
R format - add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem
I format - addi, andi, ori, lb, ld, lh, lw, jalr
S format - sb, sw, sd, sh
SB format - beq, bne, bge, blt
U format - auipc, lui
UJ format - jal
# Built With / Concept Used
C++ 
RISC-V (32 bit architecture)

# How To Run Code
 Type following
-> Place the code to translate in assemblycode.asm File
-> Compile main.cpp
-> Output will be produced in machinecode.mc File
-> machinecode.mc has Machine Code in Hexadecimal Form with Program Counter followed by Data Memory Part.

# Built By
-> Hartik Arora
-> Sneha Sahu
