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
ZEND_BEGIN_ARG_INFO(arginfo_llvm_bind_void, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ llvm_bind_methods[]
 *
 * Every user visible function must have an entry in llvm_bind_functions[].
 */
const zend_function_entry llvm_bind_methods[] = {
        PHP_ME(LLVMBind,    __construct,    arginfo_llvm_bind_void,    ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
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
    load();
}

void initLLVMBindClass(TSRMLS_D)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "LLVMBind", llvm_bind_methods);
    llvm_bind_ce = zend_register_internal_class(&ce TSRMLS_CC);    
//    ce.create_object = create_cult_secrets;
}
