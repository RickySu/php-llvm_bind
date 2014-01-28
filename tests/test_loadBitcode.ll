@.str = private unnamed_addr constant [3 x i8] c"OK\00", align 1

define i8* @main(i8** %a, i32 %n) nounwind uwtable {
  %1 = alloca i8**, align 8
  %2 = alloca i32, align 4
  store i8** %a, i8*** %1, align 8
  store i32 %n, i32* %2, align 4
  %3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0))
  %4 = load i8*** %1, align 8
  %5 = getelementptr inbounds i8** %4, i64 0
  %6 = load i8** %5
  ret i8* %6
}

declare i32 @printf(i8*, ...)
