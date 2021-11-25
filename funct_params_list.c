#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scanner.h"
#include "funct_params_list.h"

void init_function_parameters (Parameters_list *list){
    list->parameters_count = 0;
    list->allocated_memory = 0;
    list->items = NULL;
}

bool function_parameters_insert(Parameters_list *list, Token_type token_type){
    Token_type *new_item;
    new_item = (Token_type *) realloc(list->items,(list->allocated_memory + 1) * sizeof(Token_type));

        if(new_item == NULL){
            return false;
        }

    list->items = new_item;
    list->items[list->parameters_count] = token_type;
    list->parameters_count++;
    list->allocated_memory++;

    return true;

}

void function_parameters_free_memory(Parameters_list *list){
    free(list->items);
}
