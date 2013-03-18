<?php
$IRFile=__DIR__.DIRECTORY_SEPARATOR.'triggerCallback.s';
$outputIRFile=__DIR__.DIRECTORY_SEPARATOR.'triggerCallback.s.c';
$IRs=array();
if($handle = @fopen($IRFile, "r")){
    while($line = fgets($handle)){
        $IRs[]='"'.rtrim($line).'"';
    }
}
file_put_contents($outputIRFile,"const char *triggerCallback_ir = ".implode("\n", $IRs).";\n");