#pragma once

#include <string>
#include <iostream>

#include "macro/macro.h"
#include "macro/include_macro.h"
#include "macro/notify_macro.h"
#include "macro/if_not_def_macro.h"
#include "macro/macro_macro.h"

#include "scope.h"

#include "common/text_processor.h"

namespace comp {
    using namespace std;

    struct PreprocessorResult {
        string sourceCode;
    };

    class Preprocessor : public TextProcessor {
        private:
            vector<shared_ptr<Macro>> macros;
            vector<Scope> scopes;

            static string replace_sub_str(string str, const size_t& begin, const size_t& len, const string &replacement);
            static string replace_sub_strs(string str,const string &subStr,const string &replacement);

            pair<bool, Scope> is_begin_scope(const byte& ch) const;
            pair<bool, Scope> is_end_scope(const byte& ch) const;

            static vector<Scope> get_default_scopes();

            string continue_macro_pass_zero_args(const string& text, shared_ptr<Macro>& macro);
            string continue_macro_pass_multy_args(const string& text, shared_ptr<Macro>& macro);

        public:
            string expand_macros(string text);
            pair<string, vector<string>> extract_args_from_index(const string& text, size_t index) const;
            pair<int, string> extract_arg_substring(const string& text, size_t index) const;

            template<class MacroType>
            void add_macro() {
                macros.push_back(make_shared<MacroType>());
            }

            void add_macro(const Macro& macro);

            bool is_macro_label_defined(const string& label) const;

            void declare_default_macros();
            void declare_default_scopes();

            pair<string, bool> comment_pass(string text) const;
            pair<string, bool> macro_pass(const string& text);
    };
}