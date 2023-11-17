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

        Macro(const string& label, const CompileTimeProcess& compTimeProcess)
                : label(label),
                  body(""),
                  argsLabels({}),
                  compTimeProcess(compTimeProcess) {

        }

        Macro(const string& label, const string& body)
                : label(label),
                  body(body),
                  argsLabels({}),
                  compTimeProcess([](auto&, auto&, auto&) { return false; }){

        }

        Macro(const string& label, const string& body, const vector<string>& argsLabels)
            : label(label),
              body(body),
              argsLabels(argsLabels),
              compTimeProcess([](auto&, auto&, auto&) { return false; }){

        }

        Macro(const string& label, const string& body, const vector<string>& argsLabels, const CompileTimeProcess& compTimeProcess)
                : label(label),
                  body(body),
                  argsLabels(argsLabels),
                  compTimeProcess(compTimeProcess) {

        }

        string paste_args(const vector<string>& args) const;
    };
}