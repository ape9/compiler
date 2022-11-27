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

namespace utils {

struct CompilerOptions {
    // TODO
};

enum class logging_level {
    DEBUG, INFO, WARNING, ERROR
};

static inline std::map<logging_level, std::string> LOGLEVELSTR = {
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
        if (instant_print) {
            std::cout << msg << '\n';
        }
        logs.push_back(log(loc, msg, logging_level::DEBUG));
    }

    static void info(const Location& loc, const std::string& msg) {
        if (level == logging_level::DEBUG) {
            return;
        }
        if (instant_print) {
            std::cout << msg << '\n';
        }
        logs.push_back(log(loc, msg, logging_level::INFO));
    }

    static void warn(const Location& loc, const std::string& msg) {
        if (level == logging_level::INFO || level == logging_level::DEBUG) {
            return;
        }
        if (instant_print) {
            std::cout << msg << '\n';
        }
        logs.push_back(log(loc, msg, logging_level::WARNING));
        warning_count++;
    }
    
    static void error(const Location& loc, const std::string& msg) {
        if (level != logging_level::ERROR) {
            return;
        }
        if (instant_print) {
            std::cout << msg << '\n';
        }
        std::cout << "HERE!!\n";
        logs.push_back(log(loc, msg, logging_level::ERROR));
        error_count++;
    }

    static void do_log() {
        std::ofstream logfile("logs.txt");
        for (auto& msg : logs) {
            if (output_dest == logging_output::FILE) 
                logfile << msg << '\n';
            else if (output_dest == logging_output::STDOUT)
                std::cout << msg << '\n';
            else 
                std::cerr << msg << '\n';

        }
        if (error_count > 0 || warning_count > 0) {
            std::cout << error_count << " error(s).\n";
            std::cout << warning_count << " warning(s).\n";
            std::cout << "Check logs.txt for details.\n";
        }
    }

    static inline logging_level level{ logging_level::ERROR };
    static inline logging_output output_dest{ logging_output::STDOUT };
    static inline std::string outfile{ "logs.txt" };
    static inline std::vector<log> logs{};
    static inline int error_count{ 0 };
    static inline int warning_count{ 0 };
    static inline bool instant_print { false };
};


}



#endif