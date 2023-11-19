#pragma once

#include <string>

#include "opcode.h"
#include "argument.h"

namespace comp {
    using namespace std;

    struct Instruction {
        string keyword;

        Opcode opcode;
        Argument argument;

        bool is_24bit_instruction() const;
        bool is_halt() const;

        /* Need this for storing in std set*/
        bool operator==(const Instruction& another) const;
        bool operator<(const Instruction& another) const;
        bool operator>(const Instruction& another) const;
    };
}