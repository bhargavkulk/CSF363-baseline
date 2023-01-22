#include "ccodegen.hh"

void CCompiler::generate(Node *root) {
    output += "#include <stdio.h>\n";
    output += "int main() {\n";

    root->c_codegen(this);

    output += "return 0;\n";
    output += "}";
}

void CCompiler::insert(std::string code) {
    output += code;
}

void CCompiler::write(std::ostream &out) {
    out << output;
}

void NodeBinOp::c_codegen(CCompiler *compiler) {
    compiler->insert("(");
    left->c_codegen(compiler);
    switch(op) {
        case PLUS: compiler->insert("+"); break;
        case MINUS: compiler->insert("-"); break;
        case MULT: compiler->insert("*"); break;
        case DIV: compiler->insert("/"); break;
    }
    right->c_codegen(compiler);
    compiler->insert(")");
}

void NodeInt::c_codegen(CCompiler *compiler) {
    compiler->insert(std::to_string(value));
}

void NodeStmts::c_codegen(CCompiler *compiler) {
    for(auto stmt : list) {
        stmt->c_codegen(compiler);
    }
}

void NodeAssn::c_codegen(CCompiler *compiler) {
    compiler->insert("int " + identifier + "=");
    expression->c_codegen(compiler);
    compiler->insert(";\n");
}

void NodeDebug::c_codegen(CCompiler *compiler) {
    compiler->insert("printf(\"%d\\n\",");
    expression->c_codegen(compiler);
    compiler->insert(");\n");
}

void NodeIdent::c_codegen(CCompiler *compiler) {
    compiler->insert(identifier);
}