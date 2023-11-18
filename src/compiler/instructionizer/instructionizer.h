#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <bitset>
#include <unordered_map>

#include "text_processor.h"

#include "instruction_list.h"
#include "instruction_set.h"
#include "number_formats.h"
#include "tokenizer/token.h"

namespace comp {
    using namespace std;

    class Instructionizer : public TextProcessor {
        private:
            InstructionSet instuctions;
            unordered_map<string, word> labels;

        public:
            Instructionizer(const InstructionSet& instuctions)
                : instuctions(instuctions) {

            }

            InstructionList tokenize(vector<Token> tokens);

            word get_label_value(string label) const;
            vector<Token> register_labels(vector<Token> tokens);

            void clear_labels();
    };
}