
#include "codegen.h"
#include "common.h"
#include "ast.h"
#include "visitor.h"
#include <fstream>

namespace frontend {

struct Codegen::Impl : public Visitor {

    std::ofstream _file;

    Impl(const std::string& outFile) {
        _file = std::ofstream(outFile);
    } 

    ~Impl() {
        _file.close();
    }

    void generate(std::vector<std::unique_ptr<ast_node>> ast) {
        for (auto& node : ast) {
            node->accept(*this);
        }
    }

    template <class Line, class ...Args>
    void write(const Line& line, Args&&... args) {
        (_file << line << std::move(...));
    }

    void visit(ast_node& ast) override {}
    void visit(expression& expr) override {}
    void visit(statement& stmt) override {}

    void visit(var_def& var) override {
        write(var.name, " = ");
        var.value->accept(*this);
    }   

    void visit(std::unique_ptr<fn_def> fn) {
        
    }

};

Codegen::Codegen(const std::string& fileName) {
    _pImpl = std::make_unique<Impl>(fileName);
}

void Codegen::generate() {
    _pImpl->generate();
}

}
