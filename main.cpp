#include "common.h"
#include "lexer.h"
#include "parser.h"

using namespace frontend;

struct compiler_options {
    // defines name for the output binary
    std::string out_name;

    // if true, keeps the generated C source file
    bool keep_c_source;
};


void handle_args(int argc, char **argv) {
    if (argc < 2) {
        utils::logger::instant_print = false;
        utils::logger::level = utils::logging_level::WARNING;
        utils::logger::output_dest = utils::logging_output::FILE;
    }
    else {
        utils::logger::output_dest = utils::logging_output::FILE;
        for (auto i = 1; i < argc; i++) {
            if (strcmp(argv[i], "debug") == 0) {
                utils::logger::level = utils::logging_level::DEBUG;
            }
            if (strcmp(argv[i], "info") == 0) {
                utils::logger::level = utils::logging_level::INFO;
            }
            if (strcmp(argv[i], "warning") == 0) {
                utils::logger::level = utils::logging_level::WARNING;
            }
            if (strcmp(argv[i], "error") == 0) {
                utils::logger::level = utils::logging_level::ERROR;
            }
        }
    }
}

int main(int argc, char **argv) {

    handle_args(argc, argv);

    Lexer l("test.txt");
    auto tokens = l.createTokens();
    //Lexer::print_tokens(std::move(tokens));
    parser p(std::move(tokens));
    auto a = p.parse();
    std::cout << "PARSED ast: " << a.size() << '\n';
    
    // Write logs
    utils::logger::do_log();

    return 0;
}