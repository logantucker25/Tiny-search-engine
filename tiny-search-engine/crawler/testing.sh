#!/bin/bash
# Logan Tucker, October 2022
# cs50
# testing file for lab 4 - crawler.c

# First, a sequence of invocations with erroneous arguments

# erroneous seed url
./crawler ttp://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test1 10 

# erroneous depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test1 11 

# run with valgrind over a moderate-sized test case (such as toscrape at depth 1)
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test15 4 

# # runs over all three CS50 websites (letters at depths 0,1,2,10, toscrape at depths 0,1,2,3, wikipedia at depths 0,1,2).
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test1 0 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test2 1 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test3 2
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test1 7
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test4 10 

# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../test5 0 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/index.html ../test6 1 

# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../test7 0 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/index.html ../test8 1 

# # Repeat with a different seed page in that same site. If the site is indeed a graph, with cycles, there should be several interesting starting points.
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test9 0 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test10 1 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test11 2 
# ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/index.html ../test12 10 

# ./crawler https://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/category/books/nonfiction_13/index.html ../test2 0 
# ./crawler https://cs50tse.cs.dartmouth.edu/tse/toscrape/catalogue/category/books/nonfiction_13/index.html ../test2 1 

# ./crawler https://cs50tse.cs.dartmouth.edu/tse/wikipedia/Unix.html ../test13 0 
# ./crawler https://cs50tse.cs.dartmouth.edu/tse/wikipedia/Unix.html ../test14 1 

exit 0





