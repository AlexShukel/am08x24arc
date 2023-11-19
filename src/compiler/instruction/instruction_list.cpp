#include "instruction_list.h"

namespace comp {
    void InstructionList::add(const Instruction& instruction) {
        instructions.push_back(instruction);
    }

    void InstructionList::add(const string& name, const Opcode& opcode, const Argument& argument) {
        instructions.push_back(Instruction{name, opcode, argument});
    }

    void InstructionList::add(const string& name, const byte& opcode, const word& argument) {
        instructions.push_back(Instruction{name,{opcode}, {argument}});
    }

    void InstructionList::export_to_file(const string& fileName, const ExportFormat& format) const {
        ofstream file(fileName, ios::binary | ios::out);

        if(file.is_open()) {
            if(format == BIN) {
                for(const auto& i : instructions) {
                    file.write((char*) &i.opcode, sizeof(Opcode));
                    file.write((char*) &i.argument, sizeof(Argument));
                }
            } else if(format == LOGISIM) {
                file << "v2.0 raw" << '\n';

                for(const auto& i : instructions) {
                    file << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.opcode.val);
                    file << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(i.argument.val);
                    file << " ";
                }
            }

            file.close();
        } else {
            cout << "Failed to open file " << fileName << endl;
        }
    }
}