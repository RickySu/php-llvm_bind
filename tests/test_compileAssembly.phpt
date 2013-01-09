--TEST--
Check Class Constructor
--FILE--
<?php
$LLVMBind=new LLVMBind();
$Bitcode=$LLVMBind->compileAssembly(file_get_contents(__DIR__."/test_compileAssembly.ll"));
if($LLVMBind->loadBitcode($Bitcode)){
    echo "OK";
}
?>
--EXPECTF--
OK