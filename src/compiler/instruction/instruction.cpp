#include "instruction.h"

namespace comp {
    bool Instruction::is_24bit_instruction() const {
        return (opcode.val & 0b01000000) != 0;
    }

    bool Instruction::is_halt() const {
        return (opcode.val == 0) && (argument.val == 0);
    }

    /* Need this for storing in std set*/
    bool Instruction::operator==(const Instruction& another) const {
        return this->keyword == another.keyword;
    }

    bool Instruction::operator<(const Instruction& another) const {
        return this->keyword < another.keyword;
    }

    bool Instruction::operator>(const Instruction& another) const {
        return this->keyword > another.keyword;
    }
}