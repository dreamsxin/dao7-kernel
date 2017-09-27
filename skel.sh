#!/bin/bash

givup() {
	echo $*
	exit 1
}

usage() {
echo "$0 --extname=module"
echo ""
echo "  --extname=module   module is the name of your extension"
exit 1
}

if test $# = 0; then
  usage
fi

while test $# -gt 0; do
  case "$1" in
  -*=*) optarg=`echo "$1" | sed 's/[-_a-zA-Z0-9]*=//'` ;;
  *) optarg= ;;
  esac

  case $1 in
    --extname=?*)
	extname=$optarg
	EXTNAME=`echo $extname | tr "[:lower:]" "[:upper:]"`
	;;
    *)
	usage
	;;
  esac
  shift
done

extname="${extname,,}"
Extname="$(tr '[:lower:]' '[:upper:]' <<< ${extname:0:1})${extname:1}"
EXTNAME="${extname^^}"

if test -d "$extname" ; then
  givup "Directory $extname already exists."
fi


mkdir $extname

echo "s/extname/$extname/g"  > $extname/sedscript
echo "s/Extname/$Extname/g"  >> $extname/sedscript
echo "s/EXTNAME/$EXTNAME/g"  >> $extname/sedscript

mkdir $extname/ext

sed -f $extname/sedscript < template/config.m4 > $extname/ext/config.m4
sed -f $extname/sedscript < template/Makefile.frag > $extname/ext/Makefile.frag
sed -f $extname/sedscript < template/Makefile.frag.deps > $extname/ext/Makefile.frag.deps
sed -f $extname/sedscript < template/php_skeleton.h > $extname/ext/php_$extname.h
sed -f $extname/sedscript < template/skeleton.h > $extname/ext/demo.h
sed -f $extname/sedscript < template/skeleton.c > $extname/ext/demo.c
sed -f $extname/sedscript < template/version.h > $extname/ext/version.h
sed -f $extname/sedscript < template/version.c > $extname/ext/version.c

mkdir $extname/ext/kernel

sed -f $extname/sedscript < kernel/main.h > $extname/ext/kernel/main.h
sed -f $extname/sedscript < kernel/main.c > $extname/ext/kernel/main.c
sed -f $extname/sedscript < kernel/memory.h > $extname/ext/kernel/memory.h
sed -f $extname/sedscript < kernel/memory.c > $extname/ext/kernel/memory.c
sed -f $extname/sedscript < kernel/require.h > $extname/ext/kernel/require.h
sed -f $extname/sedscript < kernel/require.c > $extname/ext/kernel/require.c
sed -f $extname/sedscript < kernel/file.h > $extname/ext/kernel/file.h
sed -f $extname/sedscript < kernel/file.c > $extname/ext/kernel/file.c
sed -f $extname/sedscript < kernel/output.h > $extname/ext/kernel/output.h
sed -f $extname/sedscript < kernel/output.c > $extname/ext/kernel/output.c
sed -f $extname/sedscript < kernel/string.h > $extname/ext/kernel/string.h
sed -f $extname/sedscript < kernel/string.c > $extname/ext/kernel/string.c
sed -f $extname/sedscript < kernel/array.h > $extname/ext/kernel/array.h
sed -f $extname/sedscript < kernel/array.c > $extname/ext/kernel/array.c
sed -f $extname/sedscript < kernel/hash.h > $extname/ext/kernel/hash.h
sed -f $extname/sedscript < kernel/hash.c > $extname/ext/kernel/hash.c
sed -f $extname/sedscript < kernel/object.h > $extname/ext/kernel/object.h
sed -f $extname/sedscript < kernel/object.c > $extname/ext/kernel/object.c
sed -f $extname/sedscript < kernel/fcall.h > $extname/ext/kernel/fcall.h
sed -f $extname/sedscript < kernel/fcall.c > $extname/ext/kernel/fcall.c
sed -f $extname/sedscript < kernel/operators.h > $extname/ext/kernel/operators.h
sed -f $extname/sedscript < kernel/operators.c > $extname/ext/kernel/operators.c
sed -f $extname/sedscript < kernel/concat.h > $extname/ext/kernel/concat.h
sed -f $extname/sedscript < kernel/concat.c > $extname/ext/kernel/concat.c
sed -f $extname/sedscript < kernel/variables.h > $extname/ext/kernel/variables.h
sed -f $extname/sedscript < kernel/variables.c > $extname/ext/kernel/variables.c
sed -f $extname/sedscript < kernel/iterator.h > $extname/ext/kernel/iterator.h
sed -f $extname/sedscript < kernel/iterator.c > $extname/ext/kernel/iterator.c
sed -f $extname/sedscript < kernel/math.h > $extname/ext/kernel/math.h
sed -f $extname/sedscript < kernel/math.c > $extname/ext/kernel/math.c
sed -f $extname/sedscript < kernel/exit.h > $extname/ext/kernel/exit.h
sed -f $extname/sedscript < kernel/exit.c > $extname/ext/kernel/exit.c
sed -f $extname/sedscript < kernel/debug.h > $extname/ext/kernel/debug.h
sed -f $extname/sedscript < kernel/debug.c > $extname/ext/kernel/debug.c
sed -f $extname/sedscript < kernel/assert.h > $extname/ext/kernel/assert.h
sed -f $extname/sedscript < kernel/assert.c > $extname/ext/kernel/assert.c
sed -f $extname/sedscript < kernel/backtrace.h > $extname/ext/kernel/backtrace.h
sed -f $extname/sedscript < kernel/backtrace.c > $extname/ext/kernel/backtrace.c
sed -f $extname/sedscript < kernel/exception.h > $extname/ext/kernel/exception.h
sed -f $extname/sedscript < kernel/exception.c > $extname/ext/kernel/exception.c

echo " [done]."

cat <<eof

To use your new extension, you will have to execute the following steps:

1.  $ cd $extname/ext
2.  $ phpize
3.  $ vi config.m4
4.  $ ./configure
5.  $ make
6.  $ vi ext/$extname/$extname.c
7.  $ make

Repeat steps 3-5 until you are satisfied with $extname/ext/config.m4 and
step 5 confirms that your module is compiled into PHP. Then, start writing
code and repeat the last two steps as often as necessary.
$warning

eof