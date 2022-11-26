#include "lexer.h"
#include "common.h"

namespace frontend {

std::vector<std::unique_ptr<Token>> Lexer::createTokens() {

    utils::logger::debug(_currentLocation, "Lexer starting");

    std::vector<std::unique_ptr<Token>> tokens;

    auto fileLength = _fileContent.length();
    while (_charCount != fileLength) {
        //utils::logger::debug(_currentLocation, "In createTokens() loop");

        if (isspace(_currentChar)) {
            next();
            continue;
        }
        else if (isalpha(_currentChar) || _currentChar == '_') {
            tokens.push_back(createIdent());
        }
        else if (isdigit(_currentChar)) {
            tokens.push_back(createNumber());
        }
        else {
            tokens.push_back(createOther());      
        }
    }
    
    tokens.push_back(std::make_unique<Token>(
            TokenType::ENDTOKEN, "", _currentLocation));

    utils::logger::debug(_currentLocation, "Lexer done");

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

std::unique_ptr<Token> Lexer::createNumber() {
    std::string value;
    bool hasColon = false;

    while (isdigit(_currentChar) || (_currentChar == '.' && !hasColon)) {
        if (_currentChar == '.') {
            // float
            hasColon = true;
        }

        value += _currentChar;
        next();
    }

    return std::make_unique<Token>(TokenType::NUMBER, value, _currentLocation);
}

std::unique_ptr<Token> Lexer::createOther() {
    
    std::unique_ptr<Token> tok = nullptr;

    switch (_currentChar) {
        case '=':
            tok = std::make_unique<Token>(TokenType::EQUAL, "=", _currentLocation);
            break;
        default:
            // Should never get here
            std::cout << _currentChar << std::endl;
            assert(false);
            break;
    }
        
    next();

    return tok;
}



}