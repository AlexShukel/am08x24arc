#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    vector<string> sources = {
        "assembly/examples/include_file.asm"
    };

    CompilerFlags flags = {
        .preprocessor = {
            .exportCommentPassResult = true,
            .exportMacroPassResult = true
        },
        .exportTokenizerResult = true
    };

    Compiler compiler(sources, flags);

    auto result = compiler.compile();

    result.export_to_file("assembly/examples/include_file.txt", LOGISIM);

    return 0;
}
