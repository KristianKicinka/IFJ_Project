/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file funct_params_list.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie parametrov funkcií (implementácia)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function_data_list.h"

void function_data_list_init(Data_list *list){
    list->items_count = 0;
    list->allocated_memory = 1;

    Token_type *new_item = (Token_type *) malloc(sizeof(Token_type)*(list->allocated_memory));
    if(new_item == NULL){
        process_error(INTERNAL_FAILATURE);
    }

    list->items = new_item;
    list->items[list->items_count] = -1;

}

void function_data_list_insert(Data_list *list, Token_type parameter){
    Token_type *new_item;
    new_item = (Token_type *) realloc(list->items,(list->allocated_memory + 1) * sizeof(Token_type));

        if(new_item == NULL){
            process_error(INTERNAL_FAILATURE);
        }

    list->items = new_item;
    list->items[list->items_count] = parameter;
    list->items_count++;
    list->allocated_memory++;

}

void function_data_list_free_memory(Data_list *list){
    free(list->items);
}
