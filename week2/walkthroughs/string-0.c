#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string s = GetString();
    
    if (s != NULL)
    {
        for (int i = 0, n = strlen(s) ; i < n ; i++)
        {
            printf("%c\n", s[i]);
        }
    }
    else
    {
        printf("s returned NULL");
    }
}