CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../generator.c

.PHONY: test-generator clean


# List of tests

test-generator: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_lex_analysis: test-generator
	@./test-generator
	@rm -f test-generator

clean:
	@rm -f test-generator