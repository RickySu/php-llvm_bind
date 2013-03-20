#ifndef _PHP_LLVM_BIND_H_
# define _PHP_LLVM_BIND_H_
#include <stdarg.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include "default.h"
#include "php.h"
#include "export.h"
#include "llvm_bind_struct.h"

#ifdef USE_DEFAULT_CALLBACK
#include "bitcode/triggerCallback.s.c"
#endif

PHP_MINIT_FUNCTION(llvm_bind);
PHP_MSHUTDOWN_FUNCTION(llvm_bind);  
PHP_RINIT_FUNCTION(llvm_bind);
PHP_RSHUTDOWN_FUNCTION(llvm_bind);
PHP_MINFO_FUNCTION(llvm_bind);
  
PHP_METHOD(LLVMBind, __construct);
PHP_METHOD(LLVMBind, compileAssembly);
PHP_METHOD(LLVMBind, execute);
PHP_METHOD(LLVMBind, getLastError);
PHP_METHOD(LLVMBind, loadBitcode);
PHP_METHOD(LLVMBind, registCallback);

void freeArgs(int nArgs, zval **args);
void __triggerCallback(void *object, simple_value *retvalue, int callbackIndex, const char *argsDefine, va_list ap);

void initLLVMBindClass(TSRMLS_D);
zend_object_value create_llvm_resource(zend_class_entry *class_type TSRMLS_DC);
void free_llvm_resource(void *object TSRMLS_DC);
void setTriggerCallbackEntryPoint(void *object);

void loadDefaultCallbackBitcode(llvm_resource *internal_resource);

extern zend_module_entry zmq_module_entry;


#endif