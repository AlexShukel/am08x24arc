#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <bitset>
#include <unordered_map>

#include "../common/text_processor.h"

#include "../instruction/instruction_list.h"
#include "../instruction/instruction_set.h"
#include "../common/number_formats.h"
#include "../tokenizer/tokenizer.h"
#include "../tokenizer/token.h"

namespace comp {
    using namespace std;

    struct AssemblerResult {
        InstructionList instructions;
    };

    class Assembler : public TextProcessor {
        private:
            InstructionSet instuctions;
            unordered_map<string, word> labels;

        public:
            Assembler(const InstructionSet& instuctions);

            InstructionList tokenize(vector<Token> tokens);

            word get_label_value(string label) const;
            vector<Token> register_labels(vector<Token> tokens);

            void clear_labels();
    };
}