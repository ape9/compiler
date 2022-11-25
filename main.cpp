#include "lexer.h"


int main(int argc, char **argv) {

    auto lexer = frontend::Lexer("test.txt");
    auto tokens = lexer.createTokens();
    for (auto& tok : tokens) {
        tok->dump();
    }

    return 0;
}