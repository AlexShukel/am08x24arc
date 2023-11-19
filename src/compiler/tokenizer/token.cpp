#include "token.h"

namespace comp {
    Token::Token(const string& value, const TokenType& type)
        : value(value),
          type(type) {

    }

    const TokenType& Token::get_type() const {
        return type;
    }

    string Token::get_type_str() const {
        switch (type) {
            case NUMERIC: { return "NUMERIC"; };
            case LABEL: { return "LABEL"; };
            case LABEL_START: { return "LABEL_START"; };
            case WORD: { return "WORD"; };
        }
    }

    const string& Token::get_value() const {
        return value;
    }
}