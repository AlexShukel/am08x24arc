#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    vector<string> sources = {
        "src/programs/example1.asm"
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

    result.export_to_file("src/programs/example1.txt", LOGISIM);

    return 0;
}
