#include "token.h"
#include <map>


namespace frontend {

static std::map<TokenType, std::string> TOKENTYPE_TO_STRING = {
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::NUMBER, "NUMBER"}
};


void Token::dump() {
    std::cout << "Type: "   << TOKENTYPE_TO_STRING[_typ] << "\n";
    std::cout << "Value: "  << _value << "\n";
}



}