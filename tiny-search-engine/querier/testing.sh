#!/bin/sh
# logan Tucker - testing querier.c
# cs50, October 2022

# invalid page directory
./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-f /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# invalid index file 
./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-f

# too many args
./querier cake pie lettuce

# valid args

# single word
echo for | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# and as a space
echo for tse | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# or use
echo for or search | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# and use
echo for and search | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# query for word not in index
echo logan | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# odd spacing 
echo logan     and       search or      for or breadth | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# invalid (numbers)
echo 123 | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# invalid character
echo hello-mate | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# two words not existing in the index
echo foo bar | ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3

# valgrind check to show no mem leaks
echo for or search or tse or eniac | valgrind --leak-check=full --show-leak-kinds=all -s ./querier /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-depth-3 /thayerfs/courses/22fall/cosc050/workspace/tse/tse-output/letters-index-3