#ifndef _PHP_LLVM_BIND_STRUCT_H_
# define _PHP_LLVM_BIND_STRUCT_H_

typedef struct _llvm_resource{
    zend_object zo;
    LLVMRESOURCE resource;
    const char * last_error;
} llvm_resource;

#endif