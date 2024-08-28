// indexer.c - functions to create an index from crawler output

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "counters.h"
#include "webpage.h"
#include "index.h"
#include "pagedir.h"
#include "word.h"

static void parseArgs(const int argc, char *pageDirectory, char *indexFilename);
index_t* indexBuild(char* pageDirectory);
static void indexPage(index_t* index, webpage_t* page, int docID);
static void ct_delete(void *item);

int main(const int argc, char* argv[]) {
    char *pageDirectory = argv[1];
    char *indexFilename = argv[2];

    parseArgs(argc, pageDirectory, indexFilename);
    index_t* index = indexBuild(pageDirectory);
    index_save(index, indexFilename);
    index_delete(index, ct_delete);
    return 0;
}

static void parseArgs(const int argc, char *pageDirectory, char *indexFilename) {
     // validate it received exactly two command-line arguments
    if (argc != 3) {
        fprintf(stderr, "incorrect num of args\n");
        exit(1);
    }
    // validate pageDirectory is the pathname for a directory produced by the Crawler
    if (!pagedir_validate(pageDirectory)) {
        fprintf(stderr, "invalid page directory\n");
        exit(2);
    }
    // validate indexFilename is the pathname of a file that can be written
    if (fopen(indexFilename, "w") == NULL) {
        fprintf(stderr, "invalid index file\n");
        exit(3);
    }
}

// purpose: builds an in-memory index from webpage files it finds in the pageDirectory
index_t* indexBuild(char* pageDirectory) {
    index_t* index = index_new(999);
    if (index == NULL) {
        fprintf(stderr, "failed to make index\n");
        return NULL;
    }

    // loop through each file in the wp directory and load the page (get it in wp form)
    int i = 1;
    webpage_t* page;
    while ((page = pagedir_load(pageDirectory, i)) != NULL) {
        indexPage(index, page, i);
        webpage_delete(page); // will i have a problem deleting page then reassigning it to pagedirload in the while loop. do i have to tell thhe computer that page is of type webpage again?
        i++;
    }
    return index;
}

// scans a webpage document to add its words to the index
static void indexPage(index_t* index, webpage_t* page, int docID) {
    int pos = 0;
    char* word = webpage_getNextWord(page, &pos);
    
    // go through each word on the webpage greater than 3 letters and mark it as seen or seen again in the index
    while (word != NULL) {
        if (strlen(word) > 3) {
            if ((word = normalize(word)) != NULL) {
                counters_t* ctr;
                if ((ctr = index_find(index, word)) == NULL) {
                    if ((ctr = counters_new()) != NULL) {
                        index_insert(index, word, ctr);
                    }
                }
                counters_add(ctr, docID);
            }
        }
        free(word);
        word = webpage_getNextWord(page, &pos);
    }
    free(word);
}

/******** delete counters item ********/
static void ct_delete(void *item)
{
	counters_t* ct = item;

	if (ct != NULL) {
		counters_delete(ct);
	}
}

