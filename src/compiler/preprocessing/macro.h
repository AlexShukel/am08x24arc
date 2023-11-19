#pragma once

#include <string>
#include <vector>
#include <regex>
#include <string>
#include <functional>

using namespace std;

namespace comp {
    struct Preprocessor;
    struct Macro;

    using CompileTimeProcess = function<bool(Macro&, vector<string>&, Preprocessor&)>;

    struct Macro {
        string label;
        string body;

        vector<string> argsLabels;
        CompileTimeProcess compTimeProcess;
        CompileTimeProcess preCompTimeProcess;

        Macro(const string& label, const CompileTimeProcess& compTimeProcess);
        Macro(const string& label, const string& body);
        Macro(const string& label, const string& body, const vector<string>& argsLabels);
        Macro(const string& label, const string& body, const vector<string>& argsLabels, const CompileTimeProcess& compTimeProcess);
        Macro(const string& label, const string& body, const vector<string>& argsLabels, const CompileTimeProcess& compTimeProcess, const CompileTimeProcess& preCompTimeProcess);

        string paste_args(const vector<string>& args) const;
    };
}