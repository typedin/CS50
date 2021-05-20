#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    
    printf("%d\n", argc);
    
    for (int i = 1 ; i < argc ; i++){
        printf("%s", argv[i]);
        printf("\n");
    }
}