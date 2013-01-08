#ifndef _PHP_EXPORT_H_
# define _PHP_EXPORT_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define LLVMRESOURCE void *

void llvm_init();
LLVMRESOURCE llvm_newResource();
void llvm_freeResource(LLVMRESOURCE);

#endif
