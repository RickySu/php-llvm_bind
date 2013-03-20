--TEST--
test registCallback
--FILE--
<?php
function test($boolean, $integer, $double){
    return "result:$boolean, $integer, $double\n";
}

$LLVMBind=new LLVMBind();

if(!($Bitcode=$LLVMBind->compileAssembly(file_get_contents(__DIR__."/test_registCallback.ll")))){
    echo $LLVMBind->getLasterror();
}
if($LLVMBind->loadBitcode($Bitcode)){
    echo "OK\n";
}

$LLVMBind->registCallback(1,'test');
$LLVMBind->execute('main');
?>
--EXPECTF--
OK
result:1, 10, 1.2
