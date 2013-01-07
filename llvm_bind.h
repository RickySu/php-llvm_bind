#ifndef _PHP_LLVM_BIND_H_
# define _PHP_LLVM_BIND_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
# include "TSRM.h"
#endif

#include "php.h"

#include "export.h"

PHP_MINIT_FUNCTION(llvm_bind);
PHP_MSHUTDOWN_FUNCTION(llvm_bind);  
PHP_RINIT_FUNCTION(llvm_bind);
PHP_RSHUTDOWN_FUNCTION(llvm_bind);
PHP_MINFO_FUNCTION(llvm_bind);
  
//PHP_FUNCTION(mytest);
PHP_METHOD(LLVMBind, __construct);

void initLLVMBindClass(TSRMLS_D);

extern zend_module_entry zmq_module_entry;

#endif