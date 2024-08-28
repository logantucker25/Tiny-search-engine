# CS50 TSE Querier - Logan Tucker
## Design Specification

depends on crawler and indexer files to produce accurate
 indexes and page directories. This program takes a page 
 directory and indexfile as arguments then uses that 
 information to provide answers to queries of the user. The 
 user provdes queries in the format [[word] [and/or] [word]]
  and the queries provides urls tto websites wich include 
  those words, ranked by relevancy.

### User interface

when prompted with "Query?" the user provdides words 
opttionally connected by a single operator (and/or). a query 
cannot begin / end with an operator or have two operators in 
a row.

program is run in command line as such:
./querier "path to page directory" "path to index file"

### Inputs and outputs
**Input**: scources urls for outtput from the page directory
 path name in argv[1]. creates an index of all the page 
 directories word data from teh index file in argv[2]. then 
 takes input of query through user input in stdin.

### Functional decomposition into modules
1. *main*, which parses arguments and calls other mosules
 while there is a valid query provided
 2. *tokenize*, turns user input from single sting to cleaned
  array of strings
 2. *getResCtr*, calls a series of helper functions to get 
 accurately calculated counter of webpages and ther counts of
  the query
 
 ### Major data structures
The key data structure is the *index*, mapping from *word* to
 *(docID, #occurrences)* pairs. also custom data types max 
 holding a max integer and a doc id. this data structuire is
  used to find the current highest score result in a the
   result counter so that the output is in order of
    relevance. also custom data type twoccts this data type
     holds two counters and is passed in along counters 
     iterations to run get union and intersection functions
     

### Testing plan
test the programs ability to:
reject invalid args
accept valid args
block inccorrect use of args
not crash when taking in a query that produces no results
not crash when user provides an unseen word in the query (not present in the index)
produces accurate results for querys that include the same token in multiple previous queries

