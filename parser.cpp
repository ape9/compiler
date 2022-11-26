#include "parser.h"


namespace frontend {

struct parsing_state {
    parsing_state() : location(utils::Location()) {}
    parsing_state(const utils::Location& l, int d) 
        : location(l), depth(d) {}

    utils::Location location;
    int depth;

    std::ostream& operator<<(std::ostream& os) {
        std::cout << "Parsing state " << location._fileName << " depth: " 
            << depth << '\n';
        return os;
    }

};

template <typename T>
using uptr = std::unique_ptr<T>;

class parser::impl {
public:
    impl() = default;
    impl(std::vector<Token>& tokens) 
        : _tokens(tokens) {}

    std::vector<uptr<ast_node>> parse_impl();

private:
    uptr<expression> parse_expression();
    uptr<statement> parse_statement();
    uptr<var_def> parse_var_def();
    uptr<fn_args> parse_fn_args();
    uptr<fn_def> parse_fn_def();

private:
    parsing_state _state;
    std::vector<Token> _tokens;
};

//uptr<expression> impl::

parser::parser(const std::vector<Token>& toks) {
    _pImpl = std::make_unique<impl>(toks);
}

std::vector<std::unique_ptr<ast_node>> parser::parse() {
    return _pImpl->parse_impl();
}

}