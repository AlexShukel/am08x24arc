#pragma once

#include <string>
#include <iostream>

#include "macro.h"
#include "scope.h"

#include "../text_processor.h"

namespace comp {
    using namespace std;

    class Preprocessor : public TextProcessor {
        private:
            vector<Macro> macros;
            vector<Scope> scopes;

            static string replace_sub_str(string str,const string &subStr,const string &replacement);

            pair<bool, Scope> is_begin_scope(const byte& ch) const;
            pair<bool, Scope> is_end_scope(const byte& ch) const;

            static vector<Scope> get_default_scopes();

        public:
            pair<string, vector<string>> extract_args_from_index(const string& text, size_t index) const;
            pair<int, string> extract_arg_substring(const string& text, size_t index) const;

            void add_macro(const Macro& macro);

            void declare_default_macros();
            void declare_default_scopes();

            pair<string, bool> comment_pass(string text) const;
            pair<string, bool> macro_pass(const string& text);
    };
}