# MASSEY Machine
***Start:** August 15<sup>th</sup> 2022, **Finish:** September 21<sup>st</sup> 2022*

For a first-year course - Computer Science & Programming.

## Scenario
The program simulates the MASSEY machine (a basic version of a computer; see below for more details). It receives input in the form of a text file consisting of MASSEY machine code instructions (see below for details). It simulates the machine running (works through the machine code instructions) in the correct sequence changing values of registers and memory locations as required. It will display appropriate output such as program counter, instruction register, values of recently changed registers, and values of recently changed memory locations. I have assumed that the text file contains correct machine code instructions, but can still have logic errors (instructions in the incorrect order).

## The MASSEY Machine
### Architecture
**Central Processing Unit**
- Program Counter
- Instruction Register
- 16 registers - size of 16 bits; expressed in hexadecimal (R0, R1, R2... RF) 

**Memory** - 256 locations with size of 16 bits (512 bytes total size); expressed in hexadecimal (00 to FF).

The MASSEY machine can only work with integers.

### Instruction Set
Each instruction consists of 16 bits written as 4 hexadecimal digits. The first digit is the opcode. The other 3 digits are the operands. The list of machine instructions follows:
- **1RXY** - Load register R with the value XY. (Note 2-digit hex limit on number size) *e.g. 1213 means load register R2 with the hexadecimal number 13 (19 in decimal).*
- **20RS** - Load register R with the number in register S. _e.g. 20A7 means load register R10 with the number in register R7._
- **3RXY** - Load register R with the number in the memory location at address XY. _e.g. 34AB means load register R4 with the contents from memory location AB_
- **4RXY** - Store the number in register R in the memory location at address XY. _e.g. 45B1 means store the contents of register R5 in the memory location B1_
- **5RST** - Add the numbers in registers S and T and load the result into register R. (Floating point addition.) _e.g. 534E means add the numbers in R4 and R14 and load the result into R3._
- **6RST** - Add the numbers in registers S and T and load the result into register R. (Integer addition using 2’s complement arithmetic.) _e.g. 6823 means add the contents of R2 and R3 and load the result into R8._
- **70R0** - Negate register R. (Carry out complement and add 1 – in effect, multiply R with -1) _e.g. 70A0 means multiply the number in R10 by -1._
- **8RXY** - Shift the number in register R to the right for XY bits _e.g. 8403 means that the number in R4 must be shifted 3 bits to the right._
- **9RXY** - Shift the number in register R to the left for XY bits _e.g. 9602 means that the number in R6 must be shifted 2 bits to the left._
- **ARST** - AND the numbers in registers S and T and load the result into register R. _e.g. A045 means AND the numbers in R4 and R5 and load the result into R0._
- **BRST** - OR the numbers in registers S and T and load the result into register R. _e.g. BC74 means OR the numbers in R7 and R4 and load the result into R12._
- **CRST** - XOR the numbers in registers S and T and load the result into register R. _e.g. C5F3 means XOR the numbers in R15 and R3 and load the result into R5._
- **DRXY** - Jump to the instruction at address XY if the value in register R is equal to the value in register R0. _e.g. D43C means the following: (a) compare the contents of R4 with R0. (b) if they are equal load 3C into the program counter._
- **E000** - Halt

## Example input
Text file "program1.txt" can have in it:
```
1102
1203
6012
40FF
E000
```
When the program is run:
```
Enter the file name of the MASSEY machine code: program1.txt
Memory[0] = 1102
Memory[1] = 1203
Memory[2] = 6012
Memory[3] = 40FF
Memory[4] = E000
1102 R1 = 0002 PC = 1
1203 R2 = 0003 PC = 2
6012 R0 = 0005 PC = 3
40FF Memory[FF] = 0005 PC = 4
Halt
```

## What I learnt:
- Understand and implement a simple version of a computer in code
- Function declaration and definition
