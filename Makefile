BINARY=compiler

CC=gcc
CFLAGS=-O3 -Iinclude -Itcc
LDFLAGS=-Ltcc -ltcc

CFILES=$(shell find -L src -type f -name '*.c')
OBJ=$(CFILES:.c=.o)

$(BINARY): $(OBJ) Makefile tcc/libtcc1.a
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BINARY)
	./$(BINARY) example.lisp example
	./example

tcc/libtcc1.a:
	cd tcc && ./configure
	make -C tcc

clean:
	rm -rf $(OBJ) $(BINARY) example