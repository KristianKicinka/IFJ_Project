CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c ../../lexical_analysis.c

.PHONY: test-lex-analysis clean


# List of tests

test-lex-analysis: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_lex_analysis: test-lex-analysis
	@./test-lex-analysis
	@rm -f test-lex-analysis

clean:
	@rm -f test-lex-analysis
