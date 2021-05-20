#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// prototype
void cypher_string(string s, int k);
char* user_input(void);

/**
 * This program encrypt a plain text
 * it takes 2 command line arguments : 
 * 1) the call to the program itself
 * 2) a key which is used to encipher the text 
 */
 
int main(int argc, string argv[])
{
    
    /**
     * check the command line arguments :
     * 1# must have 2 arguments
     * 2# the second argument must be a non negative integer
     */
    
    if ( argc != 2 )
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    else if ( atoi(argv[1]) < 0 )
    {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }
        
    // the second argument is converted to an integer
    int k = atoi(argv[1]);
    
    string plain_text = user_input();
    
    // checking for null    
    if (!plain_text)
        return 1;
        
    cypher_string(plain_text, k);
    
    printf("\n");
    
    return 0;
}

/**
 * ask the user for an input
*/

string user_input(void)
{
    // the staff solution doesn't check for empty strings
  
    return GetString();
}

/**
 * encipher the plain text
 * take two arguments :
 * the plain text (char* s)
 * a key (int k)
 */
 
void cypher_string(string s, int k)
{
  
    // loop over each character of the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // if the current character is a letter
        if ( isalpha(s[i]) )
        {
            
        // check if it's upper case
            if ( isupper(s[i]) )
                printf("%c", ((s[i] - 65  + k) % 26 ) + 65 );
        
        // check if it's lower case        
            else if ( islower(s[i]) )
                printf("%c", ((s[i] - 97  + k) % 26 ) + 97 );
                
        }
        // if the current character is not a letter, then print it as it is
        else
            printf("%c", s[i]);
    }
}