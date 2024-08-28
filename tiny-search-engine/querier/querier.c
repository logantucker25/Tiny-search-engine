// querier.c - return ranked web results from given query

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "index.h"
#include "token.h"
#include "counters.h"
#include <webpage.h>
#include "pagedir.h"
#include <unistd.h>
#include "file.h"
#include <ctype.h>

static void parseArgs(const int argc, char* argv[]);
static void printTokens(char** tokens, int numTokens);
bool validateOperators(char** tokens, int numTokens);
counters_t* getResCtr(index_t* index, char** tokens, int numTokens);

bool isAnd(char* word);
bool isOr(char* word);

counters_t* getIntersection(counters_t* ctrA, counters_t* ctrB);
counters_t* getUnion(counters_t* ctrA, counters_t* ctrB);

static void iHelper(void *arg, const int key, const int count);
static void uHelper(void *arg, const int key, const int count);

static inline int min(const int a, const int b) { return (a < b ? a : b);}

static void printRes(counters_t* res, const char* pd);
static void docCount(void* arg, const int key, const int count);
static void docCountZERO(void* arg, const int key, const int count);
static void maxTrack(void* arg, const int key, const int count);
static void printMax(void* arg, const char* pd);
static void resetMax(void* arg);

int getDocID(void* arg);
int getScore(void* arg);

// purpose: the tw functions below are used to iterate through a given counter and save its values in a copy. 
// this allows the same words to be queried for multiple times in a row without changing their values in the index
static void itemCopy(void *arg, const int key, const int count) {
    counters_t* copy = arg; 
    counters_set(copy, key, count); 
}

counters_t* makeCopyOf(counters_t* ctr) {
    counters_t* copy = counters_new();
    if (copy == NULL) {
        fprintf(stderr, "failed to get new counter\n");
        exit(99);
    }

    counters_iterate(ctr, copy, itemCopy);
    return copy;
}

/******** delete counters item ********/
static void ct_delete(void *item)
{
	counters_t* ct = item;

	if (ct != NULL) {
		counters_delete(ct);
	}
}

// purpose: gets input from user based on whether the it is from stdin or another location
char* getInput(void) {
  int fileno(FILE *stream);
  if (isatty(fileno(stdin))) {
    printf("Query? ");
  }
  return file_readLine(stdin);
}

// purpose: counts the number of token that will be derived from a query
// this allows me to allocate the exact amount of slots needed in the token array of strings
int getNumTokens(char* string) {
    int num = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (i == 0 && !isspace(string[i])) {
            num ++;
        }
        if (isspace(string[i]) && !isspace(string[i+1])) {
            num++;
        }
    }
    return num;
}

// purpose: a data structure that holds two counters, this is used durring my get union and get intersection function
struct twocts {
	counters_t *result;
	counters_t *another;
};

// purpose: return the result counter in a given twocts struct
counters_t* getTwoCtsResult(void *arg) {
    struct twocts *two = arg;
    if (arg != NULL) {
        return two->result;
    }
    return NULL;
}

// purpose: data structure to hold a score and a corresponding docID
// used when ranking the results to find the current max score and ccorresponsing docID
struct max {
	int max;
	int docID;
};

int main(const int argc, char* argv[]) {
    parseArgs(argc, argv);
    char *pageDirectory = argv[1];
    char *indexFilename = argv[2];

    index_t* index;
    if (( index = index_load(indexFilename)) == NULL) {
        fprintf(stderr, "failed to load index\n");
        return 4;
    }

    // run program each time there is a query provided
    char* query;
    while ((query = getInput()) != NULL) {

        // save query as tokens (an array of strings)
        int numTokens = getNumTokens(query);
        char* tokens[numTokens];
        
        if ((tokenize(tokens, query)) == NULL) {
            fprintf(stderr, "failed to tokenize your query\n");
            index_delete(index, ct_delete);
            return 5;
        } 

        // check if search operators were used correctly
        if (validateOperators(tokens, numTokens)) {
            printTokens(tokens, numTokens);

            // make results counter
            counters_t* res = getResCtr(index, tokens, numTokens);
            printRes(res, pageDirectory);
        }
        free(query);
        printf("--------------------------------------------------------\n");
    }
    index_delete(index, ct_delete);
    return 0;
}

// purpose: check if user provided proper args the programs proper use is ./querier (index file name) (page directory)  
static void parseArgs(const int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "incorrect num of args\n");
        exit(1);
    }
    if (!pagedir_validate(argv[1])) {
        fprintf(stderr, "invalid page directory\n");
        exit(2);
    }
    FILE* fp = fopen(argv[2], "r");
    if (fp == NULL) {
        fprintf(stderr, "invalid index file\n");
        exit(3);
    }
    fclose(fp);
}

// purpose: check for leading, trailing or double operator words (and/or)
bool validateOperators(char** tokens, int numTokens) {
    if (isAnd(tokens[0]) || isOr(tokens[0])) {
        fprintf(stderr, "invalid use of operators : query cannot begin with an operator\n");
        return false;
    }
    if (isAnd(tokens[numTokens - 1]) || isOr(tokens[numTokens - 1])) {
        fprintf(stderr, "invalid use of operators : query cannot end with an operator\n");
        return false;
    }
    for (int i = 0; i < numTokens - 1; i++) {
        if (isAnd(tokens[i]) || isOr(tokens[i])) {
            if (isAnd(tokens[i + 1]) || isOr(tokens[i + 1])) {
                fprintf(stderr, "invalid use of operators : query cannot have two operators in a row\n");
                return false;
            }
        }
    }
    return true;
}

// purpose: read back the users query in token form
static void printTokens(char** tokens, int numTokens) {
    printf("Query: ");
    for (int i = 0; i < numTokens; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n");
}

// purpose: get a counter of doc ids and counts for the query tokens
counters_t* getResCtr(index_t* index, char** tokens, int numTokens) {
    counters_t* res = NULL;
    counters_t* tmp = NULL;
    counters_t* cpy = NULL;

    // for each token
    for (int i = 0; i < numTokens; i++) {
        
        // if token is a non operator word
        if (!isAnd(tokens[i]) && !isOr(tokens[i])) {
            if (tmp == NULL) {
                tmp = makeCopyOf(index_find(index, tokens[i]));
            }
            else {

                // find the longest of counter between the tmp and the current token's counter and call 
                // get intersection such that the longer counter is put in first and thus iterated through
                int tmpLength = 0;
                int newLength = 0;

                counters_iterate(tmp, &tmpLength, docCount);
                counters_iterate(index_find(index, tokens[i]), &newLength, docCount);

                if (tmpLength >= newLength) {
                    tmp = getIntersection(tmp, index_find(index, tokens[i]));
                }
                else if (newLength > tmpLength) {
                    cpy = makeCopyOf(index_find(index, tokens[i]));
                    tmp = getIntersection(cpy, tmp);
                }
            }
        }
        else if (isOr(tokens[i])) {
            int tmpLength = 0;
            int resLength = 0;

            counters_iterate(tmp, &tmpLength, docCount);
            counters_iterate(res, &resLength, docCount);

            if (tmpLength >= resLength) {
                res = getUnion(tmp, res);
            }
            else if (resLength > tmpLength) {
                res = getUnion(res, tmp);
            }

            tmp = NULL;
        }
    }
    int tmpLength = 0;
    int resLength = 0;

    counters_iterate(tmp, &tmpLength, docCount);
    counters_iterate(res, &resLength, docCount);

    if (tmpLength >= resLength) {
        res =  getUnion(tmp, res);
    }
    else if (resLength > tmpLength) {
        res = getUnion(res, tmp);
        counters_delete(tmp);
    }

    return res;
}

// purpose: check if a given token is and or or
bool isAnd(char* word) {
    char* and = "and";
    if (strncmp(word, and, 3)==0) {
        return true;
    }
    return false;
}
bool isOr(char* word) {
    char* or = "or";
    if (strncmp(word, or, 2)==0) {
        return true;
    }
    return false;
}

// purpose: get the intersection or union values of two given ctr A and B and store the result in ctr A
counters_t* getIntersection(counters_t* ctrA, counters_t* ctrB) { 
    struct twocts arg = {ctrA, ctrB};
    counters_iterate(ctrA, &arg, iHelper);
    return getTwoCtsResult(&arg);
}
counters_t* getUnion(counters_t* ctrA, counters_t* ctrB) { 
    struct twocts arg = {ctrA, ctrB};
    counters_iterate(ctrA, &arg, uHelper);
    return getTwoCtsResult(&arg);
}

// purpose: set the new values of ctr A as the iterators go through each value of the longer ctr (ctr A)
static void iHelper(void *arg, const int key, const int count) {
    struct twocts *two = arg; 
    // set count to the min of the two counts
    counters_set(two->result, key, min(count, counters_get(two->another, key))); 
}
static void uHelper(void *arg, const int key, const int count) {
    struct twocts *two = arg; 
    // set count to the sum of the two counts
    counters_set(two->result, key, (count + counters_get(two->another, key))); 
}

// purpose: print the results of the query in order of greatest score
static void printRes(counters_t* res, const char* pd) {
    bool headerPrinted = false;
    int numDocs = 0;
    counters_iterate(res, &numDocs, docCountZERO);

    // if there are no items in the result counter print "no res"
    if (numDocs == 0) {
        printf("No documents match this query\n");
        counters_delete(res);
        return;
    } 

    struct max mx = {0, 0};
    
    for (int i = 0; i < numDocs; i++) {
        // struct max mx = {0, 0};
        // iterate through teh result ccounter and save the max score item in the max struct
        counters_iterate(res, &mx, maxTrack);
        // if there are no scores in the result counter print "no res"
        // this can be found by checking if the first max found is zero
        if (getScore(&mx) == 0 && i == 0) {
            printf("No documents match this query\n");
            counters_delete(res);
            return;
        }
        else if (!headerPrinted) {
            printf("Matches %d documents (ranked):\n", numDocs);
            headerPrinted = true;
        } 
        printMax(&mx, pd);
        // set that items score to zero so it will not be the max again and will not be printed twice
        counters_set(res, getDocID(&mx), 0);
        resetMax(&mx);
    }
    counters_delete(res);
}

// purpose: get the number of items in a counter
static void docCount(void* arg, const int key, const int count) { // only count if score above zerot o avoid false reuslt 
    int* nDocs = arg;

    if (nDocs != NULL) {
        (*nDocs)++;
    }
}

// purpose: get the number of items in a counter EXCLUDE ZEROS
static void docCountZERO(void* arg, const int key, const int count) { // only count if score above zerot o avoid false reuslt 
    int* nDocs = arg;

    if (nDocs != NULL && count != 0) {
        (*nDocs)++;
    }
}

// purpose: get the max counter value in a counter and save it in a given max struct
static void maxTrack(void* arg, const int key, const int count) {
    struct max* m = arg;

    if (m != NULL) {
        if (count > m->max) {
            m->max = count;
            m->docID = key;
        }
    }
}

// purpose: return info from a max struct
int getDocID(void* arg) {
    struct max* m = arg;
    return m->docID;
}
int getScore(void* arg) {
    struct max* m = arg;
    return m->max;
}

// purpose: print info of a current max result
static void printMax(void* arg, const char* pd) {
    struct max* m = arg;
    if (m->max > 0) {
        printf("score   %d  ", m->max);
        printf("doc   %d: ", m->docID);
    }

    char path[strlen(pd) + 10];
    sprintf(path, "%s/%d", pd, m->docID);

    FILE* fp = fopen(path,"r");
    if (fp != NULL) {
        char* url = file_readLine(fp);
        if (url != NULL || strcmp(url, "") == 0) {
            printf("%s\n", url);
            free(url);
        }
    
        fclose(fp);
    } 
}

// purpose: resest max structs values to zero so that it can ID the next greatest max in the result counter
static void resetMax(void* arg) {
    struct max* m = arg;
    m->max = 0;
    m->docID = 0;
}