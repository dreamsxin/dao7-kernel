#include "version.h"

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/operators.h"

/**
 * Extname\Version
 *
 * This class allows to get the installed version of the framework
 */
zend_class_entry *extname_version_ce;

PHP_METHOD(Extname_Version, _getVersion);
PHP_METHOD(Extname_Version, get);
PHP_METHOD(Extname_Version, getId);

static const zend_function_entry extname_version_method_entry[] = {
	PHP_ME(Extname_Version, _getVersion, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Extname_Version, get, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Extname_Version, getId, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};

/**
 * Extname\Version initializer
 */
PHALCON_INIT_CLASS(Extname_Version){

	PHALCON_REGISTER_CLASS(Extname, Version, version, extname_version_method_entry, 0);

	return SUCCESS;
}

/**
 * Area where the version number is set. The format is as follows:
 * ABBCCDE
 *
 * A - Major version
 * B - Med version (two digits)
 * C - Min version (two digits)
 * D - Special release: 1 = Alpha, 2 = Beta, 3 = RC, 4 = Stable
 * E - Special release version i.e. RC1, Beta2 etc.
 */
PHP_METHOD(Extname_Version, _getVersion){

	array_init_size(return_value, 5);
	add_next_index_long(return_value, PHP_EXTNAME_VERSION_MAJOR);
	add_next_index_long(return_value, PHP_EXTNAME_VERSION_MED);
	add_next_index_long(return_value, PHP_EXTNAME_VERSION_MIN);
	add_next_index_long(return_value, PHP_EXTNAME_VERSION_RELEASE);
	add_next_index_long(return_value, PHP_EXTNAME_VERSION_RELEASE_VERSION);
}

/**
 * Returns the active version (string)
 *
 * <code>
 * echo Extname\Version::get();
 * </code>
 *
 * @return string
 */
PHP_METHOD(Extname_Version, get){

	zval version = {}, major = {}, medium = {}, minor = {}, special = {}, special_number = {}, result = {}, suffix = {};

	PHALCON_CALL_SELF(&version, "_getversion");

	phalcon_array_fetch_long(&major, &version, 0, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&medium, &version, 1, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&minor, &version, 2, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&special, &version, 3, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&special_number, &version, 4, PH_NOISY|PH_READONLY);

	PHALCON_CONCAT_VSVSVS(&result, &major, ".", &medium, ".", &minor, " ");

	switch (phalcon_get_intval(&special)) {

		case EXTNAME_VERSION_ALPHA:
			PHALCON_CONCAT_SV(&suffix, "ALPHA ", &special_number);
			break;

		case EXTNAME_VERSION_BETA:
			PHALCON_CONCAT_SV(&suffix, "BETA ", &special_number);
			break;

		case EXTNAME_VERSION_RC:
			PHALCON_CONCAT_SV(&suffix, "RC ", &special_number);
			break;

		default:
			ZVAL_EMPTY_STRING(&suffix);
			break;

	}
	zval_ptr_dtor(&version);
	phalcon_concat_self(&result, &suffix);
	zval_ptr_dtor(&suffix);
	ZVAL_STR(return_value, phalcon_trim(&result, NULL, PHALCON_TRIM_BOTH));
	zval_ptr_dtor(&result);
}

/**
 * Returns the numeric active version
 *
 * <code>
 * echo Extname\Version::getId();
 * </code>
 *
 * @return int
 */
PHP_METHOD(Extname_Version, getId){

	zval version = {}, major = {}, medium = {}, minor = {}, special = {}, special_number = {}, format = {}, real_medium = {}, real_minor = {};

	PHALCON_CALL_SELF(&version, "_getversion");
	phalcon_array_fetch_long(&major, &version, 0, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&medium, &version, 1, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&minor, &version, 2, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&special, &version, 3, PH_NOISY|PH_READONLY);
	phalcon_array_fetch_long(&special_number, &version, 4, PH_NOISY|PH_READONLY);

	ZVAL_STRING(&format, "%02s");

	PHALCON_CALL_FUNCTION(&real_medium, "sprintf", &format, &medium);
	PHALCON_CALL_FUNCTION(&real_minor, "sprintf", &format, &minor);
	zval_ptr_dtor(&format);

	PHALCON_CONCAT_VVVVV(return_value, &major, &real_medium, &real_minor, &special, &special_number);
	zval_ptr_dtor(&real_medium);
	zval_ptr_dtor(&real_minor);
	zval_ptr_dtor(&version);
}
