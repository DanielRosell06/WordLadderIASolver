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