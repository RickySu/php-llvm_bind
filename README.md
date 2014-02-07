llvm_bind
==================

[![Build Status](https://travis-ci.org/RickySu/php-llvm_bind.png?branch=master)](https://travis-ci.org/RickySu/php-llvm_bind)

Introduction
------------

This is a PHP extension provid a way to bind with LLVM.

Requirements
------------

* PHP 5.3 above
* LLVM 3.0 above

Installation
------------

```
git clone https://github.com/RickySu/php-llvm_bind.git
phpize
./configure --with-llvm-config=/usr/bin/llvm-config
make install
```

How to Use
----------

### Compile llvm assembly to bitcode

```php
<?php
$LLVMBind=new LLVMBind();
$Bitcode=$LLVMBind->compileAssembly($LLVMAssembly);
if($Bitcode===false){
    echo $LLVMBind->getLastError();
}
```

### Load llvm compiled bitcode

```php
<?php
$LLVMBind=new LLVMBind();
if(!$LLVMBind->loadBitcode($Bitcode)){
    echo $LLVMBind->getLastError();
}
```

### register a function
```php
//function prototype
function test1(&$a, $b=20, array $c = null, testClass $d=null){}
```

```php
$LLVMBind=new LLVMBind();
$LLVMBind->loadBitcode($Bitcode); //load Bitcode
$LLVMBind->registerFunction('test1', array(
    'a' => array(
        true,  //pass_by_reference
        0,     //no type hint
        null,  //no type hint class
    ),
    'b' => array(
        false,  //pass_by_reference
        0,      //no type hint
        null,   //no type hint class
        20,     //with default value and is optional
    ),
    'c' => array(
        false,                   //pass_by_reference
        LLVMBind::IS_ARRAY,      //with array type hint
        null,                    //no type hint class
        null,                    //with default value null and is optional
    ),
    'd' => array(
        false,                   //pass_by_reference
        LLVMBind::IS_OBJECT,     //with object type hint
        'testClass',             //with type hint class 'testClass'
        null,                    //with default value null and is optional
    ),
));
```

reflaction function output
```
Function [ <internal> function test1 ] {

  - Parameters [4] {
    Parameter #0 [ <required> &$a ]
    Parameter #1 [ <optional> $b ]
    Parameter #2 [ <optional> array or NULL $c ]
    Parameter #3 [ <optional> testClass or NULL $d ]
  }
}
```

### execute a function

```php
$LLVMBind=new LLVMBind();
$LLVMBind->loadBitcode($Bitcode); //load Bitcode
$LLVMBind->registerFunction('main');
main(); //execute
```

### full example

```php
<?php
$Assembly = <<< EOT
@.str = private unnamed_addr constant [4 x i8] c"OK\\0A\\00", align 1

define i32 @main() nounwind uwtable {
  %1 = alloca i32, align 4
  store i32 0, i32* %1
  %2 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str, i32 0, i32 0))
  ret i32 0
}

declare i32 @printf(i8*, ...)
EOT;

//replace function name with internal function prefix "LLVM_FN_"
$Assembly = str_replace('@main()', '@'.LLVMBind::FUNCTION_PREFIX.'main()', $Assembly);
$LLVMBind=new LLVMBind();
$Bitcode=$LLVMBind->compileAssembly($Assembly,$optimize_level=3);
$LLVMBind->loadBitcode($Bitcode);
$LLVMBind->registerFunction('main');
main();
```

your will get an output "OK".

TODO
=======

pass parameter to registed function.
