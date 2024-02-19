CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CC = gcc

PROGRAMS = main

.PHONY:	all clean

all: $(PROGRAMS)

main: biblioLC.o entreeSortieLC.o biblioH.o main.o
	$(CC) -o $@ $(CFLAGS) $^
	
biblioLC.o: biblioLC.c
	gcc $(CFLAGS) -c biblioLC.c

entreeSortieLC.o: entreeSortieLC.c
	gcc $(CFLAGS) -c entreeSortieLC.c

biblioH.o: biblioH.c
	$(CC) $(CFLAGS) -c biblioH.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o *~ $(PROGRAMS)

