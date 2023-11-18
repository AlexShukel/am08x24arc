#pragma once

#include <vector>

#include "token.h"
#include "text_processor.h"

namespace comp {
    using namespace std;

    class Tokenizer : public TextProcessor {
        private:
            static bool is_label(const string& tokenStr) {
                return tokenStr.size() > 1 && tokenStr[0] == '$';
            }

            static bool is_label_start(const string& tokenStr) {
                return tokenStr.size() >= 3 && tokenStr[0] == '$' && tokenStr[tokenStr.size() - 1] == ':';
            }

            static bool is_numeric(const string& tokenStr) {
                try {
                    std::ignore = parse_16bit_numeric(tokenStr);
                } catch(...) {
                    return false;
                }

                return true;
            }

            static bool is_word(const string& tokenStr) {
                return true;
            }

        public:
            vector<Token> tokenize(const string& text) const {
                vector<Token> tokens;

                auto strings = explode(text, set{' ', '\t', '\n'});

                for(const auto& tokenStr : strings) {
                    // Label
                    if(is_label(tokenStr)) {
                        if(is_label_start(tokenStr))
                            tokens.emplace_back(tokenStr, LABEL_START);
                        else
                            tokens.emplace_back(tokenStr, LABEL);

                        continue;
                    }

                    // Numeric value
                    if(is_numeric(tokenStr)) {
                        tokens.emplace_back(tokenStr, NUMERIC);
                        continue;
                    }

                    // All others
                    if(is_word(tokenStr)) {
                        tokens.emplace_back(tokenStr, WORD);
                        continue;
                    }
                }

                return tokens;
            }
    };
}