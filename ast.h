#ifndef AST_H_
#define AST_H_

#include "common.h"
#include "visitor.h"

namespace frontend {
//namespace ast

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
    expression() {}
    virtual ~expression() = default;
};

struct number : public expression {
    number(const std::string& val) 
        : value(val) {}
    
    std::string value;
};

struct bin_expr : public expression {
    bin_expr(
        std::unique_ptr<expression> l,
        std::unique_ptr<expression> r,
        const std::string& o
    ) : left(std::move(l)),
        right(std::move(r)),
        op(o) {}

    std::unique_ptr<expression> left; 
    std::unique_ptr<expression> right;
    std::string op;
};

struct statement : public ast_node {
    statement() {}
    virtual ~statement() = default;
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
        //std::unique_ptr<fn_args> a,
        std::vector<std::unique_ptr<statement>> b)
        : name(nam), body(std::move(b)) {}

    std::string name;
    std::vector<std::unique_ptr<fn_args>> args;
    std::vector<std::unique_ptr<statement>> body;
    //std::unique_ptr<expression> retval;
};



}

#endif