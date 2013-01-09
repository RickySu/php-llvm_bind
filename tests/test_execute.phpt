--TEST--
Test method execute
--FILE--
<?php
$LLVMBind=new LLVMBind();
$LLVMBind->loadBitcode(file_get_contents(__DIR__."/test_loadBitcode.bc"));
$LLVMBind->execute('main');    
?>
--EXPECTF--
OK