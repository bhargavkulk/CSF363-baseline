#ifndef PARSER_UTIL_HH
#define PARSER_UTIL_HH

#include <string>
#include <vector>

#include "ast.hh"

/**
    Intermediate strcuct used by bison
*/
struct ParserValue {
    std::string lexeme;

    Node *node;
    NodeStmts *stmts;
};

#endif