#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <bitset>

#include "instruction_list.h"
#include "instruction_set.h"
#include "number_formats.h"

namespace comp {
    using namespace std;

    class Tokenizer {
        private:
            static vector<string> explode(const string& str, const char& ch);
            static string to_upper_case(string str);
            static word parse_16bit_numeric(string arg);
            static string remove_prefix(string number);

        public:
            InstructionList tokenize(const InstructionSet& instuctions, const string& text);
    };
}