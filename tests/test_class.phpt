--TEST--
Check Class Exists
--FILE--
<?php
if(class_exists('LLVMBind')){
  echo "OK";
}
else{
  echo "FAIL";
}
?>
--EXPECTF--
OK