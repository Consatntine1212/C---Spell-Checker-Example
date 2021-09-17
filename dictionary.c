// Implements a dictionary's functionality

#include <stdbool.h>
#include <cs50.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;  // N is set to 26

// Hash table
node *table[N];
int sum = 0 ;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int i = hash(word);
    node *cursor = table[i];
    while (cursor != NULL)
    {
        //Cheching if this is the word
        if (strcasecmp(word, cursor->word)==0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number Hash funtion 26 leters
unsigned int hash(const char *word)
{
    // Used the djb2 algorithm from http://www.cse.yorku.ca/~oz/hash.html
        unsigned long hash = 5381;
        int c = 0; //error
        while (c == (*word++)) // maybe ad toopen ;;
            hash = ((hash << 5 ) + hash) +c;
    
    
    return hash % N ; //moddulo n
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word[45];
    FILE *file = fopen(dictionary, "r");
    if (file != NULL )
    {
        // Read throu evry line and creae a new node
        while (!feof(file))
        {
            sum++; // for size
            fscanf(file, "%s", word);
            node *node1 = malloc(sizeof(node));
            if( node1 == NULL)
            {
                return false;
            }
            else
            {
                strcpy(node1->word , word);
                node1->next = NULL;
            }
            //hach the node to get a hach value
            int i = hash(word);
            // base case 
            if (table[i] == NULL)
            {
                table[i] = node1;
            }
            //other cases incerting at the front of the list
            else
            {
                node1->next = table[i];
                table[i] = node1;
            }
        }
        
    }
    else
    {
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    sum = sum -1 ;
    return sum;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 26 ; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free (temp);
        }
    }
    return true;
}
