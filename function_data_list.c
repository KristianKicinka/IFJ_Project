/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file function_data_list.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie parametrov a návratových typov funkcií (implementácia)
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "function_data_list.h"




/**
 * @brief Funkcia slúži na inicializáciu štruktúry Data list
 * 
 * @param list Ukazateľ na štruktúru Data listu
 */
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


/**
 * @brief Funkcia slúži na uloženie nového parametra alebo návratovej hodnoty do listu
 * 
 * @param list Ukazateľ na štruktúru Data listu
 * @param parameter Hodnota, ktorá sa vkladá do listu
 */
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


/**
 * @brief Funkcia slúži na vyčistenie pamäti
 * 
 * @param list Ukazateľ na štruktúru Data listu
 */
void function_data_list_free_memory(Data_list *list){
    free(list->items);
}
