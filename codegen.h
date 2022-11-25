#ifndef CODEGEN_H_
#define CODEGEN_H_
#include "common.h"

class Codegenerator {
public:
    Codegenerator();
    Codegenerator(const std::string& outFile);
    ~Codegenerator();

    void generate();

private:
    void genDeclarations();
    void genFuncDefinitions();

private:

};



#endif