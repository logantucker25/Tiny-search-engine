# implimentation spec for Querier.c

# logan Tucker, Oct 2022
# cs50

## Data structures 
index: a shell around hashtable. creates a table mapping words to
 counters where the counters hold docID's mapped to counts of the
  word.
counters: create a counter of doc IDs to scores to represent the
 reuslt of a query
twocts: copied from assignment page, holds two counter spointers and
 is used to pass in multiple counter adresses in an iteration

## Control flow
main function calls parse args function then gets user input
while tehre is a valid user input provided the main will call
 getResctr and then print results

### 2. parseArgs
ensures the user provides valid page direvtopry path in arg1 and a
 valid index file pathway in arg2

### important functions (non helper functions)

### get result counters
inspired by the pseudo code (from assignment page):

counters_t *result = NULL
counters_t *temp = NULL
Read query one word at a time
    If read a word (not AND or OR)
        find counters for this word in index (index_find(index, word))
        if temp == NULL
            temp = counters for word   //first word in AND sequence
        else
            temp = temp ^ counters for word  //intersect on AND
    else if read OR
        result = result v temp //union on OR
        temp = NULL
    else if read AND
        continue to next word  //implicit AND between words
Return result v temp //union

Things to note:
the code makes sure that the first counter passed into the getintersection and getunion helpers is always the longer of the two

uses helpers:
```c
bool isAnd(char* word);
bool isOr(char* word);

counters_t* getIntersection(counters_t* ctrA, counters_t* ctrB);
counters_t* getUnion(counters_t* ctrA, counters_t* ctrB);

static void iHelper(void *arg, const int key, const int count);
static void uHelper(void *arg, const int key, const int count);

static inline int min(const int a, const int b) { return (a < b ? a : b);}
```


### print result
this method goes through the result counter I create in the previous
 function-> identifies the highest score-> prints the information
  ascosiated with that score-> sets that score to zero within the
   results counter-> searches for next highest score in teh resulst
    counter-> print that info... repeat

uses helpr function: 
```c
static void printRes(counters_t* res, const char* pd);
static void docCount(void* arg, const int key, const int count);
static void maxTrack(void* arg, const int key, const int count);
static void printMax(void* arg, const char* pd);
static void resetMax(void* arg);

int getDocID(void* arg);
int getScore(void* arg);
```
Things to note:
this function uses the data structure 
```c
struct max {
	int max;
	int docID;
};
```

to keep return and track the current highest score pair (score,
 docID) in the result counter

### tokenize
takes in the users query string. turns it into a normalized array
 where each item in the array is a word in the users query

## Testing plan
I write a script `testing.sh` that first tests various valid and
 invalid args. It then runs a series of vairious queries both valid
  and invalid.

The output of my query is sent to the runners stdout


## output 

Query? for or search
Query: for or search 
Matches 6 documents (ranked):
score   2  doc   3: http://cs50tse.cs.dartmouth.edu/tse/letters/B.html
score   2  doc   5: http://cs50tse.cs.dartmouth.edu/tse/letters/D.html
score   1  doc   1: http://cs50tse.cs.dartmouth.edu/tse/letters/index.html
score   1  doc   2: http://cs50tse.cs.dartmouth.edu/tse/letters/A.html
score   1  doc   4: http://cs50tse.cs.dartmouth.edu/tse/letters/E.html
score   1  doc   6: http://cs50tse.cs.dartmouth.edu/tse/letters/C.html
--------------------------------------------------------
Query? for and search
Query: for and search 
Matches 2 documents (ranked):
score   1  doc   3: http://cs50tse.cs.dartmouth.edu/tse/letters/B.html
score   1  doc   5: http://cs50tse.cs.dartmouth.edu/tse/letters/D.html
--------------------------------------------------------
Query? loagn
Query: loagn 
No documents match this query
--------------------------------------------------------
Query? and loagn
invalid use of operators : query cannot begin with an operator
--------------------------------------------------------
Query? logan and search or and tse
invalid use of operators : query cannot have two operators in a row
--------------------------------------------------------
Query? hello
Query: hello 
No documents match this query
--------------------------------------------------------
Query? for or search and tse or eniac or computer
Query: for or search and tse or eniac or computer 
Matches 6 documents (ranked):
score   2  doc   4: http://cs50tse.cs.dartmouth.edu/tse/letters/E.html
score   1  doc   1: http://cs50tse.cs.dartmouth.edu/tse/letters/index.html
score   1  doc   2: http://cs50tse.cs.dartmouth.edu/tse/letters/A.html
score   1  doc   3: http://cs50tse.cs.dartmouth.edu/tse/letters/B.html
score   1  doc   5: http://cs50tse.cs.dartmouth.edu/tse/letters/D.html
score   1  doc   6: http://cs50tse.cs.dartmouth.edu/tse/letters/C.html
--------------------------------------------------------
Query? eniac
Query: eniac 
Matches 1 documents (ranked):
score   1  doc   4: http://cs50tse.cs.dartmouth.edu/tse/letters/E.html
--------------------------------------------------------
Query? computer
Query: computer 
No documents match this query
--------------------------------------------------------
Query? search
Query: search 
Matches 2 documents (ranked):
score   1  doc   3: http://cs50tse.cs.dartmouth.edu/tse/letters/B.html
score   1  doc   5: http://cs50tse.cs.dartmouth.edu/tse/letters/D.html
--------------------------------------------------------
Query? tse
Query: tse 
Matches 1 documents (ranked):
score   1  doc   1: http://cs50tse.cs.dartmouth.edu/tse/letters/index.html
--------------------------------------------------------
Query? 





