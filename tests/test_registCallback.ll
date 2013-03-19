@.str = private unnamed_addr constant [4 x i8] c"bld\00", align 1

define i32 @main() nounwind uwtable {
entry:
  tail call void (i32, i8*, ...)* @triggerCallback(i32 1, i8* getelementptr inbounds ([4 x i8]* @.str, i64 0, i64 0), i32 2, i32 10, double 1.200000e+00) nounwind
  ret i32 0
}

declare void @triggerCallback(i32, i8*, ...)
