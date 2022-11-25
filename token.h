#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <string>
#include "location.h"

namespace frontend {

enum class TokenType {
    IDENTIFIER,
    NUMBER,

    LPAREN,
    RPAREN,
    LSQUARE,
    RSQUARE,
    LCURLY,
    RCURLY,
};

struct Token {
    Token(TokenType typ, const std::string& value, const utils::Location& location) 
        : _typ(typ), _value(value), _location(location) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Token& tok) {
        std::cout << tok._value;
        return os;
    }
    
    void dump();

    TokenType _typ;
    std::string _value;
    utils::Location _location;
};

}


#endif 