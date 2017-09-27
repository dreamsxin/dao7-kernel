
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2015 Phalcon Team (http://www.phalconphp.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@phalconphp.com so we can send you a copy immediately.       |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
  |          Eduar Carvajal <eduar@phalconphp.com>                         |
  |          ZhuZongXin <dreamsxin@qq.com>                                 |
  +------------------------------------------------------------------------+
*/

#include "kernel/memory.h"

#include <Zend/zend_alloc.h>

#include "kernel/fcall.h"
#include "kernel/backtrace.h"

/**
 * Exports symbols to the active symbol table
 */
int phalcon_set_symbol(zend_array *symbol_table, zval *key_name, zval *value)
{
	if (!symbol_table) {
		php_error_docref(NULL, E_WARNING, "Cannot find a valid symbol_table");
		return FAILURE;
	}

	if (Z_TYPE_P(key_name) == IS_STRING) {
		Z_TRY_ADDREF_P(value);
		zend_hash_update(symbol_table, Z_STR_P(key_name), value);
	}

	return SUCCESS;
}

/**
 * Exports a string symbol to the active symbol table
 */
int phalcon_set_symbol_str(zend_array *symbol_table, char *key_name, unsigned int key_length, zval *value)
{
	if (!symbol_table) {
		php_error_docref(NULL, E_WARNING, "Cannot find a valid symbol_table");
		return FAILURE;
	}

	Z_TRY_ADDREF_P(value);
	zend_hash_str_update(symbol_table, key_name, key_length, value);

	return SUCCESS;
}

int phalcon_del_symbol(zend_array *symbol_table, zval *key_name)
{
	if (!symbol_table) {
		php_error_docref(NULL, E_WARNING, "Cannot find a valid symbol_table");
		return FAILURE;
	}

	if (Z_TYPE_P(key_name) == IS_STRING) {
		zend_hash_del(symbol_table, Z_STR_P(key_name));
	}

	return SUCCESS;
}

int phalcon_del_symbol_str(zend_array *symbol_table, char *key_name, unsigned int key_length)
{
	if (!symbol_table) {
		php_error_docref(NULL, E_WARNING, "Cannot find a valid symbol_table");
		return FAILURE;
	}

	zend_hash_str_del(symbol_table, key_name, key_length);

	return SUCCESS;
}
