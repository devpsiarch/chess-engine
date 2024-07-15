cc = gcc
cflages = -lncurses -Wall -Wextra -pedantic -lm -I$(IDIR)

IDIR = ./inc/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all:board run 

board:inc/board.h src/board.c
	$(cc) $(SOURCES) $(cflages) -o $@

run:
	./board

clean:
	rm board
