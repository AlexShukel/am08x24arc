#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <bitset>

#include "instruction_list.h"
#include "instruction_set.h"
#include "number_formats.h"

namespace comp {
    class TextProcessor {
        protected:
            static vector<string> explode(const string& str, set<char, less<char>, allocator<char>> ch);
            static word parse_16bit_numeric(string arg);
            static string to_upper_case(string str);
            static string remove_prefix(string number);

    };
}