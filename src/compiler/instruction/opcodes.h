#pragma once

#include "common/types.h"
#include "instruction.h"

#include "instruction_set.h"

#define DEFINE_INSTRUCTION(OP_NAME, OP_OPCODE)                                                                      \
    struct OP_NAME : Instruction {                                                                                  \
        explicit OP_NAME(const word& value) : Instruction{std::string(#OP_NAME), {OP_OPCODE}, {value}, true} {}     \
    };                                                                                                              \

#define DEFINE_ARGLESS_INSTRUCTION(OP_NAME, OP_OPCODE)                                                   \
    struct OP_NAME : Instruction {                                                                                  \
        explicit OP_NAME() : Instruction{std::string(#OP_NAME), {OP_OPCODE}, {0}, false} {}               \
    };                                                                                                              \

namespace comp {
    // CPU

    DEFINE_ARGLESS_INSTRUCTION    (HALT,  0x00);

    // STACK
    DEFINE_INSTRUCTION            (PUSH,    0x01);
    DEFINE_ARGLESS_INSTRUCTION    (PUSHPC,  0x02);
    DEFINE_ARGLESS_INSTRUCTION    (DROP,    0x03);
    DEFINE_ARGLESS_INSTRUCTION    (DUPT,    0x04);
    DEFINE_ARGLESS_INSTRUCTION    (DUPN,    0x05);
    DEFINE_ARGLESS_INSTRUCTION    (SWAP,    0x06);

    DEFINE_ARGLESS_INSTRUCTION    (STORE,   0x07);
    DEFINE_INSTRUCTION            (STOREA,  0x08);
    DEFINE_INSTRUCTION            (STOREAA, 0x09);
    DEFINE_ARGLESS_INSTRUCTION    (LOAD,    0x0a);
    DEFINE_INSTRUCTION            (LOADA,   0x0b);

    DEFINE_ARGLESS_INSTRUCTION    (ADD,     0x0C);
    DEFINE_ARGLESS_INSTRUCTION    (SUB,     0x0D);
    DEFINE_ARGLESS_INSTRUCTION    (CMP,     0x0E);
    DEFINE_ARGLESS_INSTRUCTION    (NEG,     0x0F);
    DEFINE_ARGLESS_INSTRUCTION    (NOT,     0x10);
    DEFINE_ARGLESS_INSTRUCTION    (AND,     0x11);
    DEFINE_ARGLESS_INSTRUCTION    (OR,      0x12);
    DEFINE_ARGLESS_INSTRUCTION    (NAND,    0x13);
    DEFINE_ARGLESS_INSTRUCTION    (NOR,     0x14);
    DEFINE_ARGLESS_INSTRUCTION    (XOR,     0x15);

    DEFINE_INSTRUCTION            (JMPA,    0x16);
    DEFINE_ARGLESS_INSTRUCTION    (JMP,     0x17);
    DEFINE_INSTRUCTION            (JZA,     0x18);
    DEFINE_ARGLESS_INSTRUCTION    (JZ,      0x19);
    DEFINE_INSTRUCTION            (JNZA,    0x1A);
    DEFINE_ARGLESS_INSTRUCTION    (JNZ,     0x1B);
    DEFINE_INSTRUCTION            (JNEGA,   0x1C);
    DEFINE_ARGLESS_INSTRUCTION    (JNEG,    0x1D);
    DEFINE_INSTRUCTION            (JPOSA,   0x1E);
    DEFINE_ARGLESS_INSTRUCTION    (JPOS,    0x1F);

    DEFINE_INSTRUCTION            (DEVICE,  0x21);
    DEFINE_ARGLESS_INSTRUCTION    (DEVICET, 0x22);

    /*
    // STACK
    DEFINE_INSTRUCTION            (PUSH, 0x40)
    DEFINE_ARGLESS_INSTRUCTION    (POP, 0x80, 0x8000);
    DEFINE_ARGLESS_INSTRUCTION    (DUP, 0xC5, 0x0000);
    DEFINE_ARGLESS_INSTRUCTION    (SWAP,0x80, 0x4000)

    // MEMORY
    DEFINE_ARGLESS_INSTRUCTION    (STORE, 0x97, 0x0000);
    DEFINE_ARGLESS_INSTRUCTION    (LOAD, 0xD1, 0x0000);
    DEFINE_INSTRUCTION            (DEVICE, 0x20)

    // ARITHMETIC
    DEFINE_ARGLESS_INSTRUCTION    (ADD, 0xc2, 0x0000)
    DEFINE_ARGLESS_INSTRUCTION    (SUB, 0xc2, 0x0001)
    DEFINE_ARGLESS_INSTRUCTION    (CMP, 0xc2, 0x0002)
    DEFINE_ARGLESS_INSTRUCTION    (NEG, 0xc2, 0x0003)
    DEFINE_ARGLESS_INSTRUCTION    (NOT, 0xc2, 0x0004)
    DEFINE_ARGLESS_INSTRUCTION    (AND, 0xc2, 0x0005)
    DEFINE_ARGLESS_INSTRUCTION    (OR,  0xc2, 0x0006)
    DEFINE_ARGLESS_INSTRUCTION    (NAND,0xc2, 0x0007)
    DEFINE_ARGLESS_INSTRUCTION    (NOR, 0xc2, 0x0008)
    DEFINE_ARGLESS_INSTRUCTION    (XOR, 0xc2, 0x0009)

    // FLOW
    DEFINE_INSTRUCTION            (JMPA, 0x08)
    DEFINE_ARGLESS_INSTRUCTION    (JMPT, 0x8e, 0x3800)
    DEFINE_ARGLESS_INSTRUCTION    (JZ, 0x8e, 0x2000)
    DEFINE_ARGLESS_INSTRUCTION    (JNZ, 0x8e, 0x1800)
    DEFINE_ARGLESS_INSTRUCTION    (JNEG, 0x8e, 0x1000)
    DEFINE_ARGLESS_INSTRUCTION    (JPOS, 0x8e, 0x0800)

    DEFINE_ARGLESS_INSTRUCTION    (WAIT, 0x80, 0x0000)
    DEFINE_ARGLESS_INSTRUCTION    (PUSHPC, 0xc3, 0x0000)

    // sDevice
    DEFINE_ARGLESS_INSTRUCTION    (HALT, 0x00, 0x0000);
    */


    const static InstructionSet DEFAULT_INSTRUCTION_SET(
            HALT(),

            PUSH(0),
            PUSHPC(),
            DROP(),
            DUPT(),
            DUPN(),
            SWAP(),

            STORE(),
            STOREA(0),
            STOREAA(0),
            LOAD(),
            LOADA(0),

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

            JMPA(0),
            JMP(),
            JZA(0),
            JZ(),
            JNZA(0),
            JNZ(),
            JNEGA(0),
            JNEG(),
            JPOSA(0),
            JPOS(),

            DEVICE(0),
            DEVICET()
    /*
    // STACK
    PUSH(0),
    POP(),
    DUP(),
    SWAP(),

    // MEMORY
    STORE(),
    LOAD(),
    DEVICE(0),

    // ARITHMETIC
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

    // FLOW
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
    */
    );
}
