# Lab 4

## student name
Logan Tucker
## grader name
Jack McMahon

Recall the [Assignment](https://www.cs.dartmouth.edu/~tjp/cs50/labs/lab4/).

**Total: 59/100 points**

## (10) Overall

6/10 points:

* -1 Git commit history should have more pushes and meaningful groupings of commits.
* -1 No .gitignore file in crawler
* -2 extra data folders in repo and object files in crawler

* For future labs check out the assignment details for what to submit before you push. The rubric is pretty harsh on these details for tse but it's easy to avoid getting docked for those things if you really make sure you've got exactly what it's asking for.

## (10) Makefiles

8/10 points:

* -1 no test rule in Makefile
* -1 compilation error in top level Makefile. Indexer and Querier should be commented out for this submit.

## (3) Documentation

2/3 points:

*  -1 Top level README.md should be edited to have your name and username as well as any assumptions on crawler.

## (12) Testing

10/12 points:

* -2 points for lack of testing run/published to testing.out and lack of descriptions for testing. Good job/style on the tests for valid inputs but most are commented out so nothing for them in testing.out. Also most other tests for valid inputs don't have a description or are commented out. 

## (20) Coding Style
20/20 points:

* 

## (35) Functionality

13/35 points:

-22 points. Fails tests on crawling toscrape, wikipedia, and letters. Crawler has segmentation faults due to invalid reads/writes in memory. Outputs appear in valgrind because of how valgrind handles segmentation faults, but you should make sure your code runs outside of valgrind as well.
* 

## (10) Memory leaks, according to valgrind

0/10 points:

* -4 memory errors
* -6 lost memory blocks

## Late penalites


