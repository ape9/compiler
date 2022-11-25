#ifndef AST_H_
#define AST_H_

#include "common.h"

namespace frontend {

struct Expression {

};

struct Statement {

};

// Assignment: foo = 100
struct Assignment : public Statement {
    Assignment(
        const std::string& nam, 
        std::unique_ptr<Expression> val,
        const utils::Location& loc
    ) : name(nam), value(std::move(val)), location(loc) {}

    // name of the variable
    std::string name;

    // value as expression
    std::unique_ptr<Expression> value;

    utils::Location location;

};



}

#endif