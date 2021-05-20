#include <stdio.h>
#include <cs50.h>

bool validate_triangle(float, float, float);
float get_valid_input(int i);


int main()
{
    float a, b, c;        // declare each side length of the triangle
    int i = 1;              // index variable
    
    a = get_valid_input(i++);
    b = get_valid_input(i++);
    c = get_valid_input(i);
    
    bool valid = validate_triangle(a,b,c);
    
    printf("the triangle is%svalid", valid == true? " ":" not ");
    
    
}

bool validate_triangle(float a, float b, float c)
{
    if ( a <= 0 || b <= 0 || c <= 0)        //this line is not necessary since the input is checked, but still...
        return false;
    
    else if ( a + b >= c || a + c >= b || b + c >= a)
            return true;
    
    else
        return false;
}

float get_valid_input(int i)
{
    float local_n;
    
    do 
    {
        printf("Give me a size for the #%i ", i);
        local_n = GetFloat();
    }
    while ( local_n < 1 );
    
    return local_n;
}