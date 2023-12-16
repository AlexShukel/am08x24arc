#include <fstream>
#include <iostream>

#include "preprocessing/preprocessor.h"

using namespace std;
using namespace comp;

void save_to_file(const string& fileName, const string& code) {
    ofstream file(fileName, std::ofstream::out | std::ofstream::trunc);
    file << code;
    file.close();
}

string load_from_file(const string& fileName) {
    ifstream file(fileName);
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// preprocessor file.in file.out
int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "Failed to parse arguments";
        return 1;
    }

    try {
        string rawCode = load_from_file(argv[1]);

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

        save_to_file(argv[2], rawCode);
    } catch (const exception& ex) {
        cout << ex.what() << "\n";
        return 1;
    }

    return 0;
}