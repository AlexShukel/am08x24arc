#include "opcodes.h"
#include "tokenizer.h"

using namespace comp;
using namespace std;

int main() {
    InstructionList list;

    Tokenizer tokenizer;

    try {
        list = tokenizer.tokenize(
            DEFAULT_INSTUCTION_SET,
            "push 65535 push 0xffff push 0b0000000000000001 push 'c' pop pop pop pop jmpa 0"
        );
    } catch(exception& ex) {
        cout << ex.what();
    }

    list.export_to_file("main.txt", LOGISIM);

    return 0;
}
