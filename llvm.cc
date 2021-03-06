#include "llvm.h"
using namespace std;
using namespace llvm;

void MakeErrorInfo(SMDiagnostic& err, std::string &output) {
    std::ostringstream stringStream;
    std::string errMsg = err.getMessage();
    std::string errLineContents = err.getLineContents();
    int errLineNo = err.getLineNo(), errColNo = err.getColumnNo();
    stringStream << "Error Message: " << errMsg << std::endl;
    stringStream << "Error Line number: " << errLineNo << ". Column number: " << errColNo << std::endl;
    output = stringStream.str();
}

void llvm_init() {
    InitializeNativeTarget();
    llvm_start_multithreaded();
}

LLVMRESOURCE llvm_newResource() {
    LLVMResource *Resource = new LLVMResource();
    return (LLVMRESOURCE) Resource;
}

void llvm_freeResource(LLVMRESOURCE Resource) {
    delete (LLVMResource *) Resource;
}

void *llvm_callFunc(LLVMRESOURCE _Resource, const char *name, size_t name_length, void **argv, int argc, char *errormsg, size_t errormsg_size) {
    fCall_t call;
    call = llvm_getFunc(_Resource, name);
    if(call == NULL){
        return false;
    }
    return call(argv, argc);
}

fCall_t llvm_getFunc(LLVMRESOURCE _Resource, const char *name){
    std::string funcName, errorMessage;
    Module *m;
//    funcName.assign(name, strlen(name));
    LLVMResource *Resource = (LLVMResource *) _Resource;
    ExecutionEngine *ee = Resource->getExecutionEngine();
//funcName.c_str()
    Function* func = ee->FindFunctionNamed(name);
    if (func == NULL) {
        return NULL;
    }
    return (fCall_t) ee->getPointerToFunction(func);
}

size_t llvm_compileAssembly(LLVMRESOURCE _Resource, char *Buffer, size_t size, char *Output, size_t output_size, char *errormsg, size_t errormsg_size, int optimize_level) {
    std::string str, bitcodeString, errorMessage;
    SMDiagnostic error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;

    MemoryBuffer *Mem = MemoryBuffer::getMemBuffer(StringRef(Buffer, size), "", false);
    m = ParseAssembly(Mem, 0, error, Resource->getContext());
    if (m == NULL) {
        MakeErrorInfo(error, errorMessage);
        errorMessage.copy(errormsg, errormsg_size);
        return 0;
    }
    if (optimize_level) {
        optimizeModule(m, optimize_level);
    }
    raw_string_ostream stream(str);
    WriteBitcodeToFile(m, stream);
    bitcodeString = stream.str();
    if (bitcodeString.length() > output_size) {
        errorMessage = "output buffer is too small!";
        errorMessage.copy(errormsg, errormsg_size);
        return 0;
    }
    bitcodeString.copy(Output, bitcodeString.length());
    return bitcodeString.length();
}

int llvm_loadBitcode(LLVMRESOURCE _Resource, char *Buffer, size_t size, char *errormsg, size_t errormsg_size) {
    string error;
    Module *m;
    LLVMResource *Resource = (LLVMResource *) _Resource;
//    ExecutionEngine *ee = Resource->getExecutionEngine();
    MemoryBuffer *Mem = MemoryBuffer::getMemBuffer(StringRef(Buffer, size), "", false);
    m = ParseBitcodeFile(Mem, Resource->getContext(), &error);
    if (m == NULL) {
        error.copy(errormsg, errormsg_size);
        return 0;
    }
    if (Resource->LinkModule(m, &error)) {
        error.copy(errormsg, errormsg_size);
        return 0;
    }

    return 1;
}
