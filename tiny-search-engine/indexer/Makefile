# Makefile for 'indexer' module
#
# Logan Tucker, October 2022
# CS 50, Fall 2022

OBJS = indexer.o indextest.o # ../common/pagedir.o ../common/word.o ../common/index.o ../libcs50/
LIBS =
LLIBS = ../common/common.a ../libcs50/libcs50-given.a -lm
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all test valgrind clean

all: indexer indextest

indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

indexer.o: ../libcs50/bag.h ../libcs50/hashtable.h ../libcs50/webpage.h ../libcs50/set.h ../common/pagedir.h ../common/word.h ../common/index.h

indextest.o: ../libcs50/bag.h ../libcs50/hashtable.h ../libcs50/webpage.h ../libcs50/set.h ../common/pagedir.h ../common/word.h ../common/index.h 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f indexer 
	rm -f indextest
	rm -f core