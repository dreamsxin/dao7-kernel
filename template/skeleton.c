
/*
  +------------------------------------------------------------------------+
  | Phalcon Framework                                                      |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
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

#include "php_extname.h"

#include <main/php_ini.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <main/SAPI.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"

#include "extname.h"

ZEND_DECLARE_MODULE_GLOBALS(extname)

PHP_INI_BEGIN()
	/* Enables/Disables debug */
	STD_PHP_INI_BOOLEAN("extname.debug.enable_debug",           "0",    PHP_INI_ALL,    OnUpdateBool, debug.enable_debug,           zend_extname_globals, extname_globals)
PHP_INI_END()

static PHP_MINIT_FUNCTION(extname)
{
	REGISTER_INI_ENTRIES();

	/* 1. Register exceptions */

	/* 2. Register interfaces */

	/* 4. Register everything else */
	PHALCON_INIT(Extname_Version);

	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(extname){

	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

static PHP_RINIT_FUNCTION(extname){

	zend_extname_globals *extname_globals_ptr = EXTNAME_VGLOBAL;

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(extname){

	return SUCCESS;
}

static PHP_MINFO_FUNCTION(extname)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Extname Framework", "enabled");
	php_info_print_table_row(2, "Extname Version", PHP_EXTNAME_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );

	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(extname)
{
}

static PHP_GSHUTDOWN_FUNCTION(extname)
{
}

static const zend_module_dep extname_deps[] = {
	ZEND_MOD_REQUIRED("spl")
	ZEND_MOD_REQUIRED("date")
	ZEND_MOD_END
};

zend_module_entry extname_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	extname_deps,
	PHP_EXTNAME_EXTENSIONNAME,
	NULL,
	PHP_MINIT(extname),
	PHP_MSHUTDOWN(extname),
	PHP_RINIT(extname),
	PHP_RSHUTDOWN(extname),
	PHP_MINFO(extname),
	PHP_EXTNAME_VERSION,
	ZEND_MODULE_GLOBALS(extname),
	PHP_GINIT(extname),
	PHP_GSHUTDOWN(extname),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_EXTNAME
ZEND_GET_MODULE(extname)
#endif
