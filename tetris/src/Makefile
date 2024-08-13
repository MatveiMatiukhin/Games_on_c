BUILDDIR=../build/
CC=gcc
CFLAGS= -std=c11 -lrt

all: clean_all tetris clean

tetris: tetris.o main.o
	$(CC) tetris.o main.o -o tetris $(CFLAGS)
tetris.o:tetris.c
	$(CC) $(CFLAGS) -c tetris.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c


rebuild: clean_all clean

clean:
	rm -f *.o

clean_all:
	rm -f *.o
	rm -f $(BUILDDIR)t*