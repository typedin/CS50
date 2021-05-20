#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


/**
 * A program that prints the initials of a name
 */
 

// function prototypes

string prompt_name(void);
void find_initials(string);


int main(void)
{
    // prompt the user for their name
    string user_name = prompt_name();
    
    // checking for NULL
    if(user_name != NULL)
        find_initials(user_name);
    
    else
        return 1;
        
    return 0;
}


/**
 * prompt and return user's name
 */
 
string prompt_name()
{
    return GetString(); 
}

/**
 * find the beginning of each word
 * capitalize it
 * new line when all done
 */
 
void find_initials(string name)
{
    // Variable that keeps track of
    // Set to true so the first letter is treated as an initial
    bool capitalize_next = true;
    
    /** 
    * if the loop found a space (ascii code 32)
    * then the next letter is an initial
    * then it must be capitalized
    */ 
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        
        if (name[i] == 32)
        {
            // if current char is a space then next letter must be capitalized
            capitalize_next = true;
        }  
        
        // first letter is an inital
        else if (capitalize_next) 
        {
            printf("%c", toupper(name[i]));
            capitalize_next = false; 
        }
    }
    
    printf("\n");
}