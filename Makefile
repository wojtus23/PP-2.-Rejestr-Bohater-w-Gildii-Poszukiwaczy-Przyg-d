CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: gildia

gildia: main.o lista.o bohater.o
	$(CC) $(CFLAGS) -o gildia main.o lista.o bohater.o

main.o: main.c lista.h bohater.h
	$(CC) $(CFLAGS) -c main.c

lista.o: lista.c lista.h bohater.h
	$(CC) $(CFLAGS) -c lista.c

bohater.o: bohater.c bohater.h
	$(CC) $(CFLAGS) -c bohater.c

clean:
	rm -f *.o gildia