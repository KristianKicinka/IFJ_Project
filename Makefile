CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= ifjcode21_compiler.c custom_string.c error.c function_data_list.c lexical_analysis.c  symtable.c recursive_syntactic.c generator.c expression_stack.c token_list.c expression_analysis.c

.PHONY: build clean

all:build

build: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	@rm -f build

