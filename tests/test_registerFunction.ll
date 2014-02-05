@.str = private unnamed_addr constant [3 x i8] c"OK\00", align 1

define i8* @main() nounwind uwtable {
  %1 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0))
  ret i8* null
}

declare i32 @printf(i8*, ...)
