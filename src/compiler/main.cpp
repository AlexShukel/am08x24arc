#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    vector<string> sources = {
        "src/programs/example0.asm"
    };

    Compiler compiler(sources);

    auto result = compiler.compile();

    result.export_to_file("src/programs/sample0.txt", LOGISIM);

    return 0;
}
