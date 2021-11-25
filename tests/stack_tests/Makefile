CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= ../stack.c stack_test.c #custom_string_test.c ../custom_string.c

.PHONY: test-string test-stack clean


# List of tests

#test-string: $(FILES)
#	$(CC) $(CFLAGS) -o $@ $(FILES)

test-stack: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)
# Calling tests 

#test_string: test-string
#	@./test-string
#	@rm -f test-string

test_stack: test-stack
	@./test-stack
	@rm -f test-stack	

clean:
	@rm -f test-string test-stack

