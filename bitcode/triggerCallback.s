%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@callbackObj = global i8* null, align 8
@LLVMBind_triggerCallback = global void (i8*, i8*, i32, i8*, %struct.__va_list_tag*)* null, align 8

define void @LLVMBind_setTriggerCallbackEntryPoint(i8* %object, void (i8*, i8*, i32, i8*, %struct.__va_list_tag*)* %call) nounwind uwtable {
entry:
  %0 = load i8** @callbackObj, align 8
  %tobool = icmp eq i8* %0, null
  br i1 %tobool, label %if.end, label %return

if.end:                                           ; preds = %entry
  store i8* %object, i8** @callbackObj, align 8
  store void (i8*, i8*, i32, i8*, %struct.__va_list_tag*)* %call, void (i8*, i8*, i32, i8*, %struct.__va_list_tag*)** @LLVMBind_triggerCallback, align 8
  br label %return

return:                                           ; preds = %entry, %if.end
  ret void
}

define void @triggerCallback(i32 %callbackIndex, i8* %retval, i8* %argsDefine, ...) nounwind uwtable {
entry:
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag]* %ap, i64 0, i64 0
  %arraydecay1 = bitcast [1 x %struct.__va_list_tag]* %ap to i8*
  call void @llvm.va_start(i8* %arraydecay1)
  %0 = load void (i8*, i8*, i32, i8*, %struct.__va_list_tag*)** @LLVMBind_triggerCallback, align 8
  %1 = load i8** @callbackObj, align 8
  call void %0(i8* %1, i8* %retval, i32 %callbackIndex, i8* %argsDefine, %struct.__va_list_tag* %arraydecay) nounwind
  call void @llvm.va_end(i8* %arraydecay1)
  ret void
}

declare void @llvm.va_start(i8*) nounwind

declare void @llvm.va_end(i8*) nounwind
