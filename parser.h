#ifndef PARSER_H_
#define PARSER_H_

#include "common.h"
#include "ast.h"
#include "token.h"
#include <iostream>

namespace frontend {
class parser {
public:
    parser() = default;
    parser(const std::vector<Token>& toks);

    std::vector<std::unique_ptr<ast_node>> parse();

private:
    class parser_impl;
    std::unique_ptr<parser_impl> _pImpl;
};
}



#endif