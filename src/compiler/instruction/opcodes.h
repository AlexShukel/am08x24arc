#pragma once

#include "common/types.h"
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
    DEFINE_INSTRUCTION          (PUSH, 0x40)
    DEFINE_24BIT_INSTRUCTION    (POP, 0x80, 0x8000);
    DEFINE_24BIT_INSTRUCTION    (DUP, 0xC5, 0x0000);
    DEFINE_24BIT_INSTRUCTION    (SWAP,0x80, 0x4000)

    /* MEMORY */
    DEFINE_24BIT_INSTRUCTION    (STORE, 0x87, 0x0400);
    DEFINE_24BIT_INSTRUCTION    (LOAD, 0xC1, 0x0400);
    DEFINE_INSTRUCTION          (DEVICE, 0x20)

    /* ARITHMETIC */
    DEFINE_24BIT_INSTRUCTION    (ADD, 0xc2, 0x0000)
    DEFINE_24BIT_INSTRUCTION    (SUB, 0xc2, 0x0001)
    DEFINE_24BIT_INSTRUCTION    (CMP, 0xc2, 0x0002)
    DEFINE_24BIT_INSTRUCTION    (NEG, 0xc2, 0x0003)
    DEFINE_24BIT_INSTRUCTION    (NOT, 0xc2, 0x0004)
    DEFINE_24BIT_INSTRUCTION    (AND, 0xc2, 0x0005)
    DEFINE_24BIT_INSTRUCTION    (OR,  0xc2, 0x0006)
    DEFINE_24BIT_INSTRUCTION    (NAND,0xc2, 0x0007)
    DEFINE_24BIT_INSTRUCTION    (NOR, 0xc2, 0x0008)
    DEFINE_24BIT_INSTRUCTION    (XOR, 0xc2, 0x0009)

    /* FLOW */
    DEFINE_INSTRUCTION          (JMPA, 0x08)
    DEFINE_24BIT_INSTRUCTION    (JMPT, 0x8e, 0x3800)
    DEFINE_24BIT_INSTRUCTION    (JZ, 0x8e, 0x2000)
    DEFINE_24BIT_INSTRUCTION    (JNZ, 0x8e, 0x1800)
    DEFINE_24BIT_INSTRUCTION    (JNEG, 0x8e, 0x1000)
    DEFINE_24BIT_INSTRUCTION    (JPOS, 0x8e, 0x0800)

    // Cool idea, but will not work
    // DEFINE_24BIT_INSTRUCTION    (JMPTC, 0x8e, 0xb800)
    // DEFINE_24BIT_INSTRUCTION    (JZC, 0x8e, 0xa000)
    // DEFINE_24BIT_INSTRUCTION    (JNZC, 0x8e, 0x9800)
    // DEFINE_24BIT_INSTRUCTION    (JNEGC, 0x8e, 0x9000)
    // DEFINE_24BIT_INSTRUCTION    (JPOSC, 0x8e, 0x8800)

    DEFINE_24BIT_INSTRUCTION    (WAIT, 0x80, 0x0000)
    DEFINE_24BIT_INSTRUCTION    (PUSHPC, 0xc3, 0x0000)

    /* Device */
    DEFINE_24BIT_INSTRUCTION    (HALT, 0x00, 0x0000);

    const static InstructionSet DEFAULT_INSTRUCTION_SET(
            /* STACK */
            PUSH(0),
            POP(),
            DUP(),
            SWAP(),

            /* MEMORY */
            STORE(),
            LOAD(),
            DEVICE(0),

            /* ARITHMETIC */
            ADD(),
            SUB(),
            CMP(),
            NEG(),
            NOT(),
            AND(),
            OR(),
            NAND(),
            NOR(),
            XOR(),

            /* FLOW */
            JMPA(0),
            JMPT(),
            JZ(),
            JNZ(),
            JNEG(),
            JPOS(),

            // JMPTC(),
            // JZC(),
            // JNZC(),
            // JNEGC(),
            // JPOSC(),

            WAIT(),
            PUSHPC(),

            HALT()
    );
}
