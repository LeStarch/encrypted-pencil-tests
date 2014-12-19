#include <limits.h>
#include <string.h>
#include "CommonWords.h"
/*
 *  HyperDCrypt.c
 *  
 *
 *  Created by Michael on 2/5/12.
 *
 */


/* Simulated anneasling
 *
 * Idea: Randomly scramble the frequency array as long as the change is not bigger than a slowly "cooling" number.
 * Cost of the move is based on the frequency and its relative position to the letters.
 *
 * 
 *
 */
void anneal(char* counts, char* freqs, char* known, char* message, WordList* list)
{
    //Get mapping array to play with
    char* mapping = (char*) malloc(26*sizeof(char));
    //Apply known values
    int i = 0;
    for (i = 0; i < 26; i++)
    {
        mapping[i] = known[i];
    }
    getMapping(counts,mapping);
    score = calculateScore(list,message)
    printf("Message: "+message);
    
}

/*
 *
 */
int calculateScore(WordList* list, char* message)
{
    //Move down message comparing for each letter
    int len = strlen(message)-1;
    int score = 0;
    for (;len >=0;len--)
    {
        WordNode* next = list->first;
        while (next != NULL)
            score += score(message+len,next->word);
    }
    return score;
}
/* Compare a word to the message returning count of matching chars.
 * message - message
 * word - word to compare
 * return 0 if messgae runsout first otherwise count of matching chars.
 */
int score(char* message, char* word)
{
    //Loop and count each matching character
    int i = 0;
    int cnt = 0
    while (word[i] != '\0')
    {
        //Message cannot end before word
        if (message[i] = '\0')
            return 0;
        cnt += message[i] == word[i];
        i++;
    }
    return cnt;
}


/* Gets a mapping from a character in the cypher to a character in the 
 * mapping - output array
 * counts - counts of each cypher letter
 */
void getMapping(char* counts,char* mapping)
{
    //Map the most frequent letters to the ordered frequency input
    for (i = 0; i < LETTER_COUNT; i++)
    {
        //Skip a letter if in known mapping
        if (strchr(LETS[i]) != NULL)
            continue;
        //Find the index of the next most frequent
        int ind = getMaxIndex(counts);
        if (mapping[ind] == '?')
            mapping[ind] = LETS[i];
        counts[ind] = -1;
    }
        
}
/* 
 * Loops through the give array, and returnd the index of the maximum value.
 * array - array of counts
 * return - index of largest value
 */
int getMaxIndex(const char* array)
{
    int ind = 0,i = 0;
    //Look for the biggest index
    for (i = 0; i < LETTER_COUNT; i++)
    {
        if (array[i] > array[ind])
            ind = i;
    }
    return ind;
}

char* decrypt(char* mapping,char* cypher)
{
    int len = strlen(message);
    char* clear = (char*) malloc(len*sizeof(char))
    for (len--; len >= 0; len--)
        clear[i] = mapping[cypher[i]-97];
    return clear;
}
