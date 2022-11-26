#include "token.h"
#include <map>


namespace frontend {

static std::map<TokenType, std::string> TOKENTYPE_TO_STRING = {
    { TokenType::IDENTIFIER, "IDENTIFIER" },
    { TokenType::NUMBER, "NUMBER" },

    { TokenType::EQUAL, "EQUAL" },
    { TokenType::ENDTOKEN, "ENDTOKEN" }
};


void Token::dump() {
    std::cout << "===================================\n";
    std::cout << "Type: "   << TOKENTYPE_TO_STRING[_typ] << "\n";
    std::cout << "Value: "  << _value << "\n";
    std::cout << "Location: " << _location._fileName 
        << " " << _location._row << ":" << _location._col << "\n";
}



}