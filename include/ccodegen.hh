#ifndef CCODEGEN_HH
#define CCODEGEN_HH

#include <string>
#include "ast.hh"

struct CCompiler {
    std::string output;
    void generate(Node *root);
    void insert(std::string);
    void write(std::ostream &out);
};

#endif