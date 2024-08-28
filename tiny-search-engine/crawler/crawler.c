// crawler.c - handle the collection of webpage information

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "bag.h"
#include "webpage.h"
#include "pagedir.h"
#include "math.h"

// log one word (1-9 chars) about a given url                                   
static void logr(const char *word, const int depth, const char *url)
{
    printf("%d   %s: %s\n", depth, word, url);
}

// declare static funcs
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

int main(const int argc, char* argv[]) {
    // save pointers to args for passing into ther functions
    char *seedURL = calloc(strlen(argv[1]) + 1, sizeof(char));
    char *pageDirectory = argv[2];
    int maxDepth;

    // check if args are valid and then crawl
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);
    
    // if crawl rans successfully return 0
    return 0;
}

// purpose: check if command line args are valid
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    *seedURL = normalizeURL(argv[1]);
    if (*seedURL == NULL) {
        printf("1");
        fprintf(stderr, "url could not be normalized");
        exit (1);
    }
     if (!isInternalURL(*seedURL)) {
        printf("2");
        fprintf(stderr, "url is not internal");
        exit (2);
    }
     if (!pagedir_init(*pageDirectory)) {
        printf("3");
        fprintf(stderr, "failed to initiate page directory");
        exit (3);
    }
    if (argc != 4) {
        printf("4");
        fprintf(stderr, "error invalid number of args");
        exit (4);
    }
    char excess;
    if (sscanf(argv[3], "%d%c", maxDepth, &excess) != 1) {
        printf("5");
        fprintf(stderr, "error invalid");
        exit (5);
    } else if (*maxDepth > 10 || *maxDepth < 0) {
        printf("6");
        fprintf(stderr, "depth out of range");
        exit (6);
    }
}

// purpose: crawl pages and their linked pages
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) {
    
    // create data storage
    hashtable_t*  pagesSeen = hashtable_new(500);
    bag_t* pagesToCrawl = bag_new();

    // check if data storage is created successfully
    if (pagesSeen != NULL && pagesToCrawl != NULL) {
        

        // add seedURL to pagesToCrawl
        int depth = 0;
        webpage_t* seedPage = webpage_new(seedURL, depth, NULL);
        if (webpage_fetch(seedPage)) {
            logr("Fetched", webpage_getDepth(seedPage), webpage_getURL(seedPage));
        } else {
            fprintf(stderr, "could not fetch seed");
            exit(7);
        }
        bag_insert(pagesToCrawl, seedPage);
        hashtable_insert(pagesSeen, seedURL, "");
        webpage_delete(seedPage);
        // free(seedURL);
        
        // start labeling documents with a value of 1
        int docID = 0;

        // loop next code while there are stil pages in pagesToCrawl bag
        webpage_t* page = bag_extract(pagesToCrawl);
            while (page != NULL) {

                // save found page to the webpage directory
                docID += 1;
                char key[(int) log10(docID) + 1];
                sprintf(key, "%d", docID);
                pagedir_save(page, pageDirectory, docID);
                logr("added", webpage_getDepth(page), webpage_getURL(page));
                

                // if the crawler is not yet at max depth, continue searching urls
                if (webpage_getDepth(page) < (maxDepth) - 1) {
                    
                    pageScan(page, pagesToCrawl, pagesSeen);
                }
                // get next page to crawl
                
                webpage_delete(page);
                page = bag_extract(pagesToCrawl);
            }
            hashtable_delete(pagesSeen, NULL);
            bag_delete(pagesToCrawl, webpage_delete);
    }
}

// purpose: scan web pages for urls
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {
    logr("scanning", webpage_getDepth(page), webpage_getURL(page));
    int pos = 0;
    char* url = webpage_getNextURL(page, &pos);
    int depth = webpage_getDepth(page);

    // while there are still urls on this page to be discovered
    while (url != NULL) {
        if (isInternalURL(url)) {
            depth += 1;
            webpage_t* discPage = webpage_new(url, depth, NULL);
            webpage_fetch(discPage);
            if (hashtable_insert(pagesSeen, url, "")) {
                logr("Found", webpage_getDepth(discPage), webpage_getURL(discPage));

                // if ths url's page has never been seen before
                bag_insert(pagesToCrawl, discPage);
                
            } else {
                free(url);
            }
            webpage_delete(discPage);
        }
        free(url);
        url = webpage_getNextURL(page, &pos);
    }
    free(url);
}





