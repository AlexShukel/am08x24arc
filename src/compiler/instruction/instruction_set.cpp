#include "instruction_set.h"

namespace comp {
    Instruction InstructionSet::find(const string& keyword) const {
        auto res = std::find_if(instructions.begin(), instructions.end(), [&](const Instruction& inst) {
            return inst.keyword == keyword;
        });

        if(res == instructions.end())
            throw runtime_error("Could not find instruction '" + keyword + "'");

        return *res;
    }
}