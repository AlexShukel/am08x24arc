#include "tokenizer.h"

namespace comp {
    string Tokenizer::to_upper_case(string str) {
        std::transform(str.begin(), str.end(), str.begin(), [](auto& c){
            return std::toupper(c);
        });

        return str;
    }

    string Tokenizer::remove_prefix(string number) {
        reverse(number.begin(), number.end());
        number.pop_back();
        number.pop_back();
        reverse(number.begin(), number.end());

        return number;
    }

    word Tokenizer::parse_16bit_numeric(string arg) {
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

    InstructionList Tokenizer::tokenize(const InstructionSet& instuctions, const string& text) {
        InstructionList list;

        const auto tokens = explode(text, set{' ', '\t', '\n'});

        for(auto it = tokens.begin(); it != tokens.end();) {
            auto keyword = *it;
            keyword = to_upper_case(keyword);

            auto instruction = instuctions.find(keyword);

            if(!instruction.is_24bit_instruction()) {
                ++it;

                if(it == tokens.end())
                    throw std::runtime_error("Expected instruction argument after " + keyword + "keyword");

                auto argument = *it;

                instruction.argument.val = parse_16bit_numeric(argument);
            }

            ++it;

            list.add(instruction);
        }

        return list;
    }
}