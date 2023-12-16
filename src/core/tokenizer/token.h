#pragma once

#include <string>

#include "token_type.h"

namespace comp {
    using namespace std;

    class Token {
        private:
            TokenType type;
            string value;

        public:
            Token(const string& value, const TokenType& type);

            const TokenType& get_type() const;
            string get_type_str() const;
            const string& get_value() const;
    };
}