#include <cs50.h>
#include <stdio.h>

// prototype

int GetPositiveInt(void);

int main(void)
{
    int n = GetPositiveInt();
    printf("Thank for %i\n", n);
}

int GetPositiveInt(void)
{
    int n;
    
    do
    {
        printf("Give me a positive int: ");
        n = GetInt();
    }
    while (n < 1);
    
    return n;
}