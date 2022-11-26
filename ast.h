#ifndef AST_H_
#define AST_H_

#include "common.h"
#include "visitor.h"

namespace frontend {

enum class node_type {
    EXPR,
    STMT,
    VARDEF,
    FNDEF
}; 

struct ast_node {
    void accept(Visitor& v) {
        v.visit(*this);
    }
};

struct expression : public ast_node {
};

struct statement : public ast_node {
};

// var_def: foo = 100
struct var_def : public statement {
    var_def(
        const std::string& nam, 
        std::unique_ptr<expression> val,
        const utils::Location& loc
    ) : name(nam), value(std::move(val)), location(loc) {}

    // name of the variable
    std::string name;

    // value as expression
    std::unique_ptr<expression> value;

    utils::Location location;

};

struct fn_args : public statement {
};

struct fn_def : public statement {
    fn_def(const std::string& nam, 
        std::vector<std::unique_ptr<fn_args>>);


};



}

#endif