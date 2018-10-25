// Implements a dictionary's functionality

// TODO - debug

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// define size
#define SIZE 143091

// create hashtable
node *hashtable[SIZE];
bool loadSuccess = false;

// Hash function: djb2 - http://www.cse.yorku.ca/~oz/hash.html
// Added case insensitivity from Neel Mehta
// https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
unsigned int hashstring(const char* word)
{
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % SIZE;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int lookup = hashstring(word);
    node *cursor = hashtable[lookup];

    // Loop through
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

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    char word[LENGTH];
    FILE *inload = fopen(dictionary, "r");
    if (inload == NULL)
    {
        unload();
        return false;
    }

    // while loop to create a linked list of nodes
    while (fscanf(inload, "%s", word) != EOF)
    {
        // Hash function
        int hash = hashstring(word);

        // Malloc memory for node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy word into node
        strcpy(new_node->word, word);

        // TNew node added to front of linked list, head now points at new_node
        new_node->next = hashtable[hash];
        hashtable[hash] = new_node;
    }

    if (fscanf(inload, "%s", word) == EOF)
    {
        fclose(inload);
        loadSuccess = true;
        return true;
    }

    // Check whether there was an error
    if (ferror(inload))
    {
        fclose(inload);
        unload();
        return false;
    }

    // Close text
    fclose(inload);

    return false;
}

// Recursive getcount modified from
// https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
unsigned int getcount(node* head)
{
    if (head == NULL)
    {
        return 0;
    }

    return 1 + getcount(head->next);
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loadSuccess)
    {
        // initialize counter
        unsigned int counter = 0;

        // iterate through heads in hash table
        for (int k = 0; k < SIZE; k++)
        {
            counter += getcount(hashtable[k]);
        }

        return counter;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int l = 0; l < SIZE; l++)
    {
        node *cursor = hashtable[l];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        if (l == SIZE - 1)
        {
            return true;
        }
    }

    return false;
}
