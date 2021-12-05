CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=recursive_test.c ../../lexical_analysis.c ../../custom_string.c ../../error.c ../../recursive_syntactic.c ../../generator.c

.PHONY: test-rec clean


# List of tests

test-rec: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


recursive_syntactic: test-rec
	@./test-rec
	@rm -f test-rec


clean:
	@rm -f test-rec

