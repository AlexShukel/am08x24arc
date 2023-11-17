#include "opcodes.h"
#include "tokenizer.h"
#include "preprocessing/preprocessor.h"

using namespace comp;
using namespace std;

string read_file(const string& path) {
    ifstream file(path);
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

void save_file(const string& path, const string& text) {
    ofstream file(path);
    file << text;
}

int main() {
    InstructionList list;

    auto assemblyCode = read_file("src/programs/example0.asm");

    try {
        Preprocessor preprocessor;

        preprocessor.add_macro(
        Macro(
            "@NOTIFY",
            "",
            {"@ARG1"},
            [&](auto& macro, auto& args, auto& preprocessor) {
                for(auto arg : args)
                    cout << arg;

                cout << endl;

                return true;
            }
        ));

        preprocessor.add_macro(
        Macro{
            "@MACRO",
            "",
            {"@ARG1", "@ARG2", "@ARG3"},
            [](auto& macro, auto& args, auto& pp) {
                auto argResult = Preprocessor::extract_args_from_index(args[1], 0);
                pp.add_macro(Macro( args[0], args[2], argResult.second));

                return true;
            }
        });

        // We do comment pass until no comments left
        auto commentResult = preprocessor.comment_pass(assemblyCode);
        while(commentResult.second) {
            assemblyCode = commentResult.first;
            commentResult = preprocessor.comment_pass(assemblyCode);
        }
        save_file("src/programs/sample1.o0", assemblyCode);

        auto macroResult = preprocessor.macro_pass(assemblyCode);
        while(macroResult.second) {
            assemblyCode = macroResult.first;
            macroResult = preprocessor.macro_pass(assemblyCode);
        }
        save_file("src/programs/sample1.o1", assemblyCode);

        auto labelResult = preprocessor.label_pass(assemblyCode);
        while(labelResult.second) {
            assemblyCode = labelResult.first;
            labelResult = preprocessor.label_pass(assemblyCode);
        }
        save_file("src/programs/sample1.o2", assemblyCode);

        Tokenizer tokenizer;

        list = tokenizer.tokenize(DEFAULT_INSTRUCTION_SET, assemblyCode);
    } catch(exception& ex) {
        cout << ex.what();
    }

    list.export_to_file("src/programs/sample1.txt", LOGISIM);

    return 0;
}
