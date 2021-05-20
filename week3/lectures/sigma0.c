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
    
    int sum = 0;
    
    for (int i = 1 ; i <= m ; i++)
    {
        sum += i;
    }
    
    return sum;
    
}