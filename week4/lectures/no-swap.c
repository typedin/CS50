#include <stdio.h>
#include <cs50.h>


void swap(int a, int b);

int main(void)
{
    int x = 1;
    int y = 2;
    
    printf("x is %d \ny is %d\n", x, y);
    
    swap(x,y);
    
    printf("x is %d \ny is %d\n", x, y);
    
    return 0;
}

void swap(int a, int b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
