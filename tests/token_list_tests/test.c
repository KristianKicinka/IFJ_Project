#include "../../token_list.h"
#include "../../lexical_analysis.h"
#include "../../recursive_syntactic.h"
#include "../../token_list.h"
#include "../../error.h"
#include <stdio.h>
#include <stdlib.h>

void anal(token_list *token_list)
{
    syntactic_data_t data;

    custom_string_init(&data.my_string);

    generate_token(&data.token, &data.my_string);
    // printf("vygenerovany token %d \n", data.token.type_of_token);

    token_list_insertlast(token_list, data.token);
    // printf("%u\n", token_list->lastElement->token.type_of_token);
}

int main()
{
    token_list *token_list;

    token_list_init(token_list);

    int err = 0;
    int i = 0;

    while (!feof(stdin) && err == 0)
    {
        i++;
        // printf("while cislo %d \n", i);

        anal(token_list);
    }

    printf("\n\n--------- Printing tokens ---------\n\n");

    token_list_activefirst(token_list);

    i=0;
    while (token_list->activeElement != NULL)
    {
        i++;
        printf("Token number %d: %u\n", i, token_list->activeElement->token.type_of_token);
        token_list_next(token_list);
    }

    printf("\n--------- Printing tokens ---------\n\n");

    token_list_activefirst(token_list);

    while (token_list->activeElement != NULL)
    {
        printf("%u ", token_list->activeElement->token.type_of_token);
        token_list_next(token_list);
    }

    printf("\n\n---- This should print nothing ----\n\n");

    token_list_dispose(token_list);

    token_list_activefirst(token_list);

    while (token_list->activeElement != NULL)
    {
        printf("%u ", token_list->activeElement->token.type_of_token);
        token_list_next(token_list);
    }
    printf("\n");

    return 0;
}
