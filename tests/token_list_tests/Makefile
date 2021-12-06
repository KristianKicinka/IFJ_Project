CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../lexical_analysis.c ../../token_list.c ../../error.c ../../custom_string.c

.PHONY: test-token-list clean


# List of tests

test-token-list: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_params_list: test-params-list
	@./test-token-list
	@rm -f test-token-list

clean:
	@rm -f test-token-list