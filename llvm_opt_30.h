#ifndef LLVM_OPT_H
#define LLVM_OPT_H
#include "default.h"
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Analysis/LoopPass.h>
#include <llvm/Analysis/RegionPass.h>
#include <llvm/Analysis/CallGraph.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/LinkAllPasses.h>
#include <llvm/Target/TargetData.h>


using namespace llvm;
void AddOptimizationPasses(PassManagerBase &MPM, FunctionPassManager &FPM, unsigned OptLevel, unsigned SizeLevel);
static void AddStandardCompilePasses(PassManagerBase &PM);

#endif