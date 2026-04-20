#include <string.h>
#include "operations.h"
#include "database.h"

int heuristicFun(const char word1[], const char word2[]) {
    int result = 0;

    for(int i = 0; i < WORD_LENGTH; i++) {
        if(word1[i] == word2[i]) {
            result++;
        }
    }

    return result;
}

int searchForWord(const char word[]) {
    for(int i = 0; i < NUM_GUESSES; i++){
        if(strcmp(word, VALID_GUESSES[i]) == 0){
            return i;
        }
    }
    return -1;
}