#include <stdio.h>
#include <cs50.h>
#include <string.h>

#include "dictionary.h"

bool unload(void);

int main(void) {
    int counter = 0;
    int SIZE = 4;
    node *hashtable[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    do
    {
        // Get string:
        char* str = get_string("String: ");
        if (str == NULL)
        {
            return 1;
        }

        // Unsign the string
        unsigned char* ustr = (unsigned char*) str;

        // Hash the string
        unsigned long key = hashstring(ustr);
        int hash = key % SIZE;

        printf("%lu, %d\n", key, hash);

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            //unload();
            return false;
        }

        strcpy(new_node->word, str);

        new_node->next = hashtable[hash];
        hashtable[hash] = new_node;

        counter++;

        printf("%d\n", counter);
    }
    while (counter < 20);

    int lookup = get_int("Enter index: ");
    node *cursor = hashtable[lookup];
    while (cursor != NULL)
    {
        printf("%s\n", cursor->word);
        cursor = cursor->next;
    }

    for (int l = 0; l < SIZE; l++)
    {
        cursor = hashtable[l];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
}

unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}