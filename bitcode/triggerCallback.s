; ModuleID = 'bitcode/triggerCallback.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@callbackObj = global i8* null, align 8
@LLVMBind_triggerCallback = global void (i8*, i32, i8*, %struct.__va_list_tag*)* null, align 8

define void @LLVMBind_setTriggerCallbackEntryPoint(i8* %object, void (i8*, i32, i8*, %struct.__va_list_tag*)* %call) nounwind uwtable {
entry:
  %0 = load i8** @callbackObj, align 8, !tbaa !0
  %tobool = icmp eq i8* %0, null
  br i1 %tobool, label %if.end, label %return

if.end:                                           ; preds = %entry
  store i8* %object, i8** @callbackObj, align 8, !tbaa !0
  store void (i8*, i32, i8*, %struct.__va_list_tag*)* %call, void (i8*, i32, i8*, %struct.__va_list_tag*)** @LLVMBind_triggerCallback, align 8, !tbaa !0
  br label %return

return:                                           ; preds = %entry, %if.end
  ret void
}

define void @triggerCallback(i32 %callbackIndex, i8* %argsDefine, ...) nounwind uwtable {
entry:
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag]* %ap, i64 0, i64 0
  %arraydecay1 = bitcast [1 x %struct.__va_list_tag]* %ap to i8*
  call void @llvm.va_start(i8* %arraydecay1)
  %0 = load void (i8*, i32, i8*, %struct.__va_list_tag*)** @LLVMBind_triggerCallback, align 8, !tbaa !0
  %1 = load i8** @callbackObj, align 8, !tbaa !0
  call void %0(i8* %1, i32 %callbackIndex, i8* %argsDefine, %struct.__va_list_tag* %arraydecay) nounwind
  call void @llvm.va_end(i8* %arraydecay1)
  ret void
}

declare void @llvm.va_start(i8*) nounwind

declare void @llvm.va_end(i8*) nounwind

!0 = metadata !{metadata !"any pointer", metadata !1}
!1 = metadata !{metadata !"omnipotent char", metadata !2}
!2 = metadata !{metadata !"Simple C/C++ TBAA"}
