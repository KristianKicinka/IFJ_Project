#include "../../token_list.h"
#include "../../lexical_analysis.h"
#include "../../recursive_syntactic.h"
#include "../../error.h"
#include "../../expression_analysis.h"
#include <stdio.h>
#include <stdlib.h>

void test()
{
    syntactic_data_t data;
    custom_string_init(&data.my_string);
    generate_token(&data.token, &data.my_string);
    precedence_analysis(data.token, &data.my_string);
}

int main()
{
    //int err = 0;
    //int i = 0;

    test();

    /*
    while (!feof(stdin) && err == 0)
    {
        //i++;
        //printf("while cislo %d \n", i);

        test();
    }

    */

    return 0;
}