#include <stdio.h>

int main(void)
{
    float f = 1.0 / 10.0;
    // which is equivalent to 
    // float f = (float) 1 / (float) 10;
    printf("%.1f\n", f);
}