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
                file << "v2.0 raw" << endl;

                for(const auto& i : instructions) {
                    file << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.opcode.val);
                    file << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(i.argument.val);
                    file << " ";
                }
            } else if(format == ASSEMBLY) {
                file << "INSTR    VALUE  |  OPCODE  | ADRESS" << endl;
                file << "----------------+----------+-------" << endl;

                 const auto instructionCount = static_cast<word>(instructions.size());

                 for(word adr = 0; adr < instructionCount; ++adr) {
                     const auto& i = instructions[adr];

                     file << std::setw(8) << std::left << std::setfill(' ') << i.keyword << std::right;

                     if(i.is_require_argument())
                         file << " 0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(i.argument.val);
                     else
                         file << "       ";

                     // Opcode
                     file << " | 0x";
                     file << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i.opcode.val);
                     file << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(i.argument.val);

                     // Adress
                     file << " | 0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(adr);

                     file << endl;

                 }
            }

            file.close();
        } else {
            cout << "Failed to open file " << fileName << endl;
        }
    }
}