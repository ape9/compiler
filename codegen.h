#ifndef CODEGEN_H_
#define CODEGEN_H_
#include "common.h"
#include "ast.h"

namespace frontend {


class Codegen {
public:
    Codegen();
    Codegen(const std::string& outFile);

    void generate();

private:
    class CodegenImpl;
    CodegenImpl *_pImpl;
};

}


#endif