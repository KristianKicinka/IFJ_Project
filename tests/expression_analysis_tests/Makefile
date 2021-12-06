CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm  -ggdb3
FILES=test.c ../../expression_analysis.c ../../lexical_analysis.c  ../../custom_string.c  ../../expression_stack.c  ../../error.c ../../stack.c  ../../token_list.c

.PHONY: test-expression clean


# List of tests

test-expression: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)


test_params_list: test-params-list
	@./test-expression
	@rm -f test-expression

clean:
	@rm -f test-expression