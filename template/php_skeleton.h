#ifndef PHP_EXTNAME_H
#define PHP_EXTNAME_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <main/php.h>
#ifdef ZTS
#include <TSRM/TSRM.h>
#endif

#define PHP_EXTNAME_VERSION "Extname"
#define PHP_EXTNAME_VERSION_MAJOR           0
#define PHP_EXTNAME_VERSION_MED             0
#define PHP_EXTNAME_VERSION_MIN             0
#define PHP_EXTNAME_VERSION_RELEASE         EXTNAME_VERSION_STABLE
#define PHP_EXTNAME_VERSION_RELEASE_VERSION 0
#define PHP_EXTNAME_EXTENSIONNAME "extname"

/** DEBUG options */
typedef struct _extname_debug_options {
	int debug_level;
	zend_bool enable_debug;
} extname_debug_options;

ZEND_BEGIN_MODULE_GLOBALS(extname)

	/** DEBUG */
	extname_debug_options debug;

ZEND_END_MODULE_GLOBALS(extname)


ZEND_EXTERN_MODULE_GLOBALS(extname)

#ifdef ZTS
	#define EXTNAME_GLOBAL(v) TSRMG(extname_globals_id, zend_extname_globals *, v)
	#define EXTNAME_VGLOBAL   ((zend_extname_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(extname_globals_id)])
#else
	#define EXTNAME_GLOBAL(v) (extname_globals.v)
	#define EXTNAME_VGLOBAL &(extname_globals)
#endif

extern zend_module_entry extname_module_entry;
#define phpext_extname_ptr &extname_module_entry

#define INIT_ZVAL(z) z = EG(uninitialized_zval);

#define PHALCON_ALLOC_ZVAL(z) \
	(z) = (zval *) emalloc(sizeof(zval)); \

#define PHALCON_ALLOC_INIT_ZVAL(z) \
	PHALCON_ALLOC_ZVAL(z); \

#ifndef INIT_PZVAL
#	define INIT_PZVAL(z) \
		Z_SET_REFCOUNT_P(z, 1); \
		ZVAL_UNREF(z);
#endif

#ifndef INIT_PZVAL_COPY
#	define INIT_PZVAL_COPY(z, v) \
		ZVAL_COPY_VALUE(z, v);   \
		Z_SET_REFCOUNT_P(z, 1);  \
		ZVAL_UNREF(z);
#endif

#ifndef ZVAL_COPY_VALUE
#	define ZVAL_COPY_VALUE(z, v) \
		(z)->value  = (v)->value; \
		Z_TYPE_P(z) = Z_TYPE_P(v);
#endif

#define PHALCON_INIT_CLASS(name) \
	int phalcon_ ##name## _init(int module_number)

#define PHALCON_INIT(name) \
	if (phalcon_ ##name## _init(module_number) == FAILURE) { \
		return FAILURE; \
	}

/** Macros for branch prediction */
#define likely(x)       EXPECTED(x)
#define unlikely(x)     UNEXPECTED(x)

#if defined(__GNUC__) && (defined(__clang__) || ((__GNUC__ * 100 + __GNUC_MINOR__) >= 405))
#	define UNREACHABLE() __builtin_unreachable()
#	define ASSUME(x)     if (x) {} else __builtin_unreachable()
#else
#	define UNREACHABLE() assert(0)
#	define ASSUME(x)     assert(!!(x));
#endif

#if defined(__GNUC__) || defined(__clang__)
#	define PHALCON_ATTR_NONNULL            __attribute__((nonnull))
#	define PHALCON_ATTR_NONNULL1(x)        __attribute__((nonnull (x)))
#	define PHALCON_ATTR_NONNULL2(x, y)     __attribute__((nonnull (x, y)))
#	define PHALCON_ATTR_NONNULL3(x, y, z)  __attribute__((nonnull (x, y, z)))
#	define PHALCON_ATTR_PURE               __attribute__((pure))
#	define PHALCON_ATTR_CONST              __attribute__((const))
#	define PHALCON_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#	define PHALCON_ATTR_NONNULL
#	define PHALCON_ATTR_NONNULL1(x)
#	define PHALCON_ATTR_NONNULL2(x, y)
#	define PHALCON_ATTR_NONNULL3(x, y, z)
#	define PHALCON_ATTR_PURE
#	define PHALCON_ATTR_CONST
#	define PHALCON_ATTR_WARN_UNUSED_RESULT
#endif

#if !defined(__GNUC__) && !(defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#	define __builtin_constant_p(s)    (0)
#endif

#ifndef ZEND_MOD_END
#	define ZEND_MOD_END { NULL, NULL, NULL, 0 }
#endif

#ifndef __func__
#	define __func__ __FUNCTION__
#endif

#define PHALCON_STATIC

/* This is a temporary fix until config.w32 is updated */
#if !defined(__CYGWIN__) && defined(WIN32) && defined(HAVE_CONFIG_H)

#endif /* !defined(__CYGWIN__) && !defined(WIN32) && defined(HAVE_CONFIG_H) */

#if !defined(__CYGWIN__) && defined(WIN32)
double round(double num) {
	return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}
#endif

#endif /* PHP_EXTNAME_H */
