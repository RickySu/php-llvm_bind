@callbackObj = global i8* null, align 8
@LLVMBind_triggerCallback = global void (i32, i8*, ...)* null, align 8

define void @LLVMBind_setTriggerCallbackEntryPointet(i8* %object, void (i32, i8*, ...)* %call) nounwind uwtable {
entry:
  %0 = load i8** @callbackObj, align 8
  %tobool = icmp eq i8* %0, null
  br i1 %tobool, label %if.end, label %return

if.end:                                           ; preds = %entry
  store i8* %object, i8** @callbackObj, align 8
  store void (i32, i8*, ...)* %call, void (i32, i8*, ...)** @LLVMBind_triggerCallback, align 8
  br label %return

return:                                           ; preds = %entry, %if.end
  ret void
}
