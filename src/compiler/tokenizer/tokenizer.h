#pragma once

#include <vector>

#include "token.h"
#include "common/text_processor.h"

namespace comp {
    using namespace std;

    struct TokenizerResult {
        vector<Token> tokens;
    };

    class Tokenizer : public TextProcessor {
        private:
            static bool is_label(const string& tokenStr);
            static bool is_label_start(const string& tokenStr);
            static bool is_numeric(const string& tokenStr);
            static bool is_word(const string& tokenStr);

        public:
            vector<Token> tokenize(const string& text) const;
    };
}