// index.c - wrapper of hashtable - index data type

// Logan Tucker, October 2022
// CS 50, Fall 2022

#include "hashtable.h"
#include "counters.h"
#include "file.h"
#include "index.h"
#include <string.h>

index_t* index_new(const int num_slots) {
    return hashtable_new(num_slots);
}

bool index_insert(index_t* index, const char* key, counters_t* counters) {
    return hashtable_insert(index, key, counters);
}

counters_t* index_find(index_t* index, const char* key) {
    return hashtable_find(index, key);
}

void index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
    hashtable_iterate(index, arg, itemfunc);
}

void index_delete(index_t* index, void (*itemdelete)(void* item) ) {
    hashtable_delete(index, itemdelete);
}

// purpose: load an index info from a text file into the index data type
index_t* index_load(const char *indexFilename) {
    FILE *fp = fopen(indexFilename, "r");
    if (fp != NULL) {
        // if the file has content
        if (file_numLines(fp) > 0) {
            index_t* newIndex= index_new(999);
            char* word;
            while ((word = file_readWord(fp)) != NULL) {
                // get word from webpage
                if (strlen(word) > 0) {
                    // collect occurance info of this word
                    counters_t* ctr = counters_new();
                    int id, count;
                    while (fscanf(fp, " %d %d", &id, &count) == 2) {
                        //place occurance info into a counter
                        counters_set(ctr, id, count);
                    }
                    // insert word and its occurnace info into the index
                    index_insert(newIndex, word, ctr);  
                }

                free(word);
            }

            fclose(fp);
            return newIndex;
        }
        fclose(fp);  
	}
    return NULL;
}

// purpose: save index from an index data type to a text file 
void index_save(index_t *index, const char *indexFilename) {  
    FILE *fp = fopen(indexFilename, "w");
    if (fp != NULL) {
        // loop throuugh index and save each item (slot) to the text file
		hashtable_iterate(index, fp, save_item);
	    fclose(fp); 
	}
}

/******** helper to save item in hashtable ********/
// taken from cs50 actvities mon oct 15
void save_item (void *arg, const char *key, void *item)
{
	FILE *fp = arg; 
	counters_t *c = item;

	fprintf(fp, "%s", key);
	counters_iterate(c, fp, save_counts);
	fprintf(fp, "\n");
}

/******** helper to save items in counters ********/
void save_counts (void *arg, const int key, int count)
{
	FILE *fp = arg; 
	fprintf(fp, " %d %d", key, count);
}


