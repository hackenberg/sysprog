CC = gcc
DEFS = -DENDEBUG -D_XOPEN_SOURCE=500 -D_BSD_SOURCE
CFLAGS = -std=c99 -pedantic -Wall -g $(DEFS)

all: mastermind

mastermind: server client

server: server.o
	$(CC) $(CFLAGS) -o $@ $^

client: client.o
	$(CC) $(CFLAGS) -o $@ $^

server.o: server.c
	$(CC) $(CFLAGS) -c -o $@ $<

client.o: client.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -vf *.o server client *~
.PHONY: clean
