CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= custom_string.c error.c expression_analysis.c funct_params_list.c scanner.c  #symtable.c syntactic_analyze.c LL_table.c stack.c generator.c 

.PHONY: build clean

all:build

build: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	@rm -f build

