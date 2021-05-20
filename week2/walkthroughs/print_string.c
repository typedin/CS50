#include <stdio.h>
#include <cs50.h>

void print_name(char string[])
{
    int i = 0;
    while(string[i])
        printf("%c", string[i++]);
    
    printf("\n");
}

int main(void)
{
    
    char name[] = "Antoine";
    
    print_name(name);
    
    return 0;
}