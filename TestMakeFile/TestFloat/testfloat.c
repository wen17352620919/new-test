#include "testfloat.h"

void compare_float(float a, float b)
{
    if(a<b)
        printf(" a<b\r\n");
    else if(a>b)
        printf(" a<b\r\n");
    else
         printf(" a=b\r\n");
}



void testfloat_demo()
{
    float a = 1111.11111;
    float b = 1111.111111;
    // compare_float(a,b);//a=b

    a = 111.11111;
    b = 111.111111;
    // compare_float(a,b);//a<b
    float c = 876.4444;
    float d = 87.4443;
    printf("c=%f\r\n", c);//876.444397
    printf("d=%f\r\n", d);//87.444297
    if(c == 876.4444) printf("==");
    else
        printf("!==");
}










