cc = gcc
cflages = -Wall -Wextra -pedantic -lm -g -I$(IDIR)

debug = -g -I$(IDIR)

IDIR = ./inc/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all:engine run clean 

engine:inc/engine.h src/engine.c
	$(cc) $(SOURCES) $(cflages) -o $@

debug:
	$(cc) $(SOURCES) $(debug) -o $@


run:
	./engine

clean:
	rm engine
