#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <vector>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "parser.hh"
#include "ast.hh"
#include "llvmcodegen.hh"

extern FILE *yyin;
extern int yylex();
extern char* yytext;

NodeStmts* final_values;

void lexer_output();

int main(int argc, char* argv[]) {

	if(argc == 1) {
		std::cerr << "Usage:\n";
		std::cerr << "`base <file_name>`, to compile file and output to stdout\n";
		std::cerr << "`base <file_name> <output>`, to compile file and output to <output>\n";
        exit(1);
    }

    bool output = argc == 3;

	std::string file_name(argv[1]);
	FILE *source = fopen(argv[1], "r");

    if(!source) {
        std::cerr << "File does not exists.\n";
        exit(1);
    }

	yyin = source;

    final_values = nullptr;
	yyparse();

	if(final_values) {
		std::cout << final_values->to_string() << std::endl;
        llvm::LLVMContext context;
		LLVMCompiler compiler(&context, "base");
		compiler.compile(final_values);
        if(output) {
            compiler.write(std::string(argv[2]));
        } else
            compiler.dump();
	}
	else
	 	std::cerr << "empty program";

	fclose(source);

    return 0;
}