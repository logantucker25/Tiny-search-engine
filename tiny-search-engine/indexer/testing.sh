# testing.sh - test the usages of indexer.c and index.c

# Logan Tucker, October 2022
# CS 50, Fall 2022

#### test running with invalid args

# no args
./indexer

# invalid index File 
./indexer /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-5 cake

# invalid page directory
./indexer ../invalidPageDir ./indexFile

#### test running with valid args
./indexer /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-5 ../indexFile

### test tindex.c useing indextest.c
./indextest ../indexFile ../newIndexFile

# run compare func to show that the created index matched the given input file (prints any differences)
/thayerfs/courses/22fall/cosc050/workspace/tse/indexcmp ../indexFile ../newIndexFile

#### test running with valid args and valgrind to show no leaks
valgrind ./indexer /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-5 ../indexFile


