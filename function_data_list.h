/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file funct_params_list.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie parametrov funkcií (implementácia)
 * 
 */

#ifndef FUNCT_PARAMS_LIST_H
#define FUNCT_PARAMS_LIST_H

#include "lexical_analysis.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct function_data_list_t {
    Token_type *items;
    int items_count;
    int allocated_memory;
}Data_list;


void function_data_list_init(Data_list *list);

void function_data_list_insert(Data_list *list, Token_type token_type);

void function_data_list_free_memory(Data_list *list);

#endif // FUNCT_PARAMS_LIST_H