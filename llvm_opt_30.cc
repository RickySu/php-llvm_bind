#include "llvm_opt_30.h"

void AddOptimizationPasses(PassManagerBase &MPM, FunctionPassManager &FPM, unsigned OptLevel, unsigned SizeLevel) {
    PassManagerBuilder Builder;
    FPM.add(createVerifierPass());
    Builder.OptLevel = OptLevel;
    Builder.SizeLevel = SizeLevel;

    Builder.Inliner = createAlwaysInlinerPass();
    Builder.DisableUnrollLoops = OptLevel == 0;
    Builder.populateFunctionPassManager(FPM);
    Builder.populateModulePassManager(MPM);

}

static void AddStandardCompilePasses(PassManagerBase &PM) {
    PM.add(createVerifierPass()); // Verify that input is correc
    PassManagerBuilder Builder;
    Builder.Inliner = createFunctionInliningPass();
    Builder.OptLevel = 3;
    Builder.populateModulePassManager(PM);
}

void optimizeModule(Module *M,int optimize_level) {
    PassManager Passes;
    FunctionPassManager FPasses(M);

    PassRegistry &Registry = *PassRegistry::getPassRegistry();
    initializeCore(Registry);
    initializeScalarOpts(Registry);
    initializeIPO(Registry);
    initializeAnalysis(Registry);
    initializeIPA(Registry);
    initializeTransformUtils(Registry);
    initializeInstCombine(Registry);
    initializeInstrumentation(Registry);
    initializeTarget(Registry);

    TargetData *TD = 0;
    const std::string &ModuleDataLayout = M->getDataLayout();
    TD = new TargetData(ModuleDataLayout);
    FPasses.add(new TargetData(*TD));

    AddStandardCompilePasses(Passes);

    FPasses.doInitialization();
    for (Module::iterator F = M->begin(), E = M->end(); F != E; ++F)
        FPasses.run(*F);
    FPasses.doFinalization();


    AddOptimizationPasses(Passes, FPasses, optimize_level, 0);
    Passes.add(createVerifierPass());

    Passes.run(*M);
}