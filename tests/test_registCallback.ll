; ModuleID = 'test_registCallback.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"bld\00", align 1

define i32 @main() nounwind uwtable {
entry:
  tail call void (i32, i8*, ...)* @triggerCallback(i32 1, i8* getelementptr inbounds ([4 x i8]* @.str, i64 0, i64 0), i32 2, i32 10, double 1.200000e+00) nounwind
  ret i32 0
}

declare void @triggerCallback(i32, i8*, ...)
