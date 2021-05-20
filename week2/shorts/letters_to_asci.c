#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char* argv[])
{
    
    for (int i = 1; i < argc; i++)
        for (int j = 0, n = strlen(argv[i]); j < n; j++)
        {
            printf("%c is: %d\n", argv[i][j], argv[i][j]);
        }
        
    return 0;
}