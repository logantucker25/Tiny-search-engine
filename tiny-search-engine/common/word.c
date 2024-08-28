// word.c - normalize a word given as s string

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* normalize(char* word) {
    if (word == NULL) {
        return NULL;
    }

    // lower case the uppercase letters in the word in place
    for (int i = 0; i < strlen(word); i++) {
        if(isalpha(word[i]) && !islower(word[i])) {
            word[i] = tolower(word[i]);
        } 
    }
    return word;
}
