# Assembly To Machine Code 
A C++ program which can convert a RISC – V assembly code to its corresponding Machine Code along with Data Memory. Here is the link for RISC – V simulator https://venus.cs61c.org/ . All conversion is based on formats present in RISC – V Reference Sheet available in Project.
# Support 
Project currently supports below mentioned instructions: <br>
R format - add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem <br>
I format - addi, andi, ori, lb, ld, lh, lw, jalr <br>
S format - sb, sw, sd, sh <br>
SB format - beq, bne, bge, blt <br>
U format - auipc, lui <br>
UJ format - jal <br>
# Built With / Concept Used
C++ <br>
RISC-V (32 bit architecture) <br>

# How To Run Code
 Type following <br>
-> Place the code to translate in assemblycode.asm File <br>
-> Compile main.cpp <br>
-> Output will be produced in machinecode.mc File <br>
-> machinecode.mc has Machine Code in Hexadecimal Form with Program Counter followed by Data Memory Part. <br>

# Built By
-> Hartik Arora <br>
-> Sneha Sahu <br>
