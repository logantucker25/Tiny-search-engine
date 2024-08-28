// indextest.c - test the accuracy of indexer.c and index.c

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdlib.h>
#include <stdio.h>
#include "index.h"
#include "file.h"
#include "hashtable.h"
#include "counters.h"

static void parseArgs(const int argc, index_t* index);

// purpose: take a text file of index info.. make an index from it.. print that index to a text file.. compare the two text files
// if they are the same then the indexer and index.c accuratley create indexs
int main(const int argc, char* argv[]) {
    index_t* index = index_new(999);
    parseArgs(argc, index);

    char *prevIndexOut = argv[1];
    char *newIndexOut = argv[2];

    if ((index = index_load(prevIndexOut)) != NULL) {
        index_save(index, newIndexOut);
        return 0;
    }
    return 1;
}

static void parseArgs(const int argc, index_t* index) {
    if (index == NULL) {
        fprintf(stderr, "index failed to make");
        exit(1);
    }
    if (argc != 3) {
        fprintf(stderr, "incorrect num of args");
        exit(2);
    }
}
