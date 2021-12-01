CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= ../../stack.c stack_test.c ../../error.c  ../../LL_table.c ../../scanner.c ../../custom_string.c #../syntactic_tests/syntactic_analyze_test.c

.PHONY: test-stack clean


# List of tests

test-stack: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

# Calling tests 

test_stack: test-stack
	@./test-stack
	@rm -f test-stack	

clean:
	@rm -f test-string test-stack

