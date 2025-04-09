// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *p = table[hash(word)];
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }
    char file_word[LENGTH];
    while (fscanf(source, "%s", file_word) == 1)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(source);
            return false;
        }
        strcpy(n->word, file_word);
        n->next = NULL;
        unsigned int index = hash(file_word);
        if (table[index] == NULL)
        {
            table[index] = n;

            count += 1;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
            count += 1;
        }
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p != NULL)
        {
            node *temp = p;
            p = p->next;
            free(temp);
        }
    }
    return true;
}
