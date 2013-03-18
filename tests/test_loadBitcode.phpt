--TEST--
test Method loadBitcode
--FILE--
<?php
$LLVMBind=new LLVMBind();
$bitcode=$LLVMBind->compileAssembly(file_get_contents(__DIR__."/test_loadBitcode.ll"));
if($LLVMBind->loadBitcode($bitcode)){
    echo "OK";
}
else{
    echo "FAIL";
}
?>
--EXPECTF--
OK