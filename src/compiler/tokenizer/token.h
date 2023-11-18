#pragma once

#include <string>

namespace comp {
    using namespace std;

    enum TokenType {
        NUMERIC,
        WORD,

        LABEL,
        LABEL_START,
    };

    class Token {
        private:
            TokenType type;
            string value;

        public:
            Token(const string& value, const TokenType& type)
                : value(value),
                  type(type) {

            }

            const TokenType& get_type() const {
                return type;
            }

            string get_type_str() const {
                switch (type) {
                    case NUMERIC: { return "NUMERIC"; };
                    case LABEL: { return "LABEL"; };
                    case LABEL_START: { return "LABEL_START"; };
                    case WORD: { return "WORD"; };
                }
            }

            const string& get_value() const {
                return value;
            }
    };
}