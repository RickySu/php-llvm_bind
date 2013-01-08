#include "llvm.h"

using namespace llvm;

LLVMResource::LLVMResource()
{
    MainModule=new Module("main",context);
    ee=ExecutionEngine::createJIT(MainModule);
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
