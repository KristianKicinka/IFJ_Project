CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm
FILES=custom_string_test.c ../custom_string.c 

.PHONY: test-string clean


# List of tests

test-string: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

# Calling tests 

test_string: test-string
	@./test-string
	@rm -f test-string

clean:
	@rm -f test-string

