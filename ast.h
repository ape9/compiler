#ifndef AST_H_
#define AST_H_

#include "common.h"
#include "visitor.h"
#include "value.h"

namespace frontend {

enum class node_kind {
    EXPR,
    NUMBER,
    BINEXPR,
    STMT,
    EXPRSTMT,
    VARDEF,
    FNDEF,
    FNARGS
}; 

std::map<node_kind, std::string> node_kind_to_str = {
    { node_kind::EXPR, "EXPR" },
    { node_kind::STMT, "STMT" },
    { node_kind::VARDEF, "VARDEF" }
};


class ast_node {
public:
    ast_node() = default;
    ast_node(const ast_node&) = delete;
    ast_node(ast_node&&) = delete;
    
    void accept(Visitor& v) {
        v.visit(*this);
    }

    inline node_kind kind() const { return _kind; }
    const utils::Location& location() const { return _location; }

protected:
    explicit ast_node(node_kind kind, utils::Location&& loc) 
    : _kind(kind), _location(std::move(loc)) {
        utils::logger::debug(_location, "AST node created: " + node_kind_to_str[kind]);
    }

private:
    node_kind _kind;
    utils::Location _location;
};

class expression : public ast_node {
public:
    expression() : ast_node(node_kind::EXPR) {}
    virtual ~expression() = default;


};

struct number : public expression {
    number(const std::string& val) 
        : value(val) {}
    
    std::string value;
};

enum class bin_expr_op {
    PLUS, 
    MINUS,
    MUL,
    DIV
};

class bin_expr final : public expression {
public:
    bin_expr(
        std::unique_ptr<expression> left,
        std::unique_ptr<expression> right,
        bin_expr_op op
    ) : _left(std::move(left)),
        _right(std::move(right)),
        _op(op) {}

    const expression& left() const { return *_left; }
    const expression& right() const { return *_right; }
    const bin_expr_op& op() const { return _op; }

private:
    std::unique_ptr<expression> _left; 
    std::unique_ptr<expression> _right;
    bin_expr_op _op;
};

class statement : public ast_node {
public:
    statement() : ast_node(node_kind::STMT) {}
    statement(node_kind kind) : ast_node(kind) {}
    virtual ~statement() = default;
    void accept(Visitor& v) override;
};

class expression_statement : public statement {
public:
    expression_statement(std::unique_ptr<expression> expr) 
        : statement(node_kind::EXPRSTMT), _expr(std::move(expr)) {}

    void accept(Visitor& v) override;

    const expression& expr() const { return *_expr; }
    expression& expr() { return *_expr; }

private:
    std::unique_ptr<expression> _expr;
}; 

// var_def: foo = 100
struct var_def : public statement {
    var_def(
        const std::string& nam, 
        std::unique_ptr<expression> val,
        const utils::Location& loc
    ) : name(nam), value(std::move(val)), location(loc) 
    {
        utils::logger::debug(location, "Init var_def " + name);
    }

    // name of the variable
    std::string name;

    // value as expression
    std::unique_ptr<expression> value;

    utils::Location location;

};

class fn_args : public statement {
public:
    fn_args() {}
};

class fn_def : public statement {
    fn_def(const std::string& nam, 
        //std::unique_ptr<fn_args> a,
        std::vector<std::unique_ptr<statement>> b)
        : name(nam), body(std::move(b)) 
    {
        utils::logger::debug(location, "Init fn_def " + name);
    }

    std::string name;
    std::vector<std::unique_ptr<fn_args>> args;
    std::vector<std::unique_ptr<statement>> body;
    //std::unique_ptr<expression> retval;
    utils::Location location;
    
};

class if_statement final : public statement {
public:
    if_statement(
        std::unique_ptr<expression> condition, 
        std::unique_ptr<statement> else_block
    ) {}


};



}

#endif