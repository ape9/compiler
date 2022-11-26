#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"
#include "location.h"
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

namespace frontend {

class Lexer {
public:

    Lexer() = default;

    Lexer(const std::string &fileName) {
        std::ifstream f(fileName);
        std::stringstream ss;
        ss << f.rdbuf();
        _fileContent = ss.str();
        _currentLocation = utils::Location(fileName, 0, 0);
        _currentChar = _fileContent[0];
        _charCount = 0;
    }

    // Main method to create a list of tokens from source code
    std::vector<std::unique_ptr<Token>> createTokens();

    static void print_tokens(std::vector<std::unique_ptr<Token>> toks) {
        for (auto& tok : toks) {
            tok->dump();
        }
    }

private:
    // Peek forward n characters
    char peek(int n);

    // Move to next character
    void next();

    std::unique_ptr<Token> createIdent();
    std::unique_ptr<Token> createNumber();
    std::unique_ptr<Token> createOther();

private:

    std::string _fileContent;
    
    // Stores location information
    utils::Location _currentLocation;
    
    // Most recently read character
    char _currentChar;

    // Number of read characters
    uint32_t _charCount;
};


}

#endif