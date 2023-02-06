## Parser
Parsing is the process of matching grammar symbols to elements in the input data, according to the rules of the grammar.

The parser obtains a sequence of tokens from the lexical analyzer, and recognizes it's structure in the form of a parse tree.
Tree nodes represent symbols of the grammar (non-terminals or terminals), and tree edges represent derivation steps.

## Bison and parser.yy 
Bison is a general purpose `parser generator` that converts a grammar description into a C program to parse that grammar . 
