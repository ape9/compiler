
#include "codegen.h"
#include "common.h"
#include "ast.h"
#include <fstream>

namespace frontend {

#define GEN(data) 

struct CodegenImpl {

    std::ofstream _file;

    CodegenImpl(const std::string& outFile) {
        _file = std::ofstream(outFile);
    } 

    template <class Line, class ...Args>
    void write(const Line& line, Args... args) {
        (_file << line << ...);
    }

    void writeLine(const std::string& line) {
        write(line, "\n");
    }

    void genHeaders() {

    }

    void genDeclarations() {

    }
    void genFuncDefinitions() {

    }
    
    void genVariable(std::unique_ptr<Assignment> assignment) {
        write(assignment->name);
        write("=");
        writeLine(assignment->value);
    }
};

}