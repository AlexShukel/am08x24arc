#pragma once

#include <vector>
#include <string>

#include "instruction/opcodes.h"

#include "preprocessing/preprocessor.h"
#include "tokenizer/tokenizer.h"
#include "assembler/assembler.h"

namespace comp {
    using namespace std;

    struct CompilerFlags {
        struct {
            bool exportCommentPassResult;
            bool exportMacroPassResult;
        } preprocessor;

        bool exportTokenizerResult;
    };

    class Compiler {
        private:
            CompilerFlags flags;
            vector<string> sourcePaths;

            PreprocessorResult run_preprocessor(string rawCode);
            TokenizerResult run_tokenizer(const string& rawCode);
            AssemblerResult run_assembler(const vector<Token>& tokens);

            static string read_file(const string& path);

    public:
            Compiler(const vector<string>& sourcePaths, const CompilerFlags& flags);

            void add_source_path(const string& sourcePath);

            InstructionList compile();
    };
}
