#include "preprocessor.h"

namespace comp {
    void Preprocessor::add_macro(const Macro& macro) {
        if(is_macro_label_defined(macro.get_label()))
            throw runtime_error("Could not add macro with '" + macro.get_label() + "' label, this label is already defined");

        macros.push_back(make_shared<Macro>(macro));
    }

    vector<Scope> Preprocessor::get_default_scopes() {
        return {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'},
            {'<', '>'},
            {'"', '"'}
        };
    }

    string Preprocessor::replace_sub_str(string str, const size_t& begin, const size_t& len, const string &replacement) {
        str.replace(begin, len, replacement);

        return str;
    }

    string Preprocessor::replace_sub_strs(string str, const string &subStr, const string &replacement) {
        size_t pos = str.find(subStr);

        while (pos != std::string::npos) {
            str.replace(pos, subStr.length(), replacement);
            pos = str.find(subStr, pos + replacement.length());
        }

        return str;
    }

    bool is_in_scope(const unordered_map<Scope, int>& scopes) {
        for(const auto& scope : scopes)
            if(scope.second != 0)
                return true;

        return false;
    }

    pair<int, string> Preprocessor::extract_arg_substring(const string& text, size_t index) const {
        unordered_map<Scope, int> argScopes;
        for(const auto& scope : get_default_scopes())
            argScopes[scope] = 0;

        while(true) {
            if(index >= text.size())
                throw runtime_error("Expected scope open character for multiple argument macro");

            byte character = text[index];

            if(!is_begin_scope(character).first) {
                ++index;
            } else {
                auto scope = is_begin_scope(character);
                argScopes[scope.second] = 1;

                break;
            }
        }

        size_t endIndex = index + 1;

        while(true) {
            if(endIndex >= text.size())
                throw runtime_error("Not closed macro argument scope");

            byte character = text[endIndex];

            ++endIndex;

            if(character == '\\') {
                ++endIndex;
                continue;
            }

            auto beginScope = is_begin_scope(character);
            auto endScope = is_end_scope(character);

            // There we handle if scope start and end symbols are equal
            if(beginScope.first && endScope.first) {
                auto& scopeValue = argScopes[beginScope.second];

                if(scopeValue > 0)
                    --scopeValue;
                else
                    ++scopeValue;
            } else {
                if(beginScope.first)
                    ++argScopes[beginScope.second];

                if(endScope.first)
                    --argScopes[endScope.second];
            }

            if(is_in_scope(argScopes))
                continue;

            break;
        }

        return {endIndex, text.substr(index + 1, endIndex - index - 2)};
    }

    string Preprocessor::open_top_scope(string text) {

        return text;
    }

    pair<string, vector<string>> Preprocessor::extract_args_from_index(const string& text, size_t index) const {
        unordered_map<Scope, int> argScopes;
        for(const auto& scope : get_default_scopes())
            argScopes[scope] = 0;

        auto argSubstr = extract_arg_substring(text, index);

        vector<string> args;
        string arg = "";

        bool skip = false;
        for(size_t i = 0; i < argSubstr.second.size(); ++i) {
            auto character = argSubstr.second[i];

            if(character == '\\' && !skip) {
                skip = true;
                continue;
            }

            auto beginScope = is_begin_scope(character);
            auto endScope = is_end_scope(character);

            // There we handle if scope start and end symbols are equal
            if(beginScope.first && endScope.first) {
                auto& scopeValue = argScopes[beginScope.second];

                if(scopeValue > 0)
                    --scopeValue;
                else
                    ++scopeValue;
            } else {
                if(beginScope.first)
                    ++argScopes[beginScope.second];

                if(endScope.first)
                    --argScopes[endScope.second];
            }

            // Todo, this work not really how it was intendant
            if(skip) {
                arg += character;
                skip = false;
            } else {
                if(!is_in_scope(argScopes) && (character == ',')) {
                    args.push_back(arg);
                    arg = "";
                } else {
                    arg += character;
                }
            }
        }

        if(!arg.empty())
            args.push_back(arg);

        return make_pair(text.substr(index, argSubstr.first - index), args);
    }

    pair<string, bool> Preprocessor::comment_pass(string text) const {
        bool madeChanges = false;

        size_t index = 0;

        long long startIndex = -1;
        long long endIndex = -1;

        while(true) {
            char c = text[index];

            if(c == '#' && startIndex == -1)
                startIndex = index;

            if(c == '\n' && endIndex == -1 && startIndex != -1)
                endIndex = index + 1;

            if(startIndex != -1 && endIndex != -1)
                break;

            ++index;

            if(index >= text.size()) {
                if(startIndex != -1)
                    endIndex = index - 1;

                break;
            }
        }

        if(endIndex != -1 && startIndex != -1) {
            auto commentLength = endIndex - startIndex;
            auto commentSubstring = text.substr(startIndex, commentLength);

            text.erase(startIndex, commentLength);

            madeChanges = true;
        }

        return make_pair(text, madeChanges);
    }

    string Preprocessor::expand_macros(string text) {
        auto passResult = macro_pass(text);
        while(passResult.second) {
            text = passResult.first;
            passResult = macro_pass(text);
        }

        return text;
    }

    string Preprocessor::continue_macro_pass_zero_args(const string& text, shared_ptr<Macro>& macro) {
        vector<string> args;

        macro->pre_comp_time_process(*this, args);

        string newText = regex_replace(text, std::regex(macro->get_label()), macro->paste_args({}));

        if(newText != text)
            macro->comp_time_process(*this, args);

        return newText;
    }

    string Preprocessor::continue_macro_pass_multy_args(const string& text, shared_ptr<Macro>& macro) {
        size_t index = text.find(macro->get_label(), 0);

        if(index == std::string::npos)
            return text;

        auto result = extract_args_from_index(text, index);

        string& macroString = result.first;
        vector<string> arguments = result.second;

        // Note that we do not do that
        // for(auto& arg : arguments) {
        //     arg = expand_macros(arg);
        // }

        macro->pre_comp_time_process(*this, arguments);

        string newText = replace_sub_str(text, index, macroString.size(), macro->paste_args(arguments));

        if(newText != text)
            macro->comp_time_process(*this, arguments);

        return newText;
    }

    pair<string, bool> Preprocessor::macro_pass(const string& text) {
        for(auto i = 0; i < macros.size(); ++i) {
            auto macro = macros[i];

            string newText = text;

            if(macro->is_zero_arg_macro())
                newText = continue_macro_pass_zero_args(newText, macro);
            else
                newText = continue_macro_pass_multy_args(newText, macro);

            if(newText != text)
                return make_pair(newText, true);
        }

        return make_pair(text, false);
    }

    void Preprocessor::declare_default_macros() {
        add_macro<IncludeMacro>();
        add_macro<IfNotDefMacro>();
        add_macro<MacroMacro>();
        add_macro<NotifyMacro>();
    }

    bool Preprocessor::is_macro_label_defined(const string& label) const {
        for(const auto& macro : macros)
            if(macro->get_label() == label)
                return true;

        return false;
    }

    pair<bool, Scope> Preprocessor::is_begin_scope(const byte& ch) const {
        for(const auto& scope : scopes)
            if(scope.beginChar == ch)
                return {true, scope};

        return {false, {}};
    }

    pair<bool, Scope> Preprocessor::is_end_scope(const byte& ch) const {
        for(const auto& scope : scopes)
            if(scope.endChar == ch)
                return {true, scope};

        return {false, {}};
    }

    void Preprocessor::declare_default_scopes() {
        auto defaultScopes = get_default_scopes();
        scopes = defaultScopes;
    }
}
