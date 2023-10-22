# OPCODE specification

OPCODE consists of 26 bits. First 16 bits are for operand. Next 6 bits for operation code. Last 4 bits remains for specific needs.

ANY ARG:
the last 2 bits define how to interpret argument:
1) 16 bit number    - 00
2) registry         - 01
3) memory address   - 10

<!-- FIXME: MOV is the only operation that uses all last 4 bits. -->

## MOV - move

2 bits for registry. Using ANY ARG.

## JMP - jump

The argument is interpreted as a 16 bit address where to jump.

## LD - load

Loads value from address specified in argument into registry A.

## ST - store

Stores value from registry A into memory address specified in the argument.

## CMP - compare

Compares value from registry A with ANY ARG. The result is written in ZF and CF flags:
|result | ZF | CF|
|-------|----|---|
|">"    | 0  | 0 |
|"="    | 1  | 0 |
|"<"    | 0  | 1 |

## JG - jump if greater

Jumps to the address specified in the argument if ZF = 0 & CF = 0

## JL - jump if less

Jumps to the address specified in the argument if CF = 1

## JE - jump if equals

Jumps to the address specified in the argument if ZF = 1

## ADD - addition

Adds ANY ARG to registry A.

## ADDC - addition with carry

Adds ANY ARG and CF to registry A.

## SUB - subtraction

Subtracts ANY ARG from registry A.

## SUBB - subtraction with borrow

Subtracts ANY ARG and CF from registry A.

## AND - bitwise &

Calculates bitwise and on the registry A and ANY ARG.

## NAND - bitwise nand

Calculates bitwise nand on the registry A and ANY ARG.

## OR - bitwise |

Calculates bitwise or on the registry A and ANY ARG.

## NOR - bitwise nor

Calculates bitwise nor on the registry A and ANY ARG.

## XOR - bitwise ^

Calculates bitwise xor on the registry A and ANY ARG.

## NEG - bitwise !

Negates bitwise the value in registry A.

## NEGV - negate value

Negates a value in registry A.

<!-- TODO: add shift operations -->

## HALT 111111 - halt

Stop the program
