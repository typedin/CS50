/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct _trie
{
	char *word;
	bool is_word;
	struct _trie *path[27];
	unsigned int nb_words;
	FILE *dic_fp;
}
trie;

//global variable, because...
extern struct _trie *root;

/**
 * recursive function
 * free all allocated nodes
 */
void free_trie(struct _trie *node);

/**
 * allocate new_node
 * assign all members to NULL
 */
struct _trie * node_allocation(void);

/**
 * insert each word from the dictionary
 * arguments:
 * @pointer to the root of the trie structure
 * @char pointer to the word to be inserted 
 */
bool insert_word(char *word);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload();

#endif // DICTIONARY_H
