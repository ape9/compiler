#include "common.h"
#include "lexer.h"
#include "parser.h"

using namespace frontend;

int main(int argc, char **argv) {

    utils::logger::instant_print = true;
    utils::logger::level = utils::logging_level::DEBUG;

    Lexer l("test.txt");
    auto tokens = l.createTokens();
    //Lexer::print_tokens(std::move(tokens));
    parser p(std::move(tokens));
    auto a = p.parse();
    std::cout << "PARSED: " << a.size() << '\n';
    
    // Write logs
    utils::logger::do_log();

    return 0;
}