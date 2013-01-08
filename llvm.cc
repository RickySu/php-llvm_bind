#include "llvm.h"

using namespace std;
using namespace llvm;

void displayErrorInfo(SMDiagnostic& err)
{
    std::string errFileName = err.getFilename();
    std::string errMsg = err.getMessage();
    std::string errLineContents = err.getLineContents();
    int errLineNo = err.getLineNo(), errColNo = err.getColumnNo();
    std::cout << "Error File Name: "<< errFileName << std::endl;
    std::cout << "Error Message: " << errMsg << std::endl;
    std::cout << "Error Line number: " << errLineNo << ". Column number: "<< errColNo <<  std::endl;
}

Module *LoadASFromFile(const char * filename,LLVMContext &context){
    string bcfile(filename);
    bcfile=bcfile+".bc";
    SMDiagnostic error;
    OwningPtr<MemoryBuffer> Buffer;
    MemoryBuffer::getFile(filename, Buffer);                                                                                    
    Module *m=ParseAssembly(Buffer.take(),0, error, context);
    std::string ErrorInfo;
    raw_fd_ostream os(bcfile.c_str(), ErrorInfo);
    WriteBitcodeToFile(m, os);
    displayErrorInfo(error);
    return m;
}

Module *LoadBitCodeFromFile(const char * filename,LLVMContext &context){
    string error;    
    OwningPtr<MemoryBuffer> Buffer;
    MemoryBuffer::getFile(filename, Buffer);                                                                                    
    return ParseBitcodeFile(Buffer.get(), context, &error);
}

void llvm_init()
{
    InitializeNativeTarget();
    llvm_start_multithreaded();
}

void *llvm_newResource()
{
    LLVMResource *Resource = new LLVMResource();
    return NULL;
}

void llvm_freeResource(void*Resource)
{
    delete (LLVMResource*)Resource;
}

int load()
{
    const char * filename="a.bc";
    LLVMContext context;
    Module *m = LoadBitCodeFromFile(filename , context);
//    Module *m = LoadASFromFile(filename , context);
    ExecutionEngine *ee = ExecutionEngine::create(m);

    Function* func = ee->FindFunctionNamed("main");

    void (*mainFunc)() = (void (*)()) ee->getPointerToFunction(func);
//    typedef void (*PFN)();
//    PFN pfn = reinterpret_cast<PFN>();
//    pfn();
    mainFunc();
    delete ee;
    return 0;
}
