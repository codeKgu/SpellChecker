/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"


static node *root;
int word_count;

bool check(const char *word)
{
    node* trav = root;
    int index = 0;
    for (int i = 0; i < strlen(word); i++ )
        { 
            index = tolower(word[i]);
            if (index == 39)
                index = 123;
            index = index- 97;
                
            if (trav->children[index] == NULL)
                return false;
            else
                trav = trav -> children[index];
        }
    if (trav -> is_word == true)
        return true;
    else 
        return false;
}

static void init_node(node *cur)
{
    for (int i = 0; i < 27; i++)
    {
        cur->children[i] = NULL;
    }
    cur->is_word = false;
}    
bool load(const char *dictionary)
{
    word_count = 0;   
    FILE *ptr = fopen(dictionary, "r");
    if (ptr == NULL)
    {
        return false;
    }
    
    root = malloc (sizeof(node));
    init_node(root);
    
    int index = 0;
    char word[46];
     
    for (int c = fgetc(ptr); c != EOF; c = fgetc(ptr))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            index++;
        }
        else if (index > 0)
        {
            word[index] = '\0';
            node* head = root;
            
            for (int i = 0, len = strlen(word) ; i < len ; i++ )
            { 
                int count = word[i]; 
                if (count == 39)
                    count = 123;
                count -=97;
                
                    
                if (head->children[count] == NULL)
                {
                    node* child  = malloc (sizeof(node));
                    if (child == NULL)
                        return false;
                    
                    init_node(child);
                    head -> children[count] = child;
                    head = child;
                }
                else
                {
                    head = head -> children[count];
                }
            }
            head -> is_word = true;
            word_count++;
            index = 0;
        }
    }  
    fclose(ptr);
    return true;
}

/**        
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void) 
{
    unload_recursion(root);
    free(root);
    return true;
}

void unload_recursion(struct node *cur)
{
    node *child;
    for (int i = 0; i <27; i++)
    {
        child = cur->children[i];
        if (child != NULL)
        {
            unload_recursion(child);
            free(child);
        }
    }
    return;
}















