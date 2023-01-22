LEXER:= lexer
PARSER:= parser

FLAGS:= -Wall -Wextra -Wno-unused-function -Wunused-parameter -Iinclude -std=c++17
LLVMFLAGS:= `llvm-config --cppflags`
LLVMLIB:= `llvm-config --ldflags`

SRC:= $(wildcard src/*.cc) src/$(PARSER).cc src/$(LEXER).cc
OBJ:= $(patsubst src/%.cc,obj/%.o,$(SRC))
BIN:= bin/base

$(BIN): $(OBJ)
	@echo "mkdir -p bin"; mkdir -p bin
	@echo "clang++ $^ -o $@ $(LLVMLIB)"; clang++ $^ -o $@ $(LLVMLIB)

obj/%.o: src/%.cc
	@echo "mkdir -p obj"; mkdir -p obj
	@echo "clang++ $(FLAGS) $(LLVMFLAGS) -c $^ -o $@"; clang++ $(FLAGS) $(LLVMFLAGS) -c $^ -o $@

src/$(PARSER).cc: src/$(PARSER).yy
	@echo "bison src/$(PARSER).yy -do src/$(PARSER).cc"; bison src/$(PARSER).yy -do src/$(PARSER).cc
	@echo "mv -f src/$(PARSER).hh include/$(PARSER).hh"; mv -f src/$(PARSER).hh include/$(PARSER).hh

src/$(LEXER).cc: src/$(LEXER).lex
	@echo "flex -o src/$(LEXER).cc src/$(LEXER).lex"; flex -o src/$(LEXER).cc src/$(LEXER).lex

clean:
	rm -rf src/$(LEXER).cc src/$(PARSER).cc include/$(PARSER).hh obj bin/* test.c
