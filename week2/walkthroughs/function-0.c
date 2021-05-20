#include <cs50.h>
#include <stdio.h>

// prototype

void PrintName(string name);

int main(void)
{
    printf("Your name: ");
    string s = GetString();
    PrintName(s);
}

void PrintName(string name)
{
    printf("Hello, %s\n", name);
}