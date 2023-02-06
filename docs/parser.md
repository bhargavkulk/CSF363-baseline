## Parser
Parsing is the process of matching grammar symbols to elements in the input data, according to the rules of the grammar.

The parser obtains a sequence of tokens from the lexical analyzer.The parser is responsible for analyzing the syntax of the input code and constructing a parse tree. The parse tree represents the structure of the input code and is used to generate the final output.

## Bison and parser.yy 
Bison is a general-purpose parser generator that converts a grammar description (Bison Grammar Files) for an LALR(1) context-free grammar into a C program to parse that grammar. The Bison parser is a bottom-up parser. It tries, by shifts and reductions, to reduce the entire input down to a single grouping whose symbol is the grammar's start-symbol.

`parser.yy` defines the grammar and specifies the rules for constructing a parse tree of the input program. The parse tree is then used to generate intermediate code that can be executed. The symbol_table is used to keep track of declared variables.


The code starts with `%define` and `%code` blocks which provide bison with information about the global variables and functions used in the parser.

The `%token` section defines the lexical tokens used in the grammar.

The `%type` section defines the types of the non-terminal symbols in the grammar. 

The `%left` section specifies the precedence of the binary arithmetic operators. 

Tokens in line 36 will have lower precedence than those in line 37 . 
In same Line the leftmost operator will be evaluated first.  

lines 39-90 (bounded by `%%`) define the  grammar rules using BNF (Backus-Naur Form)

The `Program`  rule  is the start symbol of the grammar and defines the top-level structure of the parse tree. 
The `StmtList` rule defines a **list of statements** and the `Stmt` rule defines a **single statement**.
The `Expr` rule defines an expression in the language.

Each `rule` in the grammar is composed of one or more alternatives, separated by pipes `|`. 
Each alternative consists of a sequence of tokens and/or non-terminals, followed by an action (Inside curly braces)that is executed when that alternative is recognized. 
The actions use C++ code to construct the parse tree, with the final parse tree being stored in the global variable final_values.

The `symbol_table` is a global SymbolTable object that keeps track of the variables declared in the program. 
The `yyerror` function is called by bison when a parse error is encountered and prints an error message to standard error and exits the program.