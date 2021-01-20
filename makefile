CC=gcc
CFLAGS=-g -lpthread -Wall -pedantic -std=gnu99 -lm 
HEADERS = grid.h

default: main.o

main.o: main.c $(HEADERS) 
		$(CC) $(CFLAGS) grid.c main.c $(FLAGS) -o main

main: main.o
		gcc main.o -o main -lm 

clean:
		-rm -f main.o
		-rm -f main
