#include "preprocessor.h"

namespace comp {
    void Preprocessor::add_macro(const Macro& macro) {
        for(auto& m : macros)
            if(m.label == macro.label)
                throw runtime_error("Could not add macro with '" + macro.label + "' label, this label is already defined");

        macros.push_back(macro);
    }

    string Preprocessor::replace_sub_str(string str,const string &subStr,const string &replacement) {
        size_t pos = str.find(subStr);

        while (pos != std::string::npos) {
            str.replace(pos, subStr.length(), replacement);
            pos = str.find(subStr, pos + replacement.length());
        }

        return str;
    }

    pair<string, vector<string>> Preprocessor::extract_args_from_index(const string& text, size_t index) {
        auto startIndex = index;

        while(true) {
            if(text[index] != '(') {
                ++index;

                if(index >= text.size())
                    throw runtime_error("Expected '(' for multiple argument macro");
            } else
                break;
        }

        int scope = 1;
        size_t endIndex = index + 1;

        while(true) {
            if(text[endIndex] == '(')
                ++scope;
            else if(text[endIndex] == ')')
                --scope;

            ++endIndex;

            if(scope == 0)
                break;

            if(endIndex >= text.size())
                throw runtime_error("Not closed macro argument scope");
        }

        string argSubstr = text.substr(index + 1, endIndex - index - 2);

        vector<string> args;
        string arg = "";
        int argScopes = 0;

        for(auto c : argSubstr) {
            if(c == '(')
                ++argScopes;
            else if(c == ')')
                --argScopes;

            if(argScopes == 0 && c == ',') {
                args.push_back(arg);
                arg = "";
            } else {
                arg += c;
            }
        }

        if(arg != "")
            args.push_back(arg);

        return make_pair(text.substr(startIndex, endIndex - startIndex), args);
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

            if(c == '\n' && endIndex == -1 && startIndex != -1) {
                endIndex = index;
            }

            if(startIndex != -1 && endIndex != -1) {
                break;
            }

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

    pair<string, bool> Preprocessor::macro_pass(const string& text) {
        for(auto i = 0; i < macros.size(); ++i) {
            auto macro = macros[i];

            size_t argCount = macro.argsLabels.size();
            vector<string> arguments;

            string newText = text;

            if(argCount == 0) {
                newText = regex_replace(newText, std::regex(macro.label), macro.paste_args({}));
            } else {
                size_t index = newText.find(macro.label, 0);

                if(index == std::string::npos)
                    continue;

                auto result = extract_args_from_index(newText, index);

                string& macroString = result.first;
                arguments = result.second;

                newText = replace_sub_str(newText, macroString, macro.paste_args(arguments));
            }

            if(newText != text) {
                macro.compTimeProcess(macro, arguments, *this);

                return make_pair(newText, true);
            }
        }

        return make_pair(text, false);
    }
}
