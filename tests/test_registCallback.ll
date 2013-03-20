%struct._simple_value_struct = type { %union._simple_value_value, i8 }
%union._simple_value_value = type { %struct.anon }
%struct.anon = type { i8*, i32 }

@.str = private unnamed_addr constant [4 x i8] c"bld\00", align 1
@.str1 = private unnamed_addr constant [5 x i8] c"%.*s\00", align 1

define i32 @main() nounwind uwtable {
entry:
  %retval1 = alloca %struct._simple_value_struct, align 8
  call void (i32, %struct._simple_value_struct*, i8*, ...)* @triggerCallback(i32 1, %struct._simple_value_struct* %retval1, i8* getelementptr inbounds ([4 x i8]* @.str, i64 0, i64 0), i32 2, i32 10, double 1.200000e+00) nounwind
  %len = getelementptr inbounds %struct._simple_value_struct* %retval1, i64 0, i32 0, i32 0, i32 1
  %0 = load i32* %len, align 8
  %val = getelementptr inbounds %struct._simple_value_struct* %retval1, i64 0, i32 0, i32 0, i32 0
  %1 = load i8** %val, align 8
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([5 x i8]* @.str1, i64 0, i64 0), i32 %0, i8* %1) nounwind
  %2 = load i8** %val, align 8
  call void @free(i8* %2) nounwind
  ret i32 0
}

declare void @triggerCallback(i32, %struct._simple_value_struct*, i8*, ...)

declare i32 @printf(i8* nocapture, ...) nounwind

declare void @free(i8* nocapture) nounwind
