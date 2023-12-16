#pragma once

#include <tuple>
#include <vector>
#include <set>

#include "token.h"
#include "../common/text_processor.h"

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

            static void save_to_file(const vector<Token>& token, const string& fileName);
    };
}