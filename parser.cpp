#include "parser.h"


namespace frontend {

struct parsing_state {
    parsing_state() : location(utils::Location()) {}
    parsing_state(const utils::Location& l, int d) 
        : location(l), depth(d) {}

    utils::Location location;
    int depth;
    Token current_token;

    std::ostream& operator<<(std::ostream& os) {
        std::cout << "Parsing state " << location._fileName << " depth: " 
            << depth << '\n';
        return os;
    }
};

template <typename T>
using uptr = std::unique_ptr<T>;

class parser::parser_impl {
public:
    parser_impl() = default;
    parser_impl(std::vector<Token>& tokens) 
        : _tokens(tokens) {}

    std::vector<uptr<ast_node>> parse_impl();

    uptr<expression> parse_expression();
    uptr<number> parse_number();
    uptr<bin_expr> parse_bin_expr();
    uptr<statement> parse_statement();
    uptr<var_def> parse_var_def();
    uptr<fn_args> parse_fn_args();
    uptr<fn_def> parse_fn_def();

    inline TokenType cur_token_type() const {
        return _state.current_token._typ;
    }

    inline Token cur_token() const { 
        return _state.current_token; 
    }

    inline utils::Location cur_location() const {
        return _state.location;
    }

    Token peek() {
        
    }
    
    void next() {
        
    }

    bool maybe_expression(const Token& tok) const {
        auto typ = tok.type();
        return (typ == TokenType::NUMBER || 
                typ == TokenType::IDENTIFIER);
    }

    void skip_until_type(TokenType typ) {
        while (cur_token_type() != typ) {
            next();
        }
    }

private:
    parsing_state _state;
    std::vector<Token> _tokens;
};

uptr<statement> 
parser::parser_impl::parse_statement() {
    switch (cur_token_type()) {
        case TokenType::IDENTIFIER: {
            auto next_tok = peek();
            if (next_tok.type() == TokenType::EQUAL) {
                // Variable definition
                return parse_var_def();
            }   
            else {
                // "expression statement"
            }
            break;
        }
        default:
            assert(false);
            break;
    }
}

uptr<var_def> 
parser::parser_impl::parse_var_def() {
    // at ident
    std::string name = cur_token()._value;
    next();
    next();
    // at expression
    auto value = parse_expression();

    return std::make_unique<var_def>(
        name, std::move(value), cur_location()
    );
}

uptr<fn_def> 
parser::parser_impl::parse_fn_def() {
}

uptr<expression> 
parser::parser_impl::parse_expression() {
    switch(cur_token_type()) {
        case TokenType::NUMBER:
            return parse_number();
        default:
            assert(false);
            break;
    }

    return nullptr;
}

uptr<number> 
parser::parser_impl::parse_number() {
    // at number
    std::string value = cur_token().value();
    next();
    return std::make_unique<number>(value);
}

uptr<bin_expr> 
parser::parser_impl::parse_bin_expr() {

}

std::vector<uptr<ast_node>> 
parser::parser_impl::parse_impl() {
    std::vector<uptr<ast_node>> ast;

    while (cur_token().type() != TokenType::ENDTOKEN) {
        ast.push_back(parse_statement());
    }

    return ast;
}

parser::parser(const std::vector<Token>& toks) {
    _pImpl = std::make_unique<parser_impl>(toks);
}

std::vector<uptr<ast_node>> parser::parse() {
    return _pImpl->parse_impl();
}

}