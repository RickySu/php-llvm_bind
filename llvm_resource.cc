#include "llvm.h"

using namespace llvm;

LLVMResource::LLVMResource()
{
    MainModule=new Module("main",context);
    ee=ExecutionEngine::createJIT(MainModule,0,0,CodeGenOpt::Aggressive);
}

LLVMResource::~LLVMResource()
{
    delete ee;
}

LLVMContext & LLVMResource::getContext()
{
    return context;
}

ExecutionEngine *LLVMResource::getExecutionEngine()
{
    return ee;
}

bool LLVMResource::LinkModule(llvm::Module *Module,std::string *ErrorMsg)
{
     return Linker::LinkModules(MainModule,Module,0,ErrorMsg);
}