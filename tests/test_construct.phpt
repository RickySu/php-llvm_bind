--TEST--
Check Class Constructor
--FILE--
<?php
if($a=new LLVMBind()){
  echo "OK";
}
else{
  echo "FAIL";
}
?>
--EXPECTF--
OK