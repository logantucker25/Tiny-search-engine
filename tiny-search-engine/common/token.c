// token.c - return an array of strings where eacch item is a word in a string given to the func 

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word.h"
#include <ctype.h>

void* tokenize(char** tokens, char* string) {

    for (char* start = string; *start != '\0'; start ++) {
        if (!isalpha(*start) && !isspace(*start)) {
            return NULL;
        }
    }

    int count = 0;
    for (char* rest = string; *rest != '\0'; ) {
        char* word;
        for (word = rest; *word != '\0' && isspace(*word); word++) {
        }
        for (rest = word; *rest != '\0' && isalpha(*rest); rest++) {
        }
        if (*rest != '\0') {
            *rest++ = '\0';
        }
        if (*word != '\0') {
            tokens[count++] = normalize(word);
        }
    }

    return tokens;
}

