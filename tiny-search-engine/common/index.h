// index.h - wrapper of hashtable - index data type

// Logan Tucker, October 2022
// CS 50, Fall 2022

#ifndef __index_H
#define __index_H

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "counters.h"

typedef hashtable_t index_t;

index_t* index_new(const int num_slots);

bool index_insert(index_t* index, const char* key, counters_t* counters);

counters_t* index_find(index_t* index, const char* key);

void index_iterate(index_t* index, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );

void index_delete(index_t* index, void (*itemdelete)(void* item) );

index_t* index_load(const char *indexFilename);

void index_save(index_t *index, const char *indexFilename);

void save_item (void *arg, const char *key, void *item);

void save_counts (void *arg, const int key, int count);

#endif 