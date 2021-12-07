#include "../../expression_analysis.h"

syntactic_data_t data;

void test()
{
    custom_string_init(&data.my_string);
    generate_token(&data.token, &data.my_string);
    precedence_analysis(&data);
    custom_string_free_memory(&data.my_string);
}

int main()
{
    test();
    
    return 0;
}