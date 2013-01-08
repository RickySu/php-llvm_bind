#ifndef _PHP_EXPORT_H_
# define _PHP_EXPORT_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

void llvm_init();
void *llvm_newResource();
void llvm_freeResource(void*);

#endif
