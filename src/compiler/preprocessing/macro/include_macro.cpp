#include "include_macro.h"

#include "../preprocessor.h"

namespace comp {
    string rread_file(const string& path) {
        ifstream file(path);
        stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    IncludeMacro::IncludeMacro() : Macro("@INCLUDE","",{"@ARG1"}) {

    }

    bool IncludeMacro::pre_comp_time_process(Preprocessor& preprocessor, vector<string>& args) {
        try {
            string filePath = preprocessor.extract_arg_substring(args[0], 0).second;
            string sourceCode = rread_file(filePath);

            auto commentResult = preprocessor.comment_pass(sourceCode);
            while(commentResult.second) {
                sourceCode = commentResult.first;
                commentResult = preprocessor.comment_pass(sourceCode);
            }

            sourceCode = preprocessor.expand_macros(sourceCode);
            body = sourceCode;

        } catch (const exception& ex) {
            throw runtime_error("Failed to print @INCLUDE macro message, something wrong with argument");
        }

        return true;
    }

    bool IncludeMacro::comp_time_process(Preprocessor& preprocessor, vector<string>& args) {


        return true;
    }
};