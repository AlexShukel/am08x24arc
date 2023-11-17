#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <bitset>

#include "text_processor.h"

#include "instruction_list.h"
#include "instruction_set.h"
#include "number_formats.h"

namespace comp {
    using namespace std;

    class Tokenizer : public TextProcessor {
        private:
            static string to_upper_case(string str);
            static word parse_16bit_numeric(string arg);
            static string remove_prefix(string number);

        public:
            InstructionList tokenize(const InstructionSet& instuctions, const string& text);
    };
}