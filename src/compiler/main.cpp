#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    {
        vector<string> sources = {
                "assembly/examples/common/example1.asm"
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

        result.export_to_file("assembly/examples/common/example1.txt", LOGISIM);
        result.export_to_file("dump.asm", ASSEMBLY);
    }

    return 0;
}
