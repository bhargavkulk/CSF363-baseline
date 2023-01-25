#ifndef SYMBOL_HH
#define SYMBOL_HH

#include <set>
#include <string>
#include "ast.hh"


// Basic symbol table, just keeping track of prior existence and nothing else
struct SymbolTable {
    std::set<std::string> table;

    bool contains(std::string key);
    void insert(std::string key);
};

#endif