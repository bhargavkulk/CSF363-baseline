#ifndef AST_HH
#define AST_HH

#include <string>
#include <vector>

struct CCompiler;

struct Node {
    enum Type {
        BIN_OP, INT_LIT, STMTS, ASSN, DBG, IDENT
    } type;

    virtual std::string to_string() = 0;
    virtual void c_codegen(CCompiler *compiler) = 0;
};

struct NodeBinOp : public Node {
    enum Op {
        PLUS, MINUS, MULT, DIV
    } op;

    Node *left, *right;

    NodeBinOp(Op op, Node *leftptr, Node *rightptr);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

struct NodeInt : public Node {
    int value;

    NodeInt(int val);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

struct NodeStmts : public Node {
    std::vector<Node*> list;

    NodeStmts();
    void push_back(Node *node);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

struct NodeAssn : public Node {
    std::string identifier;
    Node *expression;

    NodeAssn(std::string id, Node *expr);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

struct NodeDebug : public Node {
    Node *expression;

    NodeDebug(Node *expr);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

struct NodeIdent : public Node {
    std::string identifier;

    NodeIdent(std::string ident);
    std::string to_string();
    void c_codegen(CCompiler *compiler);
};

#endif