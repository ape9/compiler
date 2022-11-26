#ifndef CODEGEN_H_
#define CODEGEN_H_
#include "common.h"

namespace frontend {

class Codegen {
public:
    Codegen();
    Codegen(const std::string& outFile);

    void generate();

private:
    class Impl;
    std::unique_ptr<Impl> _pImpl;
};

}


#endif