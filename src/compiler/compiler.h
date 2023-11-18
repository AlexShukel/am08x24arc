#pragma once

#include <vector>
#include <string>

#include "opcodes.h"

#include "preprocessing/preprocessor.h"
#include "tokenizer/tokenizer.h"
#include "instructionizer/instructionizer.h"

namespace comp {
    using namespace std;

    class Compiler {
        private:
            vector<string> sourcePaths;

            string run_preprocessor(string rawCode);
            vector<Token> run_tokenizer(const string& rawCode);
            InstructionList run_compiler(const vector<Token>& tokens);

            string read_file(const string& path);

    public:
            Compiler(const vector<string>& sourcePaths);

            void add_source_path(const string& sourcePath);

            InstructionList compile();
    };
}
