#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int binary_search(int value, int array[], int low, int high)
{
	// base case
	if (high < low)
		return -1 ;
	
	int mid = (low + high) / 2;
	
	if (value == array[mid])
		return mid;
	
	else if (value > array[mid])
		return binary_search(value, array, mid + 1 , high);
	
	else if (value < array[mid])
		return binary_search(value, array, low, mid - 1);
	
	else
		return -1;
}


bool search(int value, int values[], int n)
{
	// call binary_search in a way that doesn't break this declaration
	if (binary_search(value, values,0 , n - 1 ) >= 0)
		return true;
		
	return false;
}

void sort(int values[], int n)
{
    // insertion sort algorithm
    
    int current_elm, j;
    
    for (int i = 1; i < n; i++)
    {
        current_elm = values[i];
        j = i;
        while (j > 0 && values[j - 1] > current_elm)
        {
            values[j] = values[j - 1];
            j = j - 1;
        }
        values[j] = current_elm;
    }
    
    return;
}

int main(int argc, char* argv[])
{
	
	if (argc != 2)
		return 1;
	
	int values[] = {2,4,6,7,9,8,5,3};
	int n = 8;
	for (int i = 0 ; i < n ; i++)
		printf("%d ", values[i]);
	
	printf("\n");
	
	sort(values,n);
	
	for (int i = 0 ; i < n ; i++)
		printf("%d ", values[i]);
	
	
	int value = atoi(argv[1]); 
	
	if (search(value, values, n))
		printf("found it !\n");
	else
		printf("didn't find it\n");
	
	return 0;
}