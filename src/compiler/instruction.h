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

        bool is_24bit_instruction() const {
            return (opcode.val & 0b01000000) != 0;
        }

        /* Need this for storing in std set*/
        bool operator==(const Instruction& another) const {
            return this->keyword == another.keyword;
        }

        bool operator<(const Instruction& another) const {
            return this->keyword < another.keyword;
        }

        bool operator>(const Instruction& another) const {
            return this->keyword > another.keyword;
        }
    };
}