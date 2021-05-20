/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

// create some global variables
// even if we're told not to on the internet
struct _trie *root;
unsigned int nb_words;
FILE *dic_fp;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
	// create a crawler pointer
	// assign it to root
	trie *crawler = root;
	
	// interate over each letter of a word in the text we're checking
	// the loop will stop if : word[i] is '\0'
	for(int i = 0, index = 0; word[i]; i++)
	{
		
		// assign index to the current letter of the word
		// the letter is lowercase indexed
		// apostrophes are valid
		// index them in the last path
		if (word[i] == 39)
			index = 26;
		else
			index = tolower(word[i]) - 97;
		
		// we get out of the loop if we hit a closed gate
		if(crawler->path[index] == NULL)
		{
			return false;
		}
		else
			crawler = crawler->path[index];
	}

	// crawler->is_word is a boolean value
	return crawler->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

   	// create root aka : first node
	root = node_allocation();
	nb_words = 0;		

    // open file passed as a string
	dic_fp = fopen(dictionary, "r");
    
  	if (dic_fp == NULL)
	{
		return false;
	}

	// assumes no word exceeds LENGTH (45)
    // plus one for the null character 
	char *word = malloc((LENGTH + 1) * sizeof(char));
	if (word == NULL)
		return false;
		
	while (fscanf(dic_fp, " %s", word) == 1)  
    {
        insert_word(word);
    }
    
	free(word);	
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return nb_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    free_trie(root);
   	fclose(dic_fp);	
	return true;
}


/**
 *
 * For this, credit goes to :
 * http://stackoverflow.com/questions/34691151/how-to-free-recursive-struct-trie
 *
 */
void free_trie(trie *node)
{

	// safe guard including root node.
	if(!node)
		return; 

	// recursive case (go to end of trie)
	for (int i = 0; i < 27; i++)
	{	
		free_trie(node->path[i]);
	}
	
    // base case	
    free(node);
}

/**
 * This function allocates some memory for a new_node
 * it assigns : 
 * - all pointers in the array to null
 * - new_node->is_word to false
 * if I don't do that, I get complains in valgrind (conditional jumps on unitiliased value).
 */
struct _trie * node_allocation()
{
	// reserve ourselves some memory
	trie *new_node = malloc(sizeof(trie));
	
	// check the memory allocation
	if (new_node == NULL)
	{
		printf("Error pointer is NULL\n");
		exit (1);
	}
	
	// each new node won't be a word by default
	new_node->is_word = false;
	
	// create closed "gate""
	for(int i = 0 ; i < 27 ; i++)
	{
		new_node->path[i] = NULL;
	}
		
	return new_node;
}

void insert_word(char *word)
{

	// initialize a crawler pointer to root
	trie *crawler = root;
	
	// index to iterate over path[] member fo struct trie
	int index = 0;
	
	for(int i = 0; word[i] != '\0' ; i++)
	{

		// assign index to the current letter of the word
		// the letter is lowercase indexed
		// apostrophes are valid
		// index them in the last path
		if (word[i] == 39)
			index = 26;
		else
			index = tolower(word[i]) - 97;
			
		// new path is closed
		if (crawler->path[index] == NULL)
		{
			// open a gate
			// malloc the new path
			// if a malloc error occurs, 
			// node_allocation() exits the program
			crawler->path[index] = node_allocation();
			
			crawler = crawler->path[index];
		}	
		else
		{
			crawler = crawler->path[index];
		}
	}
	
	// a new valid word has been "inserted" in the trie
	crawler->is_word = true;
	
	// increment the number of words in the dictionary
	nb_words++;
}
