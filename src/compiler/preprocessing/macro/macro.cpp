#include "macro.h"

#include "preprocessing/preprocessor.h"

namespace comp {
    Macro::Macro(const string& label, const string& body)
            : label(label),
              body(body),
              argsLabels({}) {

    }

    Macro::Macro(const string& label, const string& body, const vector<string>& argsLabels)
            : label(label),
              body(body),
              argsLabels(argsLabels) {

    }

    const string& Macro::get_label() const {
        return label;
    }

    const string& Macro::get_body() const {
        return body;
    }

    const vector<string>& Macro::get_arg_labels() const {
        return argsLabels;
    }

    size_t Macro::get_arg_count() const {
        return argsLabels.size();
    }

    bool Macro::is_zero_arg_macro() const {
        return argsLabels.empty();
    }

    string Macro::paste_args(const vector<string>& args) const {
        if(argsLabels.size() == 0)
            return body;

        string newBody = body;

        if(args.size() != argsLabels.size()) {
            string message = "Could not paste " + label + " macro arguments, expected " +  to_string(argsLabels.size()) + " but provided " + to_string(args.size());
            throw runtime_error(message);
        }

        for(size_t i = 0; i < args.size(); ++i) {
            const auto argLabel = argsLabels[i];
            const auto value = args[i];

            newBody = regex_replace(newBody, std::regex(argLabel), value);
        }

        return newBody;
    }
}