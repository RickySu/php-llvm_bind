dnl $Id$
dnl config.m4 for extension llvm_bind

PHP_ARG_WITH(llvm-config, llvm config path,
[  --with-llvm-config=[PATH]    llvm config path.[/usr/bin/llvm-config]])

if test "$PHP_LLVM_BIND" != "no"; then
  AC_MSG_CHECKING(for llvm-config)
  for i in $PHP_LLVM_CONFIG /usr/bin/llvm-config /usr/local/bin/llvm-config "";do
    if test -x $i;then
      LLVM_CONFIG=$i
      break
    fi
  done
  
  if test -z "$LLVM_CONFIG"; then
    AC_MSG_ERROR(Cannot find llvm-config.Please specify correct llvm-config installation path. )
  fi
  LLVM_INCLUDE=`$LLVM_CONFIG --includedir`
  LLVM_LDFLAGS=`$LLVM_CONFIG --ldflags`
  LLVM_EXTRA_LDFLAGS=`$LLVM_CONFIG --libs core jit native all`
  LLVM_CXXFLAGS=`$LLVM_CONFIG --cxxflags`
  PHP_ADD_INCLUDE($LLVM_INCLUDE)
  EXTRA_LDFLAGS="$EXTRA_LDFLAGS $LLVM_EXTRA_LDFLAGS"
  LDFLAGS="$LDFLAGS $LLVM_LDFLAGS"
  CXXFLAGS="$CXXFLAGS $LLVM_CXXFLAGS"
  PHP_REQUIRE_CXX()
  PHP_SUBST(LLVM_BIND_SHARED_LIBADD)
  PHP_ADD_LIBRARY(stdc++, 1, LLVM_BIND_SHARED_LIBADD) 
  PHP_NEW_EXTENSION(llvm_bind, llvm_bind.c llvm.cc llvm_resource.cc, $ext_shared)
fi
