CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= ../../LL_table.c ../../stack.c ../../scanner.c ../../custom_string.c ../../error.c syntactic_analyze_test.c

.PHONY: test-synt clean


# List of tests

test-synt: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

#test-stack: $(FILES)
#	$(CC) $(CFLAGS) -o $@ $(FILES)
# Calling tests 

#test_string: test-string
#	@./test-string
#	@rm -f test-string

#test_stack: test-stack
#	@./test-stack
#	@rm -f test-stack	

syntactic_analyze_test: test-synt
	@./test-synt
	@rm -f test-synt


clean:
	@rm -f test-synt

