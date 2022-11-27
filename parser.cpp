#include "parser.h"
#include "lexer.h"

namespace frontend {

template <typename T>
using uptr = std::unique_ptr<T>;

struct parsing_state {
    parsing_state() = default;
    parsing_state(std::vector<uptr<Token>> toks) 
        :  tokens(std::move(toks)), count(0)
    {
        location = tokens[0]->_location;
        current_token = *tokens[0];
    } 

    std::vector<uptr<Token>> tokens;
    int count;
    utils::Location location;
    Token current_token;
};

class parser::parser_impl {
public:
    parser_impl() = default;
    parser_impl(std::vector<uptr<Token>> tokens) {
        _state = parsing_state(std::move(tokens));
    }
        //: _state(std::move(tokens)) {}

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
        Token tok;
        if (_state.count < _state.tokens.size()) {
            tok = *(_state.tokens[_state.count + 1]);
        }
        return tok;
    }
    
    void next() {
        if (_state.count <= _state.tokens.size()) {
            _state.count++;
            _state.current_token = *(_state.tokens[_state.count]);
            _state.location = _state.tokens[_state.count]->_location;
        }
    }

    bool maybe_expression(const Token& tok) const {
        auto typ = tok.type();
        return (typ == TokenType::NUMBER || 
                typ == TokenType::IDENTIFIER);
    }

    void skip_until_type(TokenType typ) {
        while (cur_token_type() != typ) { next(); }
    }

private:
    parsing_state _state;
};

uptr<statement> 
parser::parser_impl::parse_statement() {
    switch (cur_token_type()) {
        case TokenType::FN:
            // function definition
            return parse_fn_def();

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
            utils::logger::debug(cur_location(), 
                "parse_statement(): should not be here!! current token: " + std::string(cur_token().value()));
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
    if (maybe_expression(cur_token()) == false) {
        utils::logger::error(cur_location(), 
            "Parsing error: expected expression but got " + std::string(cur_token().value()));
        return nullptr;
    }
    auto value = parse_expression();

    return std::make_unique<var_def>(
        name, std::move(value), cur_location()
    );
}

uptr<fn_args> 
parser::parser_impl::parse_fn_args() {
    while (cur_token_type() != TokenType::RPAREN) {
        //if (cur_token_type() != TokenType::IDENTIFIER) {

        //}
        next();
    }
    return nullptr;
}

uptr<fn_def> 
parser::parser_impl::parse_fn_def() {
    // at fn
    next();
    if (cur_token_type() != TokenType::IDENTIFIER) {
        utils::logger::error(cur_location(), 
            "Parsing error: expected identifier but got " + std::string(cur_token().value()));
        return nullptr;
    }

    std::string name = cur_token().value();
    next();

    if (cur_token_type() != TokenType::LPAREN) {
        utils::logger::error(cur_location(), 
            "Parsing error: expected '(' but got " + std::string(cur_token().value()));
        return nullptr;
    }    

    next();

    // Go through arguments:
    uptr<fn_args> args = parse_fn_args();

    next();
    if (cur_token_type() != TokenType::LCURLY) {
        utils::logger::error(cur_location(), 
            "Parsing error: expected '{' but got " + std::string(cur_token().value()));
        return nullptr;
    }

    next();

    // Go through function body:
    std::vector<uptr<statement>> body;
    while (cur_token_type() != TokenType::RCURLY) {
        body.push_back(parse_statement());
        
    }

    // Move from '}'
    next(); 
    return std::make_unique<fn_def>(name, std::move(body));
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
        utils::logger::debug(cur_location(), "Parse loop ");
        ast.push_back(parse_statement());
    }

    return ast;
}

parser::parser(std::vector<uptr<Token>> toks) {
    _pImpl = std::make_unique<parser_impl>(std::move(toks));
}

parser::~parser() {}

std::vector<uptr<ast_node>> parser::parse() {
    utils::logger::debug(_pImpl->cur_location(), "in parser::parse()");
    return _pImpl->parse_impl();
}

}