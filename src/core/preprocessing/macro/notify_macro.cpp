#include "notify_macro.h"

#include "../preprocessor.h"

namespace comp {
    NotifyMacro::NotifyMacro() : Macro("@NOTIFY","",{"@ARG1"}) {

    }

    bool NotifyMacro::comp_time_process(Preprocessor& preprocessor, vector<string>& args) {
        try {
            cout << preprocessor.extract_arg_substring(args[0], 0).second << "\n";
        } catch (const exception& ex) {
            throw runtime_error("Failed to print @NOTIFY macro message, something wrong with argument");
        }

        return true;
    }

    bool NotifyMacro::pre_comp_time_process(Preprocessor& preprocessor, vector<string>& arguments) {

        return true;
    }
};