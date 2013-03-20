#include <stdio.h>
#include <stdlib.h>

typedef union _simple_value_value {
    long lval;
    double dval;
    struct {
        char *val;
        int len;  
    } str;
} simple_value_value;

typedef struct _simple_value_struct {
    simple_value_value value;
    unsigned char type;
} simple_value;


extern void triggerCallback(int callbackIndex, simple_value *ret, const char *argsDefine, ...);

int main(){
    simple_value retval;    
    triggerCallback(1, &retval, "bld" , 2, 10, 1.2);
    printf("%.*s", retval.value.str.len, retval.value.str.val);
    free(retval.value.str.val);
    return 0;
}
