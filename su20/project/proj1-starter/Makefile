CC = gcc
CFLAGS = -g -Wall -std=c99 -c
LDFLAGS = -g -Wall

.PHONY : all test clean

all : philspel

philspel : philspel.o hashtable.o
	$(CC) $(LDFLAGS) -o philspel philspel.o hashtable.o

philspel.o : philspel.c philspel.h hashtable.h
	$(CC) $(CFLAGS) philspel.c

hashtable.o : hashtable.c hashtable.h
	$(CC) $(CFLAGS) hashtable.c

clean :
	rm -f *.o philspel testOutput

test : clean philspel
	touch testOutput
	cat sampleInput | ./philspel sampleDictionary > testOutput
	@echo The following should be empty if there are no problems
	diff sampleOutput testOutput 2> /dev/null
	@echo Testing complete
