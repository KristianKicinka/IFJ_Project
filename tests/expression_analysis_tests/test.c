#include "../../token_list.h"
#include "../../lexical_analysis.h"
#include "../../recursive_syntactic.h"
#include "../../error.h"
#include "../../expression_analysis.h"
#include <stdio.h>
#include <stdlib.h>

syntactic_data_t data;

void test()
{
    custom_string_init(&data.my_string);
    generate_token(&data.token, &data.my_string);
    precedence_analysis(data.token, &data.my_string);
}

int main()
{

    test();

    custom_string_free_memory(&data.my_string);
    return 0;
}