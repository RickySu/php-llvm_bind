/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
#include "llvm_bind.h"

/* If you declare any globals in php_llvm_bind.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(llvm_bind)
*/

zend_class_entry *llvm_bind_ce;

/* True global resources - no need for thread safety here */
static int le_llvm_bind;

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_loadBitcode, 0)
    ZEND_ARG_INFO(0, bitcode)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_compileAssembly, 0)
    ZEND_ARG_INFO(0, assembly)
    ZEND_ARG_INFO(0, optimize_level)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_execute, 0)
    ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_registerFunction, 0)
    ZEND_ARG_INFO(0, name)
    ZEND_ARG_INFO(0, arginfo)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ llvm_bind_methods[]
 *
 * Every user visible function must have an entry in llvm_bind_functions[].
 */
const zend_function_entry llvm_bind_methods[] = {
        PHP_ME(LLVMBind,    __construct,  NULL,    ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
        PHP_ME(LLVMBind,    execute,    arginfo_llvm_bind_execute,  ZEND_ACC_PUBLIC)
        PHP_ME(LLVMBind,    compileAssembly,    arginfo_llvm_bind_compileAssembly,  ZEND_ACC_PUBLIC)
        PHP_ME(LLVMBind,    getLastError,    NULL,  ZEND_ACC_PUBLIC)
        PHP_ME(LLVMBind,    loadBitcode,    arginfo_llvm_bind_loadBitcode,  ZEND_ACC_PUBLIC)
        PHP_ME(LLVMBind,    registerFunction,    arginfo_llvm_bind_registerFunction,  ZEND_ACC_PUBLIC)       
	PHP_FE_END	/* Must be the last line in llvm_bind_functions[] */
};
/* }}} */

/* {{{ llvm_bind_module_entry
 */
zend_module_entry llvm_bind_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"llvm_bind",
	llvm_bind_methods,
	PHP_MINIT(llvm_bind),
	PHP_MSHUTDOWN(llvm_bind),
	PHP_RINIT(llvm_bind),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(llvm_bind),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(llvm_bind),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LLVM_BIND
ZEND_GET_MODULE(llvm_bind)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("llvm_bind.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_llvm_bind_globals, llvm_bind_globals)
    STD_PHP_INI_ENTRY("llvm_bind.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_llvm_bind_globals, llvm_bind_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_llvm_bind_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_llvm_bind_init_globals(zend_llvm_bind_globals *llvm_bind_globals)
{
	llvm_bind_globals->global_value = 0;
	llvm_bind_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(llvm_bind)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	llvm_init();
	initLLVMBindClass(TSRMLS_C);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(llvm_bind)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(llvm_bind)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(llvm_bind)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(llvm_bind)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "llvm_bind support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* {{{ proto bool LLVMBind::__construct() */
PHP_METHOD(LLVMBind, __construct)
{
    
}
/*}}}*/


/* {{{ proto bool LLVMBind::loadBitcode($bitcode) */
PHP_METHOD(LLVMBind, loadBitcode)
{
    char *bitcode;
    int  bitcode_len;
    zval *object = getThis();
    llvm_resource *internal_resource;

    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &bitcode, &bitcode_len)) {
        return;
    }
    if(llvm_loadBitcode(internal_resource->resource,bitcode,bitcode_len,internal_resource->last_error,ERROR_MESSAG_BUFFER_SIZE)==0){
        RETURN_FALSE;
    }
    RETURN_TRUE;
}
/*}}}*/

/* {{{ proto boolean LLVMBind::execute($name) */
PHP_METHOD(LLVMBind, execute)
{
    char *name;
    int  name_len;
    zval *object = getThis();
    zval *ret;
    zval ***argv;
    int argc;
    llvm_resource *internal_resource;

    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s*", &name, &name_len, &argv, &argc)) {
        return;
    }

    if(name_len==0){
        RETURN_FALSE;
    }

    ret = llvm_callFunc(
        internal_resource->resource,
        name,
        name_len,
        NULL,
        0,
        internal_resource->last_error,
        ERROR_MESSAG_BUFFER_SIZE);
    if(ret == NULL){
        RETURN_NULL();
    }
    RETURN_ZVAL(ret, 0, 0);
}
/*}}}*/

/* {{{ proto string LLVMBind::registerFunction($functionName, $argInfo) */
PHP_METHOD(LLVMBind, registerFunction)
{
    zval *object = getThis();
    zval *argInfo, **arrayElement_p, **zvalue_p;
    int  argInfo_count, index, require_argInfo_count;    
    HashTable *argInfo_hash;
    HashPosition pointer;
    char *key;
    uint klen;
    ulong key_index;
    char *functionName, *internalFunctionName, *tmpClassName;
    uint functionName_len;
    zend_arg_info *arg_info;
    zend_function_entry *functions;
    llvm_resource *internal_resource;
    
    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|a", &functionName, &functionName_len, &argInfo)) {
        return;
    }
    
    functions = ecalloc(2, sizeof(zend_function_entry));
    
    argInfo_hash = Z_ARRVAL_P(argInfo); 
    require_argInfo_count = argInfo_count = zend_hash_num_elements(argInfo_hash);
    arg_info = ecalloc(argInfo_count+1, sizeof(zend_arg_info));
    index=0;
    for(zend_hash_internal_pointer_reset_ex(argInfo_hash, &pointer); 
        zend_hash_get_current_data_ex(argInfo_hash, (void**) &arrayElement_p, &pointer) == SUCCESS;
        zend_hash_move_forward_ex(argInfo_hash, &pointer)) {
        if(HASH_KEY_IS_STRING != zend_hash_get_current_key_ex(argInfo_hash, &key, &klen, &key_index, 0, &pointer)){
            RETURN_FALSE;
        }
        arg_info[index+1].name = key;
        arg_info[index+1].name_len = klen-1;
        
        if(zend_hash_index_find( //pass_by_reference
            Z_ARRVAL_PP(arrayElement_p),
            0,
            (void**) &zvalue_p) != FAILURE){
//            SEPARATE_ZVAL(zvalue_p);
//            convert_to_boolean_ex(zvalue_p);
            if(Z_TYPE_PP(zvalue_p) == IS_BOOL || Z_TYPE_PP(zvalue_p) == IS_LONG){
                arg_info[index+1].pass_by_reference = Z_LVAL_PP(zvalue_p) && 1;
            }
//            zval_dtor(zvalue_p);
        }

        if(zend_hash_index_find( //type_hint
            Z_ARRVAL_PP(arrayElement_p),
            1,
            (void**) &zvalue_p) != FAILURE) {
            if(Z_TYPE_PP(zvalue_p) == IS_LONG){
                arg_info[index+1].type_hint = Z_LVAL_PP(zvalue_p);
            }
        }
        
        if(zend_hash_index_find( //class_name
            Z_ARRVAL_PP(arrayElement_p),
            2,
            (void**) &zvalue_p) != FAILURE) {
            if(Z_TYPE_PP(zvalue_p) == IS_STRING){
                tmpClassName = ecalloc(Z_STRLEN_PP(zvalue_p)+1, 1);
                memcpy(tmpClassName, Z_STRVAL_PP(zvalue_p), Z_STRLEN_PP(zvalue_p));
                arg_info[index+1].class_name = tmpClassName;
                arg_info[index+1].class_name_len = Z_STRLEN_PP(zvalue_p);
            }
        }

        if(zend_hash_index_find( // default value
            Z_ARRVAL_PP(arrayElement_p),
            3,
            (void**) &zvalue_p) != FAILURE) {
            if(Z_TYPE_PP(zvalue_p) != IS_LONG){
                arg_info[index+1].allow_null = 1;
                require_argInfo_count--;
            }
        }
        index++;
    }
    
    //set required_num_args
    arg_info[0].class_name_len = require_argInfo_count;    
    internalFunctionName = emalloc(sizeof(LLVM_FUNCTION_PREFIX) + functionName_len + 1);
    functions[0].arg_info = arg_info;
    functions[0].num_args = argInfo_count;
    strcpy(internalFunctionName, LLVM_FUNCTION_PREFIX);
    strcat(internalFunctionName, functionName);
    functions[0].fname = &internalFunctionName[sizeof(LLVM_FUNCTION_PREFIX)-1];
    functions[0].handler = llvm_getFunc(internal_resource->resource, internalFunctionName);
    zend_register_functions(NULL, functions, NULL, 0 TSRMLS_CC);
//    efree(internalFunctionName);
//    efree(arg_info);
    RETURN_TRUE;    
}

/* {{{ proto string LLVMBind::compileAssembly($assembly) */
PHP_METHOD(LLVMBind, compileAssembly)
{
    char *assembly, *bitcode;
    int assembly_len,bitcode_len,bitcode_buffer_len,optimize_level;
    long zval_optimize_level=3;
    zval *object = getThis();
    llvm_resource *internal_resource;

    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|l", &assembly, &assembly_len,&zval_optimize_level)) {
        return;
    }

    optimize_level=(int)zval_optimize_level;

    bitcode_buffer_len = assembly_len * 3;
    if(bitcode_buffer_len<BITCODE_MIN_BUFFER_SIZE){
        bitcode_buffer_len=BITCODE_MIN_BUFFER_SIZE;
    }
    bitcode = emalloc(bitcode_buffer_len);

    if((bitcode_len=llvm_compileAssembly(internal_resource->resource,assembly,assembly_len,bitcode,bitcode_buffer_len,internal_resource->last_error,ERROR_MESSAG_BUFFER_SIZE,optimize_level))>0){
        RETVAL_STRINGL(bitcode,bitcode_len,1);
        efree(bitcode);
        return;
    }

    efree(bitcode);
    RETURN_FALSE;
}
/*}}}*/

/* {{{ proto bool LLVMBind::getLastError() */
PHP_METHOD(LLVMBind, getLastError)
{
    zval *object = getThis();
    llvm_resource *internal_resource;
    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    RETURN_STRING(internal_resource->last_error,1);
}
/*}}}*/



void initLLVMBindClass(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "LLVMBind", llvm_bind_methods);
    ce.create_object = create_llvm_resource;
    llvm_bind_ce = zend_register_internal_class(&ce TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_NULL"), IS_NULL TSRMLS_CC);    
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_LONG"), IS_LONG TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_DOUBLE"), IS_DOUBLE TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_STRING"), IS_STRING TSRMLS_CC);            
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_ARRAY"), IS_ARRAY TSRMLS_CC);        
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_OBJECT"), IS_OBJECT TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_BOOL"), IS_BOOL TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_RESOURCE"), IS_RESOURCE TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("IS_CONSTANT"), IS_CONSTANT TSRMLS_CC);

    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("SIZEOF_ZVAL"), sizeof(zval) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("SIZEOF_LONG"), sizeof(long) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_LVAL"), (ulong)((void*)&((zval*)0)->value.lval) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_DVAL"), (ulong)((void*)&((zval*)0)->value.dval) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_STR_VAL"), (ulong)((void*)&((zval*)0)->value.str.val) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_STR_LEN"), (ulong)((void*)&((zval*)0)->value.str.len) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_HT"), (ulong)((void*)&((zval*)0)->value.ht) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_VALUE_OBJ"), (ulong)((void*)&((zval*)0)->value.obj) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_REFCOUNT__GC"), (ulong)((void*)&((zval*)0)->refcount__gc) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_TYPE"), (ulong)((void*)&((zval*)0)->type) TSRMLS_CC);
    zend_declare_class_constant_long(llvm_bind_ce, ZEND_STRL("OFFSETOF_ZVAL_IS_REF__GC"), (ulong)((void*)&((zval*)0)->is_ref__gc) TSRMLS_CC);    
    zend_declare_class_constant_string(llvm_bind_ce, ZEND_STRL("FUNCTION_PREFIX"), LLVM_FUNCTION_PREFIX TSRMLS_CC);
    #ifdef ZTS
    zend_declare_class_constant_bool(llvm_bind_ce, ZEND_STRL("ZTS"), 1 TSRMLS_CC);
    zend_declare_class_constant_string(llvm_bind_ce, ZEND_STRL("TSRMLS_C"), "tsrm_ls" TSRMLS_CC);
    #else 
    zend_declare_class_constant_bool(llvm_bind_ce, ZEND_STRL("ZTS"), 0 TSRMLS_CC);
    zend_declare_class_constant_string(llvm_bind_ce, ZEND_STRL("TSRMLS_C"), "" TSRMLS_CC);
    #endif

}

zend_object_value create_llvm_resource(zend_class_entry *class_type TSRMLS_DC) {
  zend_object_value retval;
  llvm_resource *internal_resource;
#if PHP_VERSION_ID < 50399
  zval *tmp;
#endif
  internal_resource = (llvm_resource *) ecalloc(1,sizeof(llvm_resource));
  memset(internal_resource, 0, sizeof(llvm_resource));
  internal_resource->resource=llvm_newResource();
  internal_resource->last_error=emalloc(ERROR_MESSAG_BUFFER_SIZE);
  memset(internal_resource->last_error, 0, ERROR_MESSAG_BUFFER_SIZE);
  zend_object_std_init(&internal_resource->zo, class_type TSRMLS_CC);
#if PHP_VERSION_ID < 50399
  zend_hash_copy(internal_resource->zo.properties,
       &class_type->default_properties,
       (copy_ctor_func_t) zval_property_ctor,
       (void *) &tmp,
       sizeof(zval *));
#else
  object_properties_init(&internal_resource->zo, class_type);
#endif
  retval.handle = zend_objects_store_put(internal_resource,(zend_objects_store_dtor_t) zend_objects_destroy_object,free_llvm_resource, NULL TSRMLS_CC);
  retval.handlers = zend_get_std_object_handlers();
  return retval;
}

void free_llvm_resource(void *object TSRMLS_DC){
  llvm_resource *internal_resource=(llvm_resource *) object;
  llvm_freeResource(internal_resource->resource);
  zend_object_std_dtor(&internal_resource->zo TSRMLS_CC);
  efree(internal_resource->last_error);
  efree(internal_resource);
}

void freeArgs(int nArgs, zval **args){
    int i;
    for(i=0;i<nArgs;i++){
        if(args[i]){
            zval_dtor(args[i]);
        }
    }
    efree(args);
}

