#include "text_processor.h"

namespace comp {
    vector<string> TextProcessor::explode(const string& str, set<char, less<char>, allocator<char>> ch) {
        string next;
        vector<string> result;

        for (string::const_iterator it = str.begin(); it != str.end(); it++) {
            if (ch.end() != ch.find(*it)) {
                if (!next.empty()) {
                    result.push_back(next);
                    next.clear();
                }
            } else
                next += *it;
        }

        if (!next.empty())
            result.push_back(next);

        return result;
    }
}