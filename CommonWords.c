/*
 *  CommonWords.c
 *  
 *
 *  Created by Michael on 2/6/12.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CommonWords.h"




/* Parses the given file and return an array lists of words, one per letter of the alphabet.
 * List is null-pointer list of strings terminated.
 *
 */
WordList* getCommonWords(char* fileNm)
{
    WordList* common = (WordList*)malloc(sizeof(WordList)*26);
    int i = 0;
    //Build 26 lists
    for (i =0; i<26; i++)
        constructList(&common[i]);
    char buffer[8192];
    //Open the file
    FILE * file = fopen(fileNm,"r");
    if (file == NULL)
        return NULL;
    //Loop reading lines
    while (!feof(file))
    {
        char* line = fgets(buffer,sizeof(buffer),file);
        //Try and ignore errors by breaking
        if (line == NULL || ferror(file))
            break;
        //Break up line and add it to our lists
        splitLine(line,sizeof(buffer),common);
    }
    fclose(file);
    return common;
}
/* Split up a word based on the "\n","\0","," characters. Then apply
 * algorithm to determine the first letter, and put the word in that list.
 * line - line to split
 * maxLen - maximum length of line (buffer length)
 * lists - array of 26 lists one per character
 */
void splitLine(char* line,int maxLen,WordList* lists)
{
    char* last = line;
    while ((*last) != '\n' && (*last) != '\0'  && (last - line) < maxLen)
    {
        char* next = strchr(last,',');
        //Find the nex , \n or \0 to tokenize the line
        if (next == NULL)
            next = strchr(last,'\n');
        if (next == NULL)
            next = strchr(last,'\0');
        if (next == NULL)
            break;
        int len = next - last - 1;
        WordNode* node = createNode(last,len);
        if (node != NULL)
            addNode(&lists[node->word[0]-97],node);
        last = next+1;
    }
}
/* Initialize the list.
 * returns nothing.
 */
void constructList(WordList* list)
{
    list->len = 0;
    list->first = NULL;
    list->last = NULL;
    
}

/* Creates a node containing a pointer to the next node,
 * and the word (copies word).
 * word - char* to the word in memory
 * return - NULL on error, pointer to Node
 */
WordNode* createNode(char* word, int len)
{
    //Get size of word, error on invalid size
    if (len <= 0)
        return NULL;
    //Allocate memory, fail if malloc fails, and copy word
    char* dest = (char*)malloc((len*+1)*sizeof(char));
    if (dest == NULL)
        return NULL;
    memcpy(dest,word,len+1);
    int i = 0;
    for (i = 0; i < len; i++)
        dest[i] = tolower(dest[i]);
    //Allocate memory for node, fail and clean up if malloc fails
    WordNode* node = (WordNode*) malloc(sizeof(WordNode));
    if (node == NULL)
    {
        free(dest);
        return NULL;
    }
    //Return the node
    node->word = dest;
    node->next = NULL;
    return node;
}

/* Adds a node to a WordList.
 * 
 */
void addNode(WordList* list, WordNode* node)
{
    //Can't add to a null list
    if (list == NULL)
        return;
    //Attach first node
    if (list->last == NULL && list->first == NULL)
        list->first = node;
    else
        list->last->next = node;
    list->last = node;
    list->len++;
}

/* Free node */ 
void freeNode(WordNode* node)
{
    //Can't free NULL
    if (node == NULL)
        return;
    //Free the word, set its pointer to NULL to prevent erroneous accesses
    free(node->word);
    node->word = NULL;
    free(node);
}
/* Free the list*/
void freeList(WordList* list)
{
    //Can't free NULL
    if (list == NULL)
        return;
    //Free until a NULL node is found
    WordNode* node = list->first;
    while (node != NULL)
    {
        //Capture next, free, and set pointer to NULL, and prepare to loop
        WordNode* tmp = node->next;
        free(node);
        node = NULL;
        node = tmp;
    }
}
/* Deep copy a list, pre-allocating memory to ensure a compact block. 
 * list - wordlist to copy
 * return - pointer to new list or NULL on error
 */
WordList* copyList(WordList* list)
{
    //A NULL list would remain null
    if (list == NULL)
        return NULL;
    //Allocate all nodes at once and return null on fail, make sure memory is clear 
    //So later uses of the nodes all reference NULL as next
    WordList* new = (WordList*) malloc(sizeof(WordList));
    if (new == NULL)
        return NULL;
    WordNode* nodes = (WordNode*)calloc(list->len,sizeof(WordNode));
    if (nodes == NULL)
    {
        free(new);
        return NULL;
    }
    //Copy each node, on fail free all memory
    int i = 0;
    WordNode* node = list->first;
    new->first = nodes;
    while (node != NULL)
    {
        WordNode* newNode = copyNodeToMem(node,&nodes[i]);
        //Error check that the copy went well
        if (newNode == NULL)
        {
            freeList(new);
        }
        newNode->next=&nodes[++i];
    }
    //Reset the last node to point at NULL, first to be first, and last to be last
    nodes[i-1].next = NULL;
    new->last = &nodes[i-1];
    return new;
}
/* Deep copy a node to given memory, return NULL on failure.
 * node - node being copied
 * dest - memory location to fill
 * return - fresh node or NULL on failure
 */
WordNode* copyNodeToMem(WordNode* node,WordNode* dest)
{
    //Get size of word, error on invalid size
    int len = strlen(node->word);
    if (len <= 0)
        return NULL;
    //Allocate memory, fail if malloc fails, and copy word
    char* new = (char*)malloc((len*+1)*sizeof(char));
    if (new == NULL)
        return NULL;
    memcpy(new,node->word,len+1);
    dest->word = new;
    dest->next = NULL;
    return node;
}
