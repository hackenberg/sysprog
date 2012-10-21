CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -D_XOPEN_SOURCR=500

CFILES = myexpand.c
PGMNAME = myexpand

all: $(PGMNAME)

$(PGMNAME): myexpand.c
	$(CC) $(CFLAGS) -o myexpand myexpand.c

clean:
	rm -vf $(PGMNAME) *~
