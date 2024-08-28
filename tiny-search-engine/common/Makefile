# Makefile for 'common' module
#
# Logan Tucker, October 2022
# CS 50, Fall 2022

OBJS = pagedir.o index.o word.o token.o
LIB = common.a
LIBS =
LLIBS = 
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50
CC = gcc
MAKE = make

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all test valgrind clean

all: $(LIB)

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

pagedir.o: pagedir.h ../libcs50/webpage.h ../libcs50/file.h 

index.o: index.h ../libcs50/webpage.h ../libcs50/file.h ../libcs50/hashtable.h ../libcs50/counters.h 

word.o: word.h ../libcs50/webpage.h 

token.o: word.h

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f common.a
	rm -f core