CC = cc
CFLAGS = -Wall -g

all: tests

tests: tests.o aes.o
	$(CC) $(CFLAGS) -o tests aes.c tests.o

aes.o: aes.h
tests.o:

#clean main directory
clean:
	rm *~ *.o tests
