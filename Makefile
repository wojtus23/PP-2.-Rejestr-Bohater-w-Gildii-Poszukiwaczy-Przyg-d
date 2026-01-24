CC=gcc
CFLAGS=-Wall -Wextra -std=c11

all: gildia

gildia: main.o lista.o bohater.o pomocnicze.o
	$(CC) $(CFLAGS) -o gildia main.o lista.o bohater.o pomocnicze.o

main.o: main.c lista.h bohater.h pomocnicze.h
	$(CC) $(CFLAGS) -c main.c

lista.o: lista.c lista.h bohater.h 
	$(CC) $(CFLAGS) -c lista.c

bohater.o: bohater.c bohater.h pomocnicze.h
	$(CC) $(CFLAGS) -c bohater.c

pomocnicze.o: pomocnicze.c pomocnicze.h 
	$(CC) $(CFLAGS) -c pomocnicze.c

clean:
	del *.o gildia.exe