#include <stdio.h>
#include <cs50.h>

int main()
{
    // user's input variable declaration
    int pyramid_height;
    
    /* the while loop checks the user's input :
    * it must be greater or equal to 1 and less or equal to 23
    * (or stricly greater than 0 and stricly less than 24)
    */
    
    do
    {
        printf("height: ");
        pyramid_height = GetInt();
        
    
    } while (!(pyramid_height >= 0 && pyramid_height < 24)); // prompt the user while the value is NOT > 0 and NOT < 24    
    
    // I assume the bottom line contains pyramid_height + 1 characters
    int num_char = pyramid_height + 1;
    
    // minimum number of hashes is equal to 2 (height of 1 implies 2 hashes)
    int num_hashes = 2;
    
    /*  Every line has the same amount of characters
    *   so for each line we have :
    *   number of total characters = number of hashes + number of spaces
    *   num_char = num_hashes
    */  
    
    int num_spaces = num_char - num_hashes;
    
    for (int i = 0 ; i < pyramid_height ; i++)
    {
        for (int j = 0 ; j < num_spaces ; j++)
            printf(" ");
        num_spaces--;
        
        for (int k = 0 ; k < num_hashes ; k++)
            printf("#");
        num_hashes++;
        
        // we've reached the end of the loop, beginning a new line
        printf("\n");
    }
    
    
}