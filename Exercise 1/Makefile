CC=gcc
CFLAGS=-I. -lm -w
DEPS = checkNumbers.h tickets.h checkSudoku.h
OBJ = checkNumbers.c tickets.c checkSudoku.c main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MyApp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
