/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * binary search recursive implementation
 * returns -1 either the value has not been found or an error occured
 * returns the index where the value has been found
 */
int binary_search(int value, int array[], int low, int high);