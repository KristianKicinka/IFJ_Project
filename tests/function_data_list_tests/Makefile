CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c ../../scanner.c ../../function_data_list.c

.PHONY: test-data-list clean


# List of tests

test-data-list: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_data_list: test-data-list
	@./test-data-list
	@rm -f test-data-list

clean:
	@rm -f test-data-list
