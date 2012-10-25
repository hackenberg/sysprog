CC = gcc
DEFS = -D_XOPEN_SOURCE=500 -D_BSD_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -g $(DEFS)

all: myexpand

myexpand: myexpand.o
	$(CC) $(CFLAGS) -o $@ $^

myexpand.o: myexpand.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -vf myexpand.o myexpand *~
.PHONY: clean
