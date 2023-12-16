#include "tokenizer.h"

namespace comp {
    bool Tokenizer::is_label(const string& tokenStr) {
        return tokenStr.size() > 1 && tokenStr[0] == '$';
    }

    bool Tokenizer::is_label_start(const string& tokenStr) {
        return tokenStr.size() >= 3 && tokenStr[0] == '$' && tokenStr[tokenStr.size() - 1] == ':';
    }

    bool Tokenizer::is_numeric(const string& tokenStr) {
        try {
            std::ignore = parse_16bit_numeric(tokenStr);
        } catch(...) {
            return false;
        }

        return true;
    }

    bool Tokenizer::is_word(const string& tokenStr) {
        return true;
    }

    vector<Token> Tokenizer::tokenize(const string& text) const {
        vector<Token> tokens;

        auto strings = explode(text, set<char>{' ', '\t', '\n'});

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

    void Tokenizer::save_to_file(const vector<Token>& tokens, const string& fileName) {
        ofstream file(fileName);

        for(const auto& token : tokens) {
            file << "    " << token.get_value() << endl;
        }

        // for(size_t i = 0; i < tokens.size(); ++i) {
        //     const auto& token = tokens[i];
        //     const auto& type = token.get_type();
//
        //     if(type != LABEL_START) {
        //         file << "    " << token.get_value();
//
        //         if((i + 1) < tokens.size()) {
        //             const auto& nextToken = tokens[++i];
        //             const auto& nextTokenType = nextToken.get_type();
//
        //             if(nextTokenType == NUMERIC || nextTokenType == LABEL) {
        //                 file << " " << nextToken.get_value();
        //             }
        //         }
        //     } else {
        //         file << token.get_value();
        //     }
//
        //     file << endl;
        // }

        file.close();
    }
}