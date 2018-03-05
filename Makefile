CC = gcc

CCFLAGS = -Wall -pedantic -g

LD = gcc

LDFLAGS =

all: parseline

parseline: parseline.o stage.o util.o

parseline.o: parseline.c

stage.o: stage.c

util.o: util.c

clean:
	rm *.o
