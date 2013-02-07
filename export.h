#ifndef _PHP_EXPORT_H_
# define _PHP_EXPORT_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define LLVMRESOURCE void *

void llvm_init();
LLVMRESOURCE llvm_newResource();
void llvm_freeResource(LLVMRESOURCE);
size_t llvm_compileAssembly(LLVMRESOURCE _Resource,char *Buffer,size_t size,char *Output,size_t output_size,char *errormsg,size_t errormsg_size,int optimize_level);
int llvm_callFunc(LLVMRESOURCE _Resource,const char *name,size_t name_len,char *errormsg,size_t errormsg_size);
int llvm_loadBitcode(LLVMRESOURCE _Resource,char *Buffer,size_t size,char *errormsg,size_t errormsg_size);

#endif
