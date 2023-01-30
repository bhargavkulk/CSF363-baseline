#ifndef LLVMCODEGEN_HH
#define LLVMCODEGEN_HH

#include <llvm/IR/Instructions.h>
#include <string>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <unordered_map>
#include "ast.hh"

using namespace llvm;

/**
    Compiler struct to store state of the LLVM IRBuilder.
    The `compile` method recursively calls the llvmcodegen method for a given 
    `Node`.
*/
struct LLVMCompiler {
    LLVMContext *context;
    IRBuilder<> builder;
    Module module;
    std::unordered_map<std::string, AllocaInst*> locals;
    
    LLVMCompiler(LLVMContext *context, std::string file_name) : 
        context(context), builder(*context), module(file_name, *context) {}
    
    void compile(Node *root);
    void dump();
    void write(std::string file_name);
};

#endif