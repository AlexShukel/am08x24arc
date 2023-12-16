# am08x24arc

## Stack based architecture

This architecture is based on the stack. All instructions work with the stack. For example, ADD instruction takes 2 arguments from top of the stack and then pushes their sum to the stack.

Instruction set includes 41 operations. You can see all the details in `ISA.xlsx` file.

## Examples
### Fibonacci sequence
Simple program that counts fibonacci numbers.

#### Links:
1. Source code avaiable at [assembly/examples/fibonacci/fibonacci.asm](https://github.com/AlexShukel/am08x24arc/blob/main/assembly/examples/fibonacci/fibonacci.asm)

### Video player
This example uses multiple cores, **cpu** core and one **gpu** core. Cpu is responsible for reading video data from memory, and sending it to **gpu** core, meanwhile **gpu** core recieves video data it renders everything into the led matrix screen.

#### Links:
1. Program demostration [bad apple but played on homebrew stack based CPU architecture](https://youtu.be/f2nn0lIj7cs?si=6s3Qz-TR8DqL9LBK) <br>
2. Source code avaiable at [examples/gfx](https://github.com/AlexShukel/am08x24arc/tree/main/assembly/examples/gfx)

## Assembly
> Todo

## License
am08x24arc is free and open source architecture. All code in this repository is licensed under
- MIT License ([LICENSE.md](https://github.com/AlexShukel/am08x24arc/blob/main/LICENSE.md) or https://opensource.org/license/mit/)