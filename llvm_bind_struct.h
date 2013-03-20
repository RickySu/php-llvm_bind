#ifndef _PHP_LLVM_BIND_STRUCT_H_
#define _PHP_LLVM_BIND_STRUCT_H_

typedef struct _llvm_resource{
    zend_object zo;
    LLVMRESOURCE resource;
    char * last_error;
    zval *callback[20];
    TSRMLS_D;
} llvm_resource;


typedef union _simple_value_value {
    long lval;
    double dval;
    struct {
        char *val;
        int len;  
    } str;
} simple_value_value;



typedef struct _simple_value_struct {
    simple_value_value value;
    zend_uchar type;
} simple_value;

#endif