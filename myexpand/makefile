CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -D_XOPEN_SOURCE=500 -D_BSD_SOURCE -g -c

CFILES = myexpand.c
PGMNAME = myexpand

all: $(PGMNAME)

$(PGMNAME): myexpand.c
	$(CC) $(CFLAGS) -o myexpand myexpand.c

clean:
	rm -vf $(PGMNAME) $(PGMNAME).exe *~
