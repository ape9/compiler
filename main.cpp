#include "common.h"

int main(int argc, char **argv) {
    utils::Location loc("test.c", 95, 22);
    utils::logger::level = utils::logging_level::ERROR;
    utils::logger::error(loc, "WTF IS THIS!?!?");
    utils::logger::do_log();
    return 0;
}