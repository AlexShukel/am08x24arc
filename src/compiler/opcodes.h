#pragma once

#include "types.h"
#include "instruction.h"

#include "instruction_set.h"

#define DEFINE_INSTRUCTION(OP_NAME, OP_OPCODE)                                                              \
    struct OP_NAME : Instruction {                                                                          \
        explicit OP_NAME(const word& value) : Instruction{std::string(#OP_NAME), {OP_OPCODE}, {value}} {}   \
    };                                                                                                      \

#define DEFINE_24BIT_INSTRUCTION(OP_NAME, OP_OPCODE, OP_ARGUMENT)                                           \
    struct OP_NAME : Instruction {                                                                          \
        explicit OP_NAME() : Instruction{std::string(#OP_NAME), {OP_OPCODE}, {OP_ARGUMENT}} {}              \
    };                                                                                                      \

namespace comp {
    /* STACK */
    DEFINE_INSTRUCTION          (PUSH, 0x80);
    DEFINE_24BIT_INSTRUCTION    (POP, 0x40, 0x8000);
    DEFINE_24BIT_INSTRUCTION    (DUP, 0xC5, 0x0000);
    // DEFINE_INSTRUCTION       (SWAP, xxxx, xxxx)

    /* MEMORY */
    DEFINE_24BIT_INSTRUCTION    (STORE, 0x66, 0x0000);
    DEFINE_24BIT_INSTRUCTION    (LOAD, 0xe1, 0x0000);

    /* ARITHMETIC */
    DEFINE_24BIT_INSTRUCTION    (ADD, 0xc2, 0x0000);
    DEFINE_24BIT_INSTRUCTION    (SUB, 0xc2, 0x0008);
    // DEFINE_INSTRUCTION       (NEG, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (NOT, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (AND, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (OR, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (NAND, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (NOR, xxxx, xxxx)
    // DEFINE_INSTRUCTION       (XOR, xxxx, xxxx)

    /* FLOW */
    DEFINE_INSTRUCTION          (JMPA, 0x10);
    DEFINE_24BIT_INSTRUCTION    (JMPT, 0x56, 0x7000);
    DEFINE_24BIT_INSTRUCTION    (JZ, 0x56, 0x4000);
    DEFINE_24BIT_INSTRUCTION    (JNZ, 0x56, 0x3000);
    DEFINE_24BIT_INSTRUCTION    (JNEG, 0x56, 0x2000);
    DEFINE_24BIT_INSTRUCTION    (JPOS, 0x56, 0x1000);
    DEFINE_24BIT_INSTRUCTION    (WAIT, 0x40, 0x0000);
    DEFINE_24BIT_INSTRUCTION    (PUSHPC, 0xc4, 0x0000);

    DEFINE_24BIT_INSTRUCTION    (HALT, 0x00, 0x0000);

    const static InstructionSet DEFAULT_INSTRUCTION_SET(
            /* STACK */
            PUSH(0),
            POP(),
            DUP(),
            // SWAP()

            /* MEMORY */
            STORE(),
            LOAD(),

            /* ARITHMETIC */
            ADD(),
            SUB(),
            // NEG()
            // NOT()
            // AND()
            // OR()
            // NAND()
            // NOR()
            // XOR()

            /* FLOW */
            JMPA(0),
            JMPT(),
            JZ(),
            JNZ(),
            JNEG(),
            JPOS(),
            WAIT(),
            PUSHPC(),

            HALT()
    );
}
