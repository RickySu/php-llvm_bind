#include <stdio.h>
#include <stdarg.h>
typedef void (*fCall_t)(const void *objct, int callbackIndex, const char *argsDefine, va_list ap);

const void *callbackObj=NULL;
fCall_t LLVMBind_triggerCallback=NULL;

void LLVMBind_setTriggerCallbackEntryPoint(void *object, fCall_t call){
    if(callbackObj){
        return;
    }
    callbackObj=object;

    LLVMBind_triggerCallback=call;
}

void triggerCallback(int callbackIndex, const char *argsDefine, ...){
    va_list ap;
    va_start(ap, argsDefine);
    LLVMBind_triggerCallback(callbackObj, callbackIndex, argsDefine, ap);
    va_end(ap);
}