CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c ../../scanner.c ../../funct_params_list.c

.PHONY: test-params-list clean


# List of tests

test-params-list: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_params_list: test-params-list
	@./test-params-list
	@rm -f test-params-list

clean:
	@rm -f test-params-list
