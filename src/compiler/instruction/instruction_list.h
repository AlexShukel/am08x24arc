#pragma once

#include <vector>
#include <iomanip>
#include <fstream>
#include <iostream>

#include "common/export_format.h"
#include "instruction.h"

namespace comp {
    using namespace std;

    class InstructionList {
        private:
            vector<Instruction> instructions;

        public:
            void add(const Instruction& instruction);
            void add(const string& name, const Opcode& opcode, const Argument& argument);
            void add(const string& name, const byte& opcode, const word& argument);

            template<class... Args>
            void add_all(Args... args) {
                (instructions.push_back((std::forward<Args>(args))), ...);
            }

            void export_to_file(const string& fileName, const ExportFormat& format) const;
        };
}