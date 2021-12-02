CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c ../../lexical_analysis.c ../../function_data_list.c ../../symtable.c

.PHONY: test-symtable clean


# List of tests

test-symtable: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_symtable: test-symtable
	@./test-symtable
	@rm -f test-symtable

clean:
	@rm -f test-symtable