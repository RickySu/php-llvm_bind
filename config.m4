dnl $Id$
dnl config.m4 for extension llvm_bind

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(llvm_bind, for llvm_bind support,
dnl Make sure that the comment is aligned:
dnl [  --with-llvm_bind             Include llvm_bind support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(llvm_bind, whether to enable llvm_bind support,
dnl Make sure that the comment is aligned:
dnl [  --enable-llvm_bind           Enable llvm_bind support])

if test "$PHP_LLVM_BIND" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-llvm_bind -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/llvm_bind.h"  # you most likely want to change this
  dnl if test -r $PHP_LLVM_BIND/$SEARCH_FOR; then # path given as parameter
  dnl   LLVM_BIND_DIR=$PHP_LLVM_BIND
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for llvm_bind files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LLVM_BIND_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LLVM_BIND_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the llvm_bind distribution])
  dnl fi

  dnl # --with-llvm_bind -> add include path
  dnl PHP_ADD_INCLUDE($LLVM_BIND_DIR/include)

  dnl # --with-llvm_bind -> check for lib and symbol presence
  dnl LIBNAME=llvm_bind # you may want to change this
  dnl LIBSYMBOL=llvm_bind # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LLVM_BIND_DIR/lib, LLVM_BIND_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LLVM_BINDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong llvm_bind lib version or lib not found])
  dnl ],[
  dnl   -L$LLVM_BIND_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(LLVM_BIND_SHARED_LIBADD)

  PHP_NEW_EXTENSION(llvm_bind, llvm_bind.c, $ext_shared)
fi
