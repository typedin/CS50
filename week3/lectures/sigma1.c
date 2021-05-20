#include <stdio.h>
#include <cs50.h>

int sigma(int m);

int main(void)
{
    int n;
    do
    {
        printf("Positive integer please: ");
        n = get_int();
    }
    while(n < 1);
    
    int answer = sigma(n);
    
    printf("answer : %d\n", answer);
    
    return 0;
}


int sigma(int m)
{
    
    // base case
    if ( m <= 0)
    {
        return 0;
    }
    else
    {
        return (m + sigma(m - 1));
    }
    
}