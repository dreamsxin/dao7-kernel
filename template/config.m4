PHP_ARG_ENABLE(extname, whether to enable extname framework,
[  --enable-extname        Enable extname framework])

PHP_ARG_ENABLE(extname-debug, for extname debug support,
[  --enable-extname-debug  Enable enable extname debug support], no, no)

if test "$PHP_EXTNAME_DEBUG" != "no"; then
    CFLAGS="$CFLAGS -Wall -g3 -ggdb -O0 -DEXTNAME_DEBUG=1"
    AC_DEFINE(EXTNAME_DEBUG, 1, [Enable extname debug support])
else
	CFLAGS="$CFLAGS -DEXTNAME_RELEASE=1"
fi

if test "$PHP_EXTNAME" = "yes"; then
	AC_MSG_CHECKING([PHP version])

	tmp_version=$PHP_VERSION
	if test -z "$tmp_version"; then
		if test -z "$PHP_CONFIG"; then
		AC_MSG_ERROR([php-config not found])
		fi
		php_version=`$PHP_CONFIG --version 2>/dev/null|head -n 1|sed -e 's#\([0-9]\.[0-9]*\.[0-9]*\)\(.*\)#\1#'`
	else
		php_version=`echo "$tmp_version"|sed -e 's#\([0-9]\.[0-9]*\.[0-9]*\)\(.*\)#\1#'`
	fi

	if test -z "$php_version"; then
		AC_MSG_ERROR([failed to detect PHP version, please report])
	fi

	ac_IFS=$IFS
	IFS="."
	set $php_version
	IFS=$ac_IFS
	extname_php_version=`expr [$]1 \* 1000000 + [$]2 \* 1000 + [$]3`

	if test "$extname_php_version" -lt "7000000"; then
		AC_MSG_ERROR([You need at least PHP 7.0 to be able to use this version of Phalcon/Dao7. PHP $php_version found])
	else
		AC_MSG_RESULT([$php_version, ok])
	fi

	AC_DEFINE(HAVE_EXTNAME, 1, [Whether you have Phalcon Framework])
	extname_sources="extname.c \
kernel/main.c \
kernel/fcall.c \
kernel/require.c \
kernel/debug.c \
kernel/backtrace.c \
kernel/object.c \
kernel/array.c \
kernel/hash.c \
kernel/string.c \
kernel/operators.c \
kernel/concat.c \
kernel/exception.c \
kernel/file.c \
kernel/output.c \
kernel/memory.c \
kernel/variables.c \
kernel/assert.c \
kernel/exit.c \
kernel/iterator.c \
kernel/math.c \
version.c"

	PHP_SUBST(EXTNAME_SHARED_LIBADD)

	PHP_NEW_EXTENSION(extname, $extname_sources, $ext_shared)

	PHP_C_BIGENDIAN

	PHP_ADD_MAKEFILE_FRAGMENT([Makefile.frag])
fi

if test "$GCC" = "yes"; then
	PHP_ADD_MAKEFILE_FRAGMENT([Makefile.frag.deps])
fi
