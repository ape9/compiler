#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <string>
#include <map>
#include <fstream>
#include "location.h"

#ifdef DEBUG
#define DPRINT(x) std::cout << x << '\n';
#endif

namespace utils {

struct CompilerOptions {

};

enum class logging_level {
    DEBUG, INFO, WARNING, ERROR
};

std::map<logging_level, std::string> LOGLEVELSTR = {
    { logging_level::DEBUG, "DEBUG"}, 
    { logging_level::INFO, "INFO" }, 
    { logging_level::WARNING, "WARNING" }, 
    { logging_level::ERROR, "ERROR" }
};

enum class logging_output {
    STDOUT, STDERR, FILE
};

struct log {
    log() = default;
    log(const Location& loc, 
        const std::string& msg, 
        logging_level lvl)
        : location(loc), 
        message(msg),
        level(lvl) {}

    friend std::ostream& operator<<(std::ostream& os, const log& l) {
        os << "[" << LOGLEVELSTR[l.level] << "]" 
           << " in file " << l.location._fileName
           << " row " << l.location._row << " col " << l.location._col 
           << ": " << l.message;
        return os;
    }

    Location location;
    std::string message;
    logging_level level;
};

struct logger {
    static void debug(const Location& loc, const std::string& msg) {
        if (level != logging_level::DEBUG) {
            return;
        }
        logs.push_back(log(loc, msg, logging_level::DEBUG));
    }

    static void info(const Location& loc, const std::string& msg) {
        if (level == logging_level::DEBUG) {
            return;
        }
        logs.push_back(log(loc, msg, logging_level::INFO));
    }

    static void warn(const Location& loc, const std::string& msg) {
        if (level == logging_level::INFO || level == logging_level::DEBUG) {
            return;
        }
        logs.push_back(log(loc, msg, logging_level::WARNING));
        warning_count++;
    }
    
    static void error(const Location& loc, const std::string& msg) {
        if (level == logging_level::ERROR) {
            logs.push_back(log(loc, msg, logging_level::ERROR));
            error_count++;
        }
    }

    static void do_log() {
        for (auto& msg : logs) {
            std::cout << msg << '\n';
        }
        std::cout << error_count << " error(s).\n";
        std::cout << warning_count << " warning(s).\n";
    }

    static inline logging_level level{ logging_level::ERROR };
    static inline logging_output output_dest{ logging_output::STDOUT };
    static inline std::string outfile{ "logs.txt" };
    static inline std::vector<log> logs{};
    static inline int error_count{ 0 };
    static inline int warning_count{ 0 };
};

}



#endif