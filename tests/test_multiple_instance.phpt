--TEST--
Test with multiple instance
--FILE--
<?php
$LLVMBind1=new LLVMBind();
$bitcode=$LLVMBind1->compileAssembly(file_get_contents(__DIR__."/test_compileAssembly.ll"));
$LLVMBind1->loadBitcode($bitcode);
$LLVMBind2=new LLVMBind();
$bitcode=$LLVMBind2->compileAssembly(file_get_contents(__DIR__."/test_loadBitcode.ll"));
$LLVMBind2->loadBitcode($bitcode);

$LLVMBind1->execute('main');
$LLVMBind2->execute('main');
?>
--EXPECTF--
OK
OK!