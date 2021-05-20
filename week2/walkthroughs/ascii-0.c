#include <stdio.h>

int main()
{
    
    for (int i = 0 ; i < 65 + 26; i++)
    {
        printf("%i is %c\n", i, (char)i);
    }
 
    for (char c = 'A' ; c <= 'Z' ; c++)
        printf("%i is %c\n", c, c);
}