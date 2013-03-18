<?php
$IRFile=__DIR__.DIRECTORY_SEPARATOR.'triggerCallback.s';
$outputIRFile=__DIR__.DIRECTORY_SEPARATOR.'triggerCallback.s.c';
$IRs=array();
if($handle = @fopen($IRFile, "r")){
    while($line = fgets($handle)){
        $IRs[]='"'.addslashes(rtrim($line)).'\\n"';
    }
}
file_put_contents($outputIRFile,"char *triggerCallback_ir = ".implode("\n", $IRs).";\n");