/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file funct_params_list.h 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie parametrov funkcií (rozhranie)
 * 
 */

#ifndef FUNCT_PARAMS_LIST_H
#define FUNCT_PARAMS_LIST_H

#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct function_parameters_t {
    Token_type *items;
    int parameters_count;
    int allocated_memory;
}Parameters_list;


void init_function_parameters(Parameters_list *list);

bool function_parameters_insert(Parameters_list *list, Token_type token_type);

void function_parameters_free_memory(Parameters_list *list);

#endif // FUNCT_PARAMS_LIST_H