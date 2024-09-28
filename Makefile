BINARY=compiler

CC=gcc
CFLAGS=$(shell cat compile_flags.txt)
LDFLAGS=-Ltcc -ltcc -Ofast

CFILES=$(shell find -L src -type f -name '*.c')
OBJ=$(CFILES:.c=.o)

$(BINARY): $(OBJ) Makefile tcc/libtcc1.a
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(BINARY)
	./$(BINARY) run example.lisp

run-debug: $(BINARY)
	./$(BINARY) run example.lisp -d yes

run-build: $(BINARY)
	./$(BINARY) build example.lisp -o example
	./example

run-build-debug: $(BINARY)
	./$(BINARY) build example.lisp -o example -d yes
	./example

tcc/libtcc1.a:
	cd tcc && ./configure --cc=$(CC)
	make -C tcc

clean:
	rm -rf $(OBJ) $(BINARY) example
