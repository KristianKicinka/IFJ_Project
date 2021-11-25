CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= custom_string.c error.c expression_analysis.c funct_params_list.c generator.c LL_table.c scanner.c stack.c symtable.c syntactic_analyze.c

.PHONY: build clean

all:build

build: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	@rm -f build

