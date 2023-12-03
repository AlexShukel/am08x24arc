#include "instruction.h"

namespace comp {
    bool Instruction::is_require_argument() const {
        return requireArgument;
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