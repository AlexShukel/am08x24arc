#include "preprocessor.h"

namespace comp {
    void Preprocessor::add_macro(const Macro& macro) {
        for(auto& m : macros)
            if(m.label == macro.label)
                throw runtime_error("Could not add macro with '" + macro.label + "' label, this label is already defined");

        macros.push_back(macro);
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

    string Preprocessor::replace_sub_str(string str,const string &subStr,const string &replacement) {
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

    pair<string, vector<string>> Preprocessor::extract_args_from_index(const string& text, size_t index) const {
        unordered_map<Scope, int> argScopes;
        for(const auto& scope : get_default_scopes())
            argScopes[scope] = 0;

        auto argSubstr = extract_arg_substring(text, index);

        vector<string> args;
        string arg = "";

        for(auto character : argSubstr.second) {
            if(character == '\\')
                continue;

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

            if(!is_in_scope(argScopes) && character == ',') {
                args.push_back(arg);
                arg = "";
            } else {
                arg += character;
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
                macro.preCompTimeProcess(macro, arguments, *this);

                newText = regex_replace(newText, std::regex(macro.label), macro.paste_args({}));
            } else {
                size_t index = newText.find(macro.label, 0);

                if(index == std::string::npos)
                    continue;

                auto result = extract_args_from_index(newText, index);

                string& macroString = result.first;
                arguments = result.second;

                macro.preCompTimeProcess(macro, arguments, *this);

                newText = replace_sub_str(newText, macroString, macro.paste_args(arguments));
            }

            if(newText != text) {
                macro.compTimeProcess(macro, arguments, *this);

                return make_pair(newText, true);
            }
        }

        return make_pair(text, false);
    }

    void Preprocessor::declare_default_macros() {
        add_macro(
            Macro(
                "@INCLUDE",
                "",
                {"@ARG1"},
                [](auto& macro, auto& args, Preprocessor& pp) {
                    try {
                        string fileName = pp.extract_arg_substring(args[0], 0).second;

                        cout << "Trying to include file: " << fileName << "\n";
                    } catch (const exception& ex) {
                        throw runtime_error("Failed to parse file name in @INCLUDE macro, something wrong with macro arguments");
                    }

                    return true;
                }
            ));

        add_macro(
            Macro(
                "@MACRO",
                "",
                {"@ARG1", "@ARG2", "@ARG3"},
                [](auto& macro, auto& args, auto& pp) {
                    auto argResult = pp.extract_args_from_index(args[1], 0);
                    pp.add_macro(Macro(args[0], args[2], argResult.second));

                    return true;
                }
            ));

        add_macro(
            Macro(
                "@NOTIFY",
                "",
                {"@ARG1"},
                [&](auto& macro, auto& args, auto& pp) {
                    try {
                        cout << pp.extract_arg_substring(args[0], 0).second << "\n";
                    } catch (const exception& ex) {
                        throw runtime_error("Failed to print @NOTIFY macro message, something wrong with argument");
                    }

                    return true;
                }
            ));

        add_macro(
            Macro(
                "@IF_DEF",
                "",
                {"@ARG1", "@ARG2"},
                [](auto& macro, auto& args, auto& pp) {
                    return true;
                },
                [](auto& macro, auto& args, auto& pp) {
                    if(pp.is_macro_label_defined(args[0]))
                        macro.body = args[1];

                    return true;
                }
            ));

        add_macro(
            Macro(
                "@IF_NOT_DEF",
                "",
                {"@ARG1", "@ARG2"},
                [](auto& macro, auto& args, auto& pp) {
                    return true;
                },
                [](auto& macro, auto& args, auto& pp) {
                    if(!pp.is_macro_label_defined(args[0]))
                        macro.body = args[1];

                    return true;
                }
            ));
    }

    bool Preprocessor::is_macro_label_defined(const string& label) const {
        for(const auto& macro : macros)
            if(macro.label == label)
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
