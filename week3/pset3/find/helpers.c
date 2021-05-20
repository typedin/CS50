/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/** 
 * binary search, recursive version
 * returns the index of the array where the value has been found 
 * else return -1
 */
int binary_search(int value, int values[], int low, int high)
{
	// calculate the middle of the array
	int mid = (low + high) / 2;
	
	// return the index if the value's been found
	if (value == values[mid])
		return mid;
	
	// if the value is greater than the value at mid : recursive call on the right part of the array
    else if (value > values[mid])
	{
	    // mid + 1 is passed as low
		return binary_search(value, values, mid + 1 , high);
	}
	
	// if the value is less than the value at mid : recursive call on the left part of the array
	
	else if (value < values[mid])
	{
	    // mid - 1 is passed as high
		return binary_search(value, values, low, mid - 1);
	}
	
	// if none of the above cases are true, return -1
	else
		return -1;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // return false if the array size is less than 1
    if (n < 1)
        return false;
        
    // linear search algorithm
    for (int i = 0; i < n; i++)
    {
        if (values[i] == value)
            return true;
    }
    
    // return false if the value was not found
    return false;
}

/**
 * insertion sort algorithm
 * sorts array of n values.
 */
void sort(int values[], int n)
{
    // temp will be used to store 
    int tmp, j;
    
    for (int i = 1; i < n - 1; i++)
    {
        tmp = values[i];
        j = i;
        while (j > 0 && values[j - 1] > values[i])
        {
            values[j] = values[j - 1];
            j = j - 1;
        }
        values[j] = tmp;
    }

}