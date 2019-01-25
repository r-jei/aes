# Makefile for AES implementation

CC = cc
CFLAGS = -Wall -g

all: main tests

main: main.o aes.o
	$(CC) $(CFLAGS) -o main main.o aes.o

tests: tests.o aes.o
	$(CC) $(CFLAGS) -o tests aes.c tests.o

main.o:
aes.o: aes.h
tests.o:

#clean main directory
clean:
	rm *~ *.o
