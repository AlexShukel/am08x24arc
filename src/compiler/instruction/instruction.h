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

        bool requireArgument;

        bool is_require_argument() const;
        bool is_halt() const;

        /* Need this for storing in std set*/
        bool operator==(const Instruction& another) const;
        bool operator<(const Instruction& another) const;
        bool operator>(const Instruction& another) const;
    };
}