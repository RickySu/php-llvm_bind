#include "llvm.h"

using namespace std;
using namespace llvm;

MakeErrorInfo(SMDiagnostic& err)
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

LLVMRESOURCE llvm_newResource()
{
    LLVMResource *Resource = new LLVMResource();
    return (LLVMRESOURCE) Resource;
}

void llvm_freeResource(LLVMRESOURCE Resource)
{
    delete (LLVMResource *)Resource;
}

size_t llvm_compileAssembly(LLVMRESOURCE _Resource,char *Buffer,size_t size,char **Output,const char **errormsg)
{    
    std::string str,bitcodeString;
    SMDiagnostic error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;
    MemoryBuffer *Mem=MemoryBuffer::getMemBuffer(StringRef(Buffer,size),"",false);
    m=ParseAssembly(Mem, 0, error, Resource->getContext());
    if(m==NULL){
        return 0;
    }
    raw_string_ostream stream(str);
    WriteBitcodeToFile(m,stream);
    bitcodeString=stream.str();
    *Output=(char*)emalloc(bitcodeString.length());
    bitcodeString.copy(*Output,bitcodeString.length());    
    return bitcodeString.length();
}

int llvm_loadBitcode(LLVMRESOURCE _Resource,char *Buffer,size_t size,const char **errormsg)
{
    string error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;
    ExecutionEngine *ee = Resource->getExecutionEngine();
    MemoryBuffer *Mem=MemoryBuffer::getMemBuffer(StringRef(Buffer,size),"",false);
    m=ParseBitcodeFile(Mem, Resource->getContext(), &error);
    if( error.length() > 0){
        *errormsg=error.c_str();
        return 1;
    }
    ee->addModule(m);
    return 0;
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
