/*
 *  CommonWords.h
 *  
 *
 *  Created by Michael on 2/6/12.
 *
 */



//One word node, ppoointing to the string
//and to the next node
typedef struct WordNode
{
    char* word;
    struct WordNode* next;
} WordNode;

//Word list with a start and length
typedef struct WordList
{
    WordNode* first;
    WordNode* last;
    int len;
} WordList;
/*Function Prototypes */
WordNode* createNode(char*,int);
void addNode(WordList*,WordNode*);
WordList* copyList(WordList*);

void freeNode(WordNode*);
void freeList(WordList*);

WordList* getCommonWords(char*);
void splitLine(char*,int,WordList*);
void constructList(WordList*);
WordNode* copyNodeToMem(WordNode*,WordNode*);
