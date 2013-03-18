--TEST--
Test method execute
--FILE--
<?php
$LLVMBind=new LLVMBind();
$bitcode=$LLVMBind->compileAssembly(file_get_contents(__DIR__."/test_loadBitcode.ll"));
$LLVMBind->loadBitcode($bitcode);
$LLVMBind->execute('main');    
?>
--EXPECTF--
OK!