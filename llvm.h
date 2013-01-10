#ifndef _PHP_LLVM_H_
# define _PHP_LLVM_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "default.h"

#include <string>
#include <sstream>
#include <iostream>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/system_error.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Assembly/Parser.h>
#include <llvm/Linker.h>

extern "C" {
  #include "export.h"
}

class LLVMResource{
    protected:
        llvm::LLVMContext context;
        llvm::ExecutionEngine *ee;
        llvm::Module *MainModule;
    public:
        LLVMResource();
        llvm::LLVMContext &getContext();
        llvm::ExecutionEngine *getExecutionEngine();
        bool LinkModule(llvm::Module *Module,std::string *ErrorMsg);
        ~LLVMResource();
};
  
#endif
