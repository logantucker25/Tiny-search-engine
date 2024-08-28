// .h file for pagedir.c

// Logan Tucker, October 2022
// CS 50, Fall 2022

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"

bool pagedir_init(const char* pageDirectory);

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

bool pagedir_validate(char* pageDirectory);

webpage_t* pagedir_load(char* pageDirectory, int docID);

#endif // __PAGEDIR_H