// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) // WORKS
{
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number (Super cool hash function!!!)
unsigned int hash(const char *word) // WORKS
{
    if (strlen(word) < 2)
    {
        return (((toupper(word[0]) + 'A') - (2 * 'A')) + ((toupper(word[0]) - 'A') * 25));
    }
    return (((toupper(word[0]) + toupper(word[1])) - (2 * 'A')) + ((toupper(word[0]) - 'A') * 25));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) // WORKS
{
    // Open File in
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open File");
        return false;
    }
    // Read Dictionary
    char stringChar[LENGTH + 1];
    while (fscanf(file, "%s", stringChar) != EOF)
    {
        // Create node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Computer is out of RAM");
            return false;
        }
        // Copy word readed from dictionary to node
        strcpy(n->word, stringChar);
        n->next = NULL;
        // Hash stringChar (word readed from the dictionary)
        unsigned int hash_code = hash(stringChar);
        // Insert node into table (array of linked lists)
        n->next = table[hash_code];
        table[hash_code] = n;
        wordCount++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) // WORKS
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool state = false;
    node *cursor = NULL;
    node *temp = NULL;
    for (int i = 0; i < 677; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
            state = true;
        }
    }
    return state;
}
