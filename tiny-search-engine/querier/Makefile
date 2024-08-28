OBJS = querier.o 
LIBS =
LLIBS = ../common/common.a ../libcs50/libcs50-given.a -lm
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all test valgrind clean

all: querier	

querier: querier.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

querier.o: ../libcs50/hashtable.h ../libcs50/webpage.h ../libcs50/counters.h ../common/word.h ../common/index.h ../common/token.h ../common/pagedir.h

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f querier 
	rm -f core