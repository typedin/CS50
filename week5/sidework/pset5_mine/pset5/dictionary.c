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

struct _trie *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

	if (root == NULL)
		return false;
	if(word == NULL)
		return false;
		
	trie *crawler = root;
	
	int index = 0;
	
	for(int i = 0; word[i] != '\0' ; i++)
	{

		// assign index to the current letter of the word
		// the letter is lowercase indexed
		// apostrophes are valid
		// index them in the last path
		if (word[i] == 39)
		{
			index = 26;
		}
		else if (isalpha(word[i]))
		{
			index = tolower(word[i]) - 97;
		}

		// We hit a dead end in the trie
		// AND
		// We're at the end of the word
		if (crawler->path[index] == NULL)
		{
			if(crawler->word == NULL)
			{
				return false;
			}
			else
				break;
		}	
		else
		{
			crawler = crawler->path[index];
		}
	}
/*
	for(int i = 0 ; word[i] != '\0' ; i++)
	{
		if(crawler->word[i] != tolower(word[i]))
		{
			return false;
		}		
	}
	*/
	if(crawler->is_word == false)
		return false;
	else
		return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{

   	// create root aka : first node
	root = node_allocation();
	
	if (!root)
		return false;
		
    // open file passed as a string
    root->dic_fp = fopen(dictionary, "r");
    
  	if (root->dic_fp == NULL)
	{
		printf("pointer to file error\n");
		exit (1);
	}

	// assumes no word exceeds LENGTH (45)
    // plus one for the null character 
	char *word = malloc((LENGTH + 1) * sizeof(char));
	if (!word)
		return false;
		
    while (fscanf(root->dic_fp, " %s", word) == 1) 
    {
        //if(insert_word(root, word) == false)
        if(insert_word(word) == false)
        {
        	free(word);
        	return false;
        }
    }

	free(word);
	
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return root->nb_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload()
{
    free_trie(root);	
	return true;
}


/**
 *
 * For this, credit goes to :
 * http://stackoverflow.com/questions/34691151/how-to-free-recursive-struct-trie
 *
 * I only added line 130-132
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

    // if the node holds a word
    if(node->word)
    	free(node->word);
    	
	if(node->dic_fp)
		fclose(root->dic_fp);
			
    // base case	
    free(node);
}

/**
 * Why do I need to do what's on line 151 ?
 * valgrind complains if I don't.
 */
struct _trie * node_allocation()
{
	trie *new_node = malloc(sizeof(trie));
	
	if (new_node == NULL)
	{
		printf("Error pointer is NULL\n");
		exit (1);
	}
	
	new_node->word = NULL;
	new_node->is_word = false;
	
	for(int i = 0 ; i < 27 ; i++)
	{
		new_node->path[i] = NULL;
	}
	
	new_node->nb_words = 0;
	
	new_node->dic_fp = NULL;
	
	return new_node;
}

bool insert_word(char *word)
{
		
	if (root == NULL)
		return false;
	
	// initialize a crawler pointer to root
	trie *crawler = root;
	
	// index to iterate over path[] member fo struct trie
	int index = 0;
	
	// create a size counter for word 
	// we will be mallocing only the amount of memory needed
	int word_len = 0;
	
	for(int i = 0; word[i] != '\0' ; i++)
	{

		// assign index to the current letter of the word
		// the letter is lowercase indexed
		// apostrophes are valid$
		// index them in the last path
		if (word[i] == 39)
		{
			index = 26;
		}
		else
		{
			index = tolower(word[i]) - 97;
		}

		// new path is closed
		if (crawler->path[index] == NULL)
		{
			
			// malloc the new path
			crawler->path[index] = node_allocation();
			
			crawler = crawler->path[index];
		}	
		else
		{
			crawler = crawler->path[index];
		}
		
		// increment the size counter for word
		word_len++;
		
		if (word[i + 1] == '\0')
		{
			crawler->is_word = true;
/*			crawler->word = malloc((word_len + 1) * sizeof(char));
			if(crawler->word == NULL)
			{
				printf("malloc error\n");
				exit (1);
			}
			// this could be smarter...
			for (int i = 0 ; word[i] != '\0' ; i++)
			{
				crawler->word[i] = word[i];
			}
*/
			root->nb_words++;
					
		}

	}
	
	return true;
}

