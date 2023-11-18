#include "compiler.h"

namespace comp {
    string Compiler::run_preprocessor(string rawCode) {
        Preprocessor preprocessor;

        preprocessor.declare_default_macros();

        // We do comment pass until no comments left
        auto commentResult = preprocessor.comment_pass(rawCode);
        while(commentResult.second) {
            rawCode = commentResult.first;
            commentResult = preprocessor.comment_pass(rawCode);
        }

        auto macroResult = preprocessor.macro_pass(rawCode);
        while(macroResult.second) {
            rawCode = macroResult.first;
            macroResult = preprocessor.macro_pass(rawCode);
        }

        return rawCode;
    }

    vector<Token> Compiler::run_tokenizer(const string& rawCode) {
        Tokenizer tokenizer;

        auto tokens = tokenizer.tokenize(rawCode);

        return tokens;
    }

    InstructionList Compiler::run_compiler(const vector<Token>& tokens) {
        Instructionizer inst(DEFAULT_INSTRUCTION_SET);

        auto list = inst.tokenize(tokens);

        inst.clear_labels();

        return list;
    }

    string Compiler::read_file(const string& path) {
        ifstream file(path);
        stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    Compiler::Compiler(const vector<string>& sourcePaths)
            : sourcePaths(sourcePaths) {

    }

    void Compiler::add_source_path(const string& sourcePath) {
        sourcePaths.push_back(sourcePath);
    }

    InstructionList Compiler::compile() {
        string code;

        for(auto filePath : sourcePaths) {
            auto fileContent = read_file(filePath);

            code += fileContent;
        }

        auto preProcessorResult = run_preprocessor(code);

        auto tokens = run_tokenizer(preProcessorResult);

        auto instructions = run_compiler(tokens);

        return instructions;
    }
}
