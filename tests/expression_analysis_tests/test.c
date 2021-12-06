#include "../../token_list.h"
#include "../../lexical_analysis.h"
#include "../../recursive_syntactic.h"
#include "../../error.h"
#include "../../expression_analysis.h"
#include <stdio.h>
#include <stdlib.h>

void test()
{
}

int main()
{
    int err = 0;
    int i = 0;

    while (!feof(stdin) && err == 0)
    {
        i++;
        printf("while cislo %d \n", i);

        test();
    }
    return 0;
}