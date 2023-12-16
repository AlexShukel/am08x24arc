#include "compiler.h"

namespace comp {
    PreprocessorResult Compiler::run_preprocessor(string rawCode) {
        Preprocessor preprocessor;

        preprocessor.declare_default_macros();
        preprocessor.declare_default_scopes();

        // We do comment pass until no comments left
        auto commentResult = preprocessor.comment_pass(rawCode);
        while(commentResult.second) {
            rawCode = commentResult.first;
            commentResult = preprocessor.comment_pass(rawCode);
        }

        // We do macro pass until no macros left
        auto macroResult = preprocessor.macro_pass(rawCode);
        while(macroResult.second) {
            rawCode = macroResult.first;
            macroResult = preprocessor.macro_pass(rawCode);
        }

        return {rawCode};
    }

    TokenizerResult Compiler::run_tokenizer(const string& rawCode) {
        Tokenizer tokenizer;

        auto tokens = tokenizer.tokenize(rawCode);

        return {tokens};
    }

    AssemblerResult Compiler::run_assembler(const vector<Token>& tokens) {
        Assembler inst(DEFAULT_INSTRUCTION_SET);

        auto list = inst.tokenize(tokens);

        inst.clear_labels();

        return {list};
    }

    string Compiler::read_file(const string& path) {
        ifstream file(path);
        stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    Compiler::Compiler(const vector<string>& sourcePaths, const CompilerFlags& flags)
            : sourcePaths(sourcePaths),
              flags(flags) {

    }

    void Compiler::add_source_path(const string& sourcePath) {
        sourcePaths.push_back(sourcePath);
    }

    InstructionList Compiler::compile() {
        string code;

        for(const auto& filePath : sourcePaths) {
            auto fileContent = read_file(filePath);

            code += fileContent;
        }

        try {
            auto preProcessorResult = run_preprocessor(code);

            auto tokenizerResult = run_tokenizer(preProcessorResult.sourceCode);

            auto assemblerResult = run_assembler(tokenizerResult.tokens);

            return assemblerResult.instructions;
        } catch(const exception& ex) {
            cout << ex.what();
        }

        return {};
    }
}
