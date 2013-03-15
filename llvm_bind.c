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
#include "llvm_bind_struct.h"

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
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_regist_callback, 0)
    ZEND_ARG_INFO(0, callback_index)
    ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_execute, 0)
    ZEND_ARG_INFO(0, name)
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
        PHP_ME(LLVMBind,    registCallback, arginfo_llvm_bind_regist_callback,  ZEND_ACC_PUBLIC)
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


/* {{{ proto bool LLVMBind::registCallback($index, $callback) */
PHP_METHOD(LLVMBind, registCallback)
{
    long callbackIndex;
    zval *zCallback;
    char *callbzckFunctionName;
    zval *object = getThis();
    llvm_resource *internal_resource;

    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &callbackIndex, &zCallback)) {
        return;
    }

    if (!zend_is_callable(zCallback, 0, &callbzckFunctionName TSRMLS_CC)) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "'%s' is not a valid callback", callbzckFunctionName);
        efree(callbzckFunctionName);
        RETURN_FALSE;
    }        
    efree(callbzckFunctionName);
    zval_add_ref(&zCallback);
    
    if(internal_resource->callback[callbackIndex]){
        zval_ptr_dtor(&internal_resource->callback[callbackIndex]);
    }
    
    internal_resource->callback[callbackIndex] = zCallback;
    setTriggerCallbackEntryPoint((void*)object);    
    RETURN_TRUE;
}
/*}}}*/

/* {{{ proto boolean LLVMBind::execute($name) */
PHP_METHOD(LLVMBind, execute)
{
    char *name;
    int  name_len;
    zval *object = getThis();
    llvm_resource *internal_resource;

    internal_resource = (llvm_resource *)zend_object_store_get_object(object TSRMLS_CC);
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &name, &name_len)) {
        return;
    }

    if(name_len==0){
        RETURN_FALSE
    }

    if(llvm_callFunc(internal_resource->resource,name,name_len,internal_resource->last_error,ERROR_MESSAG_BUFFER_SIZE)>0){
        RETURN_TRUE;
    }

    RETURN_FALSE;
}
/*}}}*/

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

void triggerCallback(void *object, int callbackIndex, int len, char *message){
    zval *data;
    zval *args[1];
    zval retval;
    llvm_resource *internal_resource;
    internal_resource = (llvm_resource *)zend_object_store_get_object((zval *)object TSRMLS_CC);
    MAKE_STD_ZVAL(data);
    ZVAL_STRINGL(data, message, len, 1);
    printf("call back triggered!\n");
    args[0] = data;
    if(internal_resource->callback[callbackIndex]){
        if (call_user_function(EG(function_table), NULL, internal_resource->callback[callbackIndex], &retval, 1, args TSRMLS_CC) == SUCCESS) {
            zval_dtor(&retval);
        }
    }
    zval_dtor(&retval);
    zval_ptr_dtor(&(args[0]));
}

void setTriggerCallbackEntryPoint(void *object){
    char *name="LLVMBind_stTriggerCallbackEntryPointet";
    int  name_len=strlen(name);
    llvm_resource *internal_resource;
    fCall_t call;
    internal_resource = (llvm_resource *)zend_object_store_get_object((zval *)object TSRMLS_CC);
    call = llvm_getFunc(internal_resource->resource,name,name_len,internal_resource->last_error,ERROR_MESSAG_BUFFER_SIZE);
    if(call){
        call(object, triggerCallback);
    }
}
