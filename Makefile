CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -ljpeg -lm

all: mandel mandelmovie

mandel: mandel.o jpegrw.o
	$(CC) mandel.o jpegrw.o $(LDFLAGS) -o mandel

mandelmovie: mandelmovie.o jpegrw.o
	$(CC) mandelmovie.o jpegrw.o $(LDFLAGS) -o mandelmovie

mandel.o: mandel.c 
	$(CC) $(CFLAGS) -c mandel.c -o mandel.o

mandelmovie.o: mandelmovie.c 
	$(CC) $(CFLAGS) -c mandelmovie.c -o mandelmovie.o

jpegrw.o: jpegrw.c jpegrw.h
	$(CC) $(CFLAGS) -c jpegrw.c -o jpegrw.o

clean:
	rm -f *.o mandel mandelmovie *.d