CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES= ../../expression_stack.c exp_stack_test.c ../../lexical_analysis.c  ../../expression_analysis.c ../../error.c ../../custom_string.c

.PHONY: exp-test-stack clean


# List of tests

exp-test-stack: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

# Calling tests 

exp-test_stack: exp-test-stack
	@./exp-test-stack
	@rm -f exp-test-stack	

clean:
	@rm -f exp-test-stack
