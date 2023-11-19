#include "macro_macro.h"

#include "../preprocessor.h"

namespace comp {
    MacroMacro::MacroMacro() : Macro("@MACRO","",{"@ARG1", "@ARG2", "@ARG3"}) {

    }

    bool MacroMacro::pre_comp_time_process(Preprocessor& preprocessor, vector<string>& arguments) {
        return true;
    }

    bool MacroMacro::comp_time_process(Preprocessor& preprocessor, vector<string>& args) {
        auto argResult = preprocessor.extract_args_from_index(args[1], 0);
        preprocessor.add_macro(Macro(args[0], args[2], argResult.second));

        return true;
    }
};