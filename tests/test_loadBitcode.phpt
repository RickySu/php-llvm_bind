--TEST--
Check Class Constructor
--FILE--
<?php
$LLVMBind=new LLVMBind();
if($LLVMBind->loadBitcode(file_get_contents(__DIR__."/test_loadBitcode.bc"))){
    echo "OK";
}
else{
    echo "FAIL";
}
?>
--EXPECTF--
OK