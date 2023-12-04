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
    DEFINE_INSTRUCTION            (STOREAC, 0x09); // Experimental
    DEFINE_INSTRUCTION            (STOREAA, 0x0A);
    DEFINE_ARGLESS_INSTRUCTION    (LOAD,    0x0B);
    DEFINE_INSTRUCTION            (LOADA,   0x0C);

    DEFINE_ARGLESS_INSTRUCTION    (ADD,     0x0D);
    DEFINE_ARGLESS_INSTRUCTION    (ADDC,    0x0E); // Experimental
    DEFINE_INSTRUCTION            (ADDAT,   0x0F); // Experimental
    DEFINE_INSTRUCTION            (ADDAN,   0x10); // Experimental
    DEFINE_ARGLESS_INSTRUCTION    (SUB,     0x11);
    DEFINE_ARGLESS_INSTRUCTION    (CMP,     0x12);
    DEFINE_ARGLESS_INSTRUCTION    (NEG,     0x13);
    DEFINE_ARGLESS_INSTRUCTION    (NOT,     0x14);
    DEFINE_ARGLESS_INSTRUCTION    (AND,     0x15);
    DEFINE_ARGLESS_INSTRUCTION    (OR,      0x16);
    DEFINE_ARGLESS_INSTRUCTION    (NAND,    0x17);
    DEFINE_ARGLESS_INSTRUCTION    (NOR,     0x18);
    DEFINE_ARGLESS_INSTRUCTION    (XOR,     0x19);

    DEFINE_INSTRUCTION            (JMPA,    0x1A);
    DEFINE_ARGLESS_INSTRUCTION    (JMP,     0x1B);
    DEFINE_INSTRUCTION            (JZA,     0x1C);
    DEFINE_ARGLESS_INSTRUCTION    (JZ,      0x1D);
    DEFINE_INSTRUCTION            (JEA,     0x1E);
    DEFINE_INSTRUCTION            (JEAC,    0x1F); // Experimental
    DEFINE_INSTRUCTION            (JNZA,    0x20);
    DEFINE_ARGLESS_INSTRUCTION    (JNZ,     0x21);
    DEFINE_INSTRUCTION            (JNEA,    0x22);
    DEFINE_INSTRUCTION            (JNEGA,   0x23);
    DEFINE_ARGLESS_INSTRUCTION    (JNEG,    0x24);
    DEFINE_INSTRUCTION            (JPOSA,   0x25);
    DEFINE_ARGLESS_INSTRUCTION    (JPOS,    0x26);

    DEFINE_INSTRUCTION            (DEVICE,  0x28);
    DEFINE_ARGLESS_INSTRUCTION    (DEVICET, 0x29);

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
            STOREAC(0),
            STOREAA(0),
            LOAD(),
            LOADA(0),

            ADD(),
            ADDC(),
            ADDAT(0),
            ADDAN(0),
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
            JEA(0),
            JEAC(0),
            JNZA(0),
            JNZ(),
            JNEA(0),
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
