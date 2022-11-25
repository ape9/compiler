#include "lexer.h"
#include "common.h"

namespace frontend {

std::vector<std::unique_ptr<Token>> Lexer::createTokens() {

    std::vector<std::unique_ptr<Token>> tokens;

    auto fileLength = _fileContent.length();
    while (_charCount != fileLength) {
        if (isspace(_currentChar)) {
            next();
            continue;
        }
        else if (isalpha(_currentChar) || _currentChar == '_') {
            // Identified
            tokens.push_back(createIdent());
        }
        else if (isdigit(_currentChar)) {
            // Number
        }
        else {
            // Other tokens
        // Move to next character
        next();        
        }

    }

    return std::move(tokens);
}


char Lexer::peek(int n) {

}

void Lexer::next() {
   // if (_charCount != _fileContent.length()) {
        _currentChar = _fileContent[++_charCount];
    //}

    if (_currentChar == '\n') {
        _currentLocation.setCol(0);
        _currentLocation.setRow(_currentLocation._row + 1);
    } 
    else {
        _currentLocation.setCol(_currentLocation._col + 1);
    }
}


std::unique_ptr<Token> Lexer::createIdent() {
    std::string value;
    while (isalnum(_currentChar) || _currentChar == '_') {
        value += _currentChar;
        next();
    }

    return std::make_unique<Token>(TokenType::IDENTIFIER, value, _currentLocation);
}

std::unique_ptr<Token> createNumber() {

}

std::unique_ptr<Token> createOther() {

}



}