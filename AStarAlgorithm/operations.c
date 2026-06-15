#include <string.h>
#include "operations.h"
#include "database.h"

int heuristicFun(const char word1[], const char word2[]) {
    int result = 0;

    for(int i = 0; i < WORD_LENGTH; i++) {
        if(word1[i] != word2[i]) {
            result++;
        }
    }

    return result;
}

int heuristicFunInadmissivel(const char word1[], const char word2[]) {
    int result = 0;

    for(int i = 0; i < WORD_LENGTH; i++) {
        int diff = word1[i] - word2[i];
        
        if(diff < 0) {
            diff = -diff;
        }
        
        result += diff;
    }

    return result;
}

int searchForWord(const char word[]) {
    int left = 0;
    int right = NUM_GUESSES - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(word, VALID_GUESSES[mid]);

        if (cmp == 0) {
            return mid;
        }

        if (cmp > 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}