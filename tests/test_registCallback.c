#include <stdio.h>
#include <string.h>

extern void triggerCallback(int callbackIndex, const char *argsDefine, ...);

int main(){
    triggerCallback(1, "bld" , 2, 10, 1.2);
    return 0;
}