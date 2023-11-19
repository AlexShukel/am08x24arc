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

    string TextProcessor::to_upper_case(string str) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto& c){
            return std::toupper(c);
        });

        return str;
    }

    word TextProcessor::parse_16bit_numeric(string arg) {
        if(arg.empty())
            throw std::runtime_error("Failed to parse instruction argument");

        string defaultCaseArg = arg;
        arg = to_upper_case(arg);

        NumberFormat format = NumberFormat::DECIMAL;

        if(arg[0] == '-') {
            format = NumberFormat::DECIMAL;
        }

        if(arg.size() >= 3) {
            stringstream ss;
            ss << arg[0] << arg[1];

            string formatPrefix = ss.str();

            if(formatPrefix == "0X")
                format = NumberFormat::HEXADECIMAL;
            else if(formatPrefix == "0B")
                format = NumberFormat::BINARY;
            else
                format = NumberFormat::DECIMAL;

            if(arg.size() == 3 && arg[0] == '\'' && arg[2] == '\'' ) {
                format = NumberFormat::CHARACTER;
            }
        }

        switch(format) {
            case NumberFormat::DECIMAL: {
                return static_cast<short>(stoi(arg));
            };
            case NumberFormat::HEXADECIMAL: {
                arg = remove_prefix(arg);

                return static_cast<short>(stoi(arg, 0, 16));
            };
            case NumberFormat::BINARY: {
                if(arg.size() != 18)
                    throw exception("Failed to parse binary number, expected 16 bits");

                arg = remove_prefix(arg);

                bitset<16> bitSet(arg);

                return static_cast<word>(bitSet.to_ulong());
            };
            case NumberFormat::CHARACTER: {
                return defaultCaseArg[1];
            };
        }

        return 0;
    }

    string TextProcessor::remove_prefix(string number) {
        reverse(number.begin(), number.end());
        number.pop_back();
        number.pop_back();
        reverse(number.begin(), number.end());

        return number;
    }
}