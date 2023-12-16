#pragma once

#include <set>
#include <exception>
#include <iostream>

#include "instruction.h"

namespace comp {
    using namespace std;

    class InstructionSet {
        private:
            set<Instruction> instructions;

        public:
            template<class... Args>
            InstructionSet(Args... args) {
                (instructions.insert((std::forward<Args>(args))), ...);
            }

            template<class... Args>
            void add_all(Args... args) {
                (instructions.insert((std::forward<Args>(args))), ...);
            }

            Instruction find(const string& keyword) const;
        };
}