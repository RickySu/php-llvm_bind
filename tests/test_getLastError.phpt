--TEST--
Check Class Constructor
--FILE--
<?php
$LLVMBind=new LLVMBind();
$LLVMBind->loadBitcode("bad Bitcode");
if($LLVMBind->getLastError()!=""){
    echo "OK";
}
?>
--EXPECTF--
OK