CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../custom_string.c ../../error.c  ../../table_item_list.c

.PHONY: test-table-item-list clean



# List of tests

test-table-item-list: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_data_list: test-table-item-list
	@./test-table-item-list
	@rm -f test-table-item-list

clean:
	@rm -f test-table-item-list
