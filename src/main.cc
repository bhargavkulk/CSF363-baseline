#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <fstream>

#include "parser.hh"
#include "ast.hh"
#include "ccodegen.hh"

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
		CCompiler compiler;
		compiler.generate((Node *)final_values);
        if(output) {
            std::ofstream fout(argv[2]);
            compiler.write(fout);
            fout.close();
        } else
            compiler.write(std::cout);
	}
	else
	 	std::cerr << "empty program";

	fclose(source);
}


void lexer_output() {
    int x;
        while ((x = yylex()) != 0) {   
            switch (x) {   
            case TPLUS: 
                printf("TPLUS\n");
                break;
            case TDASH:
                printf("TDASH\n");
                break;
            case TSTAR:
                printf("TSTAR\n");
                break;
            case TSLASH:
                printf("TSLASH\n");
                break;
            case TINT_LIT:
                printf("TINT_LIT %s\n", yytext);
                break;
            case TIDENT:
                printf("TIDENT %s\n", yytext);
                break;
            case TLET:
                printf("TLET\n");
                break;
            case TDBG:
                printf("TDBG\n");
                break;
            case TSCOL:
                printf("TSCOL\n");
                break;
            case TLPAREN:
                printf("TLPAREN\n");
                break;
            case TRPAREN:
                printf("TRPAREN\n");
                break;
            case TEQUAL:
                printf("TEQUAL\n");
                break;
            default:
                printf("Other: %d\n", x); 
                break;
            }   
        }
}