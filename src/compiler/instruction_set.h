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
            InstructionSet() {

            }

            template<class... Args>
            InstructionSet(Args... args) {
                (instructions.insert((std::forward<Args>(args))), ...);
            }

            template<class... Args>
            void add_all(Args... args) {
                (instructions.insert((std::forward<Args>(args))), ...);
            }

            Instruction find(const string& keyword) const {
                auto res = std::find_if(instructions.begin(), instructions.end(), [&](const Instruction& inst) {
                    return inst.keyword == keyword;
                });

                if(res == instructions.end()) {
                    const auto message = "Could not find instruction '" + keyword + "'";
                    throw std::exception(message.c_str());
                }

                return *res;
            }
        };
}