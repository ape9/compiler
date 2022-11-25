#ifndef PARSER_H_
#define PARSER_H_

#include "common.h"
#include "ast.h"

namespace frontend {

struct ParsingState {
    std::string file;
    int level;
};

class Parser {

private:
    ParsingState _parsingState;

};


std::unique_ptr<Expression> parseExpression();
std::unique_ptr<Statement> parseStatement();

}



#endif