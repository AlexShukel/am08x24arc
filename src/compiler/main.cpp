#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    {
        vector<string> sources = {
                "assembly/examples/gfx/gfx_cpu.asm"
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

        result.export_to_file("assembly/examples/gfx/gfx_cpu.txt", LOGISIM);
        result.export_to_file("gfx_cpu_cpu.asm", ASSEMBLY);
    }

    {
        vector<string> sources = {
                "assembly/examples/gfx/gfx_gpu.asm"
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

        result.export_to_file("assembly/examples/gfx/gfx_gpu.txt", LOGISIM);
        result.export_to_file("dump_gpu.asm", ASSEMBLY);
    }

    return 0;
}
