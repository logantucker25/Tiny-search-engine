// pagedir.c - handle the webpage directory

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "webpage.h"
#include "file.h"


// purpose: create a directory to hold webpages
bool pagedir_init(const char* pageDirectory) {
    // create file pathway
    char path[strlen(pageDirectory) + 10];
    sprintf(path, "%s/.crawler", pageDirectory);
    
    // try to open file pathway
    FILE* f = fopen(path,"w");

    // return true if pathway opened succesfully, and false otherwise
    if (f != NULL) {
        fclose(f);
        return true; 
    } else {
        return false;
    }
}

// purpose: make a file in pageDirectory for a discovered web page and print to it that webpages information
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {    
    // create file pathway
    char path[strlen(pageDirectory) + 15];
    sprintf(path, "%s/%d", pageDirectory, docID);
    
    // if file pathway opens successfully print webpage information to it
    FILE* f = fopen(path,"w");
    if (f != NULL) {
        fprintf(f, "%s\n%d\n%s", webpage_getURL(page), webpage_getDepth(page), webpage_getHTML(page));
        fclose(f);
    }
}

// pagedir_validate(dir) to verify whether dir is indeed a Crawler-produced directory
bool pagedir_validate(char* pageDirectory) {
    char path[strlen(pageDirectory) + 10];
    sprintf(path, "%s/.crawler", pageDirectory);

    FILE* f = fopen(path,"r");
    if (f != NULL) {
        fclose(f);
        return true; 
    } else {
        return false;
    }
}

// pagedir_load to load a page from a file in that directory.
webpage_t* pagedir_load(char* pageDirectory, int docID) {
    char path[strlen(pageDirectory) + 10];
    sprintf(path, "%s/%d", pageDirectory, docID);

    FILE* fp = fopen(path,"r");
    if (fp == NULL) {
        return NULL; 
    } 

    char* url = file_readLine(fp);
    if (url == NULL || strcmp(url, "") == 0) {
        return NULL;
    }

    char* depth = file_readLine(fp);
    if (depth == NULL || strcmp(depth, "") == 0) {
        return NULL;
    }
    int d = atoi(depth);
    free(depth);

    webpage_t* wp = webpage_new(url, d, NULL);
    if (wp == NULL ) {
        return NULL;
    }

    if (!webpage_fetch(wp)) {
        return NULL;
    }

    return wp; 
}


