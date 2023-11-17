#include "macro.h"

namespace comp {
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