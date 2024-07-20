BINARY=compiler

CC=gcc
CFLAGS=-O3 -Iinclude
LDFLAGS=-Llib -ltcc

CFILES=$(shell find -L src -type f -name '*.c')
OBJ=$(CFILES:.c=.o)

$(BINARY): $(OBJ) Makefile
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BINARY)
	./$(BINARY) example.lisp example
	./example

clean:
	rm -rf $(OBJ) $(BINARY) example