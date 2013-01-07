--TEST--
Check Class Exists
--FILE--
<?php
if(class_exists('LLVMBind')){
  echo "OK";
}
else{
  echo "FAIL";
  print_r(get_declared_classes());
}
?>
--EXPECTF--
OK