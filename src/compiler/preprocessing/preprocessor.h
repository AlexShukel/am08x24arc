#pragma once

#include <string>
#include <iostream>

#include "macro.h"
#include "../text_processor.h"

namespace comp {
    using namespace std;

    class Preprocessor : public TextProcessor {
        private:
            vector<Macro> macros;

            static string replace_sub_str(string str,const string &subStr,const string &replacement);

        public:
            static pair<string, vector<string>> extract_args_from_index(const string& text, size_t index);

            void add_macro(const Macro& macro);

            pair<string, bool> comment_pass(string text) const;
            pair<string, bool> macro_pass(const string& text);
            pair<string, bool> label_pass(string text) const;
    };
}