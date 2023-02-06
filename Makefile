LEXER:= lexer
PARSER:= parser

FLAGS:= -Wall -Wextra -Wno-unused-function -Wunused-parameter -Iinclude -std=c++17
LLVMFLAGS:= `llvm-config --cxxflags`
LLVMLIB:= `llvm-config --ldflags --system-libs --libs core`

SRC:= src/$(PARSER).cc src/$(LEXER).cc $(wildcard src/*.cc)
OBJ:= $(patsubst src/%.cc,obj/%.o,$(SRC))
BIN:= bin/base
BEBIN:= bin/test

.PHONY: clean compiler program

compiler: $(BIN)

$(BIN): $(OBJ)
	@echo "Linking..."
	@echo "mkdir -p bin"; mkdir -p bin
	@echo "clang++ $^ -o $@ $(LLVMLIB)"; clang++ $^ -o $@ $(LLVMLIB)

obj/%.o: src/%.cc
	@echo "Compiling..."
	@echo "mkdir -p obj"; mkdir -p obj
	@echo "clang++ $(FLAGS) $(LLVMFLAGS) -c $^ -o $@"; clang++ $(FLAGS) $(LLVMFLAGS) -c $^ -o $@

src/$(PARSER).cc: src/$(PARSER).yy
	@echo "Running bison..."
	@echo "bison src/$(PARSER).yy -do src/$(PARSER).cc"; bison src/$(PARSER).yy -do src/$(PARSER).cc
	@echo "mv -f src/$(PARSER).hh include/$(PARSER).hh"; mv -f src/$(PARSER).hh include/$(PARSER).hh

src/$(LEXER).cc: src/$(LEXER).lex
	@echo "Running flex..."
	@echo "flex -o src/$(LEXER).cc src/$(LEXER).lex"; flex -o src/$(LEXER).cc src/$(LEXER).lex

clean:
	@echo "Cleaning files..."
	rm -rf src/$(LEXER).cc src/$(PARSER).cc include/$(PARSER).hh obj bin

program: $(BIN) $(BEBIN)

$(BEBIN): obj/test.o obj/runtime_lib.o
	@echo "Building executable..."
	@echo "clang++ obj/test.o obj/runtime_lib.o -o $(BEBIN)"; clang++ obj/test.o obj/runtime_lib.o -o $(BEBIN)

obj/test.o: bin/test.bc
	@echo "Compiling bitcode to obj..."
	@echo "llc -filetype=obj bin/test.bc -o obj/test.o"; llc -filetype=obj bin/test.bc -o obj/test.o

bin/test.bc: test.be
	@echo "Compiling test.be to LLVM bitcode..."
	@echo "./$(BIN) test.be bin/test.bc"; ./$(BIN) test.be bin/test.bc

obj/runtime_lib.o: runtime/runtime_lib.cc
	@echo "Building runtime library..."
	@echo "clang++ -c runtime/runtime_lib.cc -o obj/runtime_lib.o"; clang++ -c runtime/runtime_lib.cc -o obj/runtime_lib.o
