#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// prototype
int usage(void);
void cypher_string(char* p, char* k);
char* user_input(void);
int zero_index(char k);

/**
 * This program encrypt a plain text to a crypted text via a key word
 * it takes 2 command line arguments : 
 * 1) the call to the program itself
 * 2) a key which is used to encipher the text 
 * 
 * a few checkings are made on the user's input
 * 
 */
 
int main(int argc, char* argv[])
{
    
    
    // check the command line arguments :
    // must have 2 arguments
    if ( argc != 2 )
        return usage();
    
    // the 2nd argument must contain letters only
    for (int i = 0, n = strlen(argv[1]) ; i < n ; i++)
    {
        // if we come accross a non alpha, we give the user the correct usage and exit
        if(! isalpha(argv[1][i]) )
            return usage();
    }   
    
    // point to argv[1]
    char* k = argv[1];
    
    char* string = user_input();
    
    cypher_string(string, k);
    
    printf("\n");
    
    return 0;
}

/**
 * simple function to print the correct usage
 * and return 1
 */
int usage(void)
{
    printf("Usage: ./caesar k\n");
        
    return 1;
}

/**
 * ask the user for an input
 */

char* user_input(void)
{
    // the staff solution doesn't check for empty strings, so do I
    
    return GetString();

}
/**
 * zero_index return a value from 0 to 25 plus 65 or 97
 * if the input character was respectively upper or lower
 * 
 */

int zero_index(char c)
{
    // we adjust the key so it's 0 indexed
    
    // adjust the k if it's upper case
    if ( isupper(c) )
        return c - 65;
        
    // adjust the k if it's lower case    
    else if ( islower(c) )
        return c - 97;
        
    // this shouldn't be reached
    else 
        return 0;
}

/**
 * encipher the plain text
 * takes two arguments :
 * 1)   the plain text as a array of char (char* s)
 * 2)   1 char (char* k)
 */

void cypher_string(char* s, char* k)
{
    // loop over each character of the string
    for (int i = 0, j = 0, n = strlen(s); i < n; i++)
    {
        
        // set j to 0 if we've reached the NULL char
        if ( !k[j] )
            j = 0;
            
        // if the current character is a letter, cipher it
        if ( isalpha(s[i]) )
        {
            
            // check if it's upper case
            if ( isupper(s[i]) )
                printf("%c", ( (zero_index(s[i]) + zero_index(k[j++]) ) % 26 ) + 65 );
            
            // check if it's lower case        
            else if ( islower(s[i]) )
                printf("%c", ( (zero_index(s[i]) + zero_index(k[j++]) ) % 26 ) + 97 );
                
        }
        
        // if the current character is not a letter, then print it as it is
        else
            printf("%c", s[i]);
            
    }
    
}