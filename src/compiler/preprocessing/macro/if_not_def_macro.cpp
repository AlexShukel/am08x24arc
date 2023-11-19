#include "if_not_def_macro.h"

#include "../preprocessor.h"

namespace comp {
    IfNotDefMacro::IfNotDefMacro() : Macro("@IF_NOT_DEF","",{"@ARG1", "@ARG2"}) {

    }

    bool IfNotDefMacro::pre_comp_time_process(Preprocessor& preprocessor, vector<string>& arguments) {
        if(!preprocessor.is_macro_label_defined(arguments[0]))
            body = preprocessor.expand_macros(arguments[1]);
        else
            body = "";

        return true;
    }

    bool IfNotDefMacro::comp_time_process(Preprocessor& preprocessor, vector<string>& args) {
        return true;
    }
};