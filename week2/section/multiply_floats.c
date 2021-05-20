#include <stdio.h>

float multiply_floats(float, float);
long double multiply_doubles(double, double);

int main()
{
    float a , b;

    a = .456;
    b = 13.45;
    
    printf("%.20f\n", multiply_floats(a,b));
    printf("%.20Lf\n", multiply_doubles(a,b));
   
}

float multiply_floats(float a, float b)
{
    float result;
    result = a * b;

    return result;
}

long double multiply_doubles(double a, double b)
{
    return a * b;
}