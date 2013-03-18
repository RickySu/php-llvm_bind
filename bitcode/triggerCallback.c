#include <stdlib.h>
typedef void (*fCall_t)(int callbackIndex, const char *argsDefine, ...);

void *callbackObj=NULL;
fCall_t LLVMBind_triggerCallback=NULL;

void LLVMBind_setTriggerCallbackEntryPointet(void *object, fCall_t call){
    if(callbackObj){
        return;
    }
    callbackObj=object;
    LLVMBind_triggerCallback=call;
}
