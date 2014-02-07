--TEST--
Test method registerFunction
--FILE--
<?php
$LLVMBind=new LLVMBind();
$assembly = file_get_contents(__DIR__."/test_registerFunction.ll");
$assembly = str_replace('@main()', '@'.LLVMBind::FUNCTION_PREFIX.'main()', $assembly);
$bitcode=$LLVMBind->compileAssembly($assembly);
$LLVMBind->loadBitcode($bitcode);
if($LLVMBind->registerFunction('main', array())){
    echo "Load...";
}
main();
?>
--EXPECTF--
Load...OK