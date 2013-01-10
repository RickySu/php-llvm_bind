#include "llvm.h"

using namespace std;
using namespace llvm;

void MakeErrorInfo(SMDiagnostic& err,std::string &output)
{
    std::ostringstream stringStream;
    std::string errMsg = err.getMessage();
    std::string errLineContents = err.getLineContents();
    int errLineNo = err.getLineNo(), errColNo = err.getColumnNo();
    stringStream << "Error Message: " << errMsg << std::endl;
    stringStream << "Error Line number: " << errLineNo << ". Column number: "<< errColNo <<  std::endl;
    output = stringStream.str();
}

/*
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
*/
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

int llvm_callFunc(LLVMRESOURCE _Resource,const char *name,size_t name_length,char *errormsg,size_t errormsg_size)
{    
    std::string funcName,errorMessage;
    SMDiagnostic error;
    Module *m;
    funcName.assign(name,name_length);
    LLVMResource *Resource = (LLVMResource *) _Resource;
    ExecutionEngine *ee = Resource->getExecutionEngine();
    
    Function* func = ee->FindFunctionNamed(funcName.c_str());
    if(func==NULL){
        return false;
    }
    void(*call)()=(void(*)())ee->getPointerToFunction(func);
    call();
    return true;
}

size_t llvm_compileAssembly(LLVMRESOURCE _Resource,char *Buffer,size_t size,char *Output,size_t output_size,char *errormsg,size_t errormsg_size)
{    
    std::string str,bitcodeString,errorMessage;    
    SMDiagnostic error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;
    
    MemoryBuffer *Mem=MemoryBuffer::getMemBuffer(StringRef(Buffer,size),"",false);
    m=ParseAssembly(Mem, 0, error, Resource->getContext());
    if(m==NULL){
        MakeErrorInfo(error,errorMessage);
        errorMessage.copy(errormsg,errormsg_size);
        return 0;
    }
    raw_string_ostream stream(str);
    WriteBitcodeToFile(m,stream);
    bitcodeString=stream.str();
    if(bitcodeString.length() > output_size){
        errorMessage = "output buffer is too small!";
        errorMessage.copy(errormsg,errormsg_size);
        return 0;
    }
    bitcodeString.copy(Output,bitcodeString.length());
    return bitcodeString.length();
}

int llvm_loadBitcode(LLVMRESOURCE _Resource,char *Buffer,size_t size,char *errormsg,size_t errormsg_size)
{
    string error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;
    ExecutionEngine *ee = Resource->getExecutionEngine();
    MemoryBuffer *Mem=MemoryBuffer::getMemBuffer(StringRef(Buffer,size),"",false);
    m=ParseBitcodeFile(Mem, Resource->getContext(), &error);
    if(m==NULL){
        error.copy(errormsg,errormsg_size);
        return 0;
    }
    if(Resource->LinkModule(m,&error)){
        error.copy(errormsg,errormsg_size);
        return 0;    
    }
    //ee->addModule(m);
    return 1;
}
