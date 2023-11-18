#include "compiler.h"

int main() {
    using namespace comp;
    using namespace std;

    vector<string> sources = {
        "src/programs/example1.asm"
    };

    Compiler compiler(sources);

    auto result = compiler.compile();

    result.export_to_file("src/programs/sample1.txt", LOGISIM);

    return 0;
}
