/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file function_data_list.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie parametrov funkcií a návratových typov (rozhranie)
 * 
 */

#ifndef FUNCTION_DATA_LIST_H
#define FUNCTION_DATA_LIST_H

#include "lexical_analysis.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct function_data_list_t {
    Token_type *items;
    int items_count;
    int allocated_memory;
}Data_list;



/**
 * @brief Funkcia slúži na inicializáciu štruktúry Data list
 * 
 * @param list Ukazateľ na štruktúru Data listu
 */
void function_data_list_init(Data_list *list);


/**
 * @brief Funkcia slúži na uloženie nového parametra alebo návratovej hodnoty do listu
 * 
 * @param list Ukazateľ na štruktúru Data listu
 * @param parameter Hodnota, ktorá sa vkladá do listu
 */

void function_data_list_insert(Data_list *list, Token_type token_type);


/**
 * @brief Funkcia slúži na vyčistenie pamäti
 * 
 * @param list Ukazateľ na štruktúru Data listu
 */

void function_data_list_free_memory(Data_list *list);

#endif // FUNCTION_DATA_LIST_H