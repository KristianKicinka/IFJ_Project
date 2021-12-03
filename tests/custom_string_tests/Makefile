CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c

.PHONY: test-string clean


# List of tests

test-string: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_string: test-string
	@./test-string
	@rm -f test-string

clean:
	@rm -f test-string

