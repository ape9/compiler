#ifndef VISITOR_H_
#define VISITOR_H_
#include "common.h"

namespace frontend {

struct ast_node;
struct expression;
struct statement;
struct var_def;
struct fn_def;

struct Visitor {
    virtual void visit(ast_node& node) = 0;
    virtual void visit(expression& expr) = 0;
    virtual void visit(statement& stmt) = 0;
    virtual void visit(var_def& def) = 0;
    virtual void visit(fn_def& def) = 0;
};

}


#endif