/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file table_item_list.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie položiek v tabuľke symbolov (implementácia)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table_item_list.h"



/**
 * @brief Funkcia slúži na inicializáciu štruktúty Table list
 * 
 * @param list Ukazateľ na štruktúru Table list
 */
void table_item_list_init(Table_list *list){
    list->items_count = 0;
    list->allocated_memory = 1;

    table_item_t **new_item = (table_item_t **) malloc(sizeof(table_item_t*)*(list->allocated_memory));
    if(new_item == NULL){
        process_error(INTERNAL_FAILATURE);
    }

    list->items = new_item;
    list->items[list->items_count] = NULL;

}


/**
 * @brief Funkcia slúži na vloženie nového prvku do listu
 * 
 * @param list Ukazateľ na štruktúru Table listu
 * @param item Položka, ktorá sa vkladá do listu
 */
void table_item_list_insert(Table_list *list, table_item_t *item){
    table_item_t **new_item;
    new_item = (table_item_t **) realloc(list->items,(list->allocated_memory + 1) * sizeof(table_item_t*));

        if(new_item == NULL){
            process_error(INTERNAL_FAILATURE);
        }

    list->items = new_item;
    list->items[list->items_count] = item;
    list->items_count++;
    list->allocated_memory++;

}


/**
 * @brief Funkcia slúži na uvoľnenie pamäti
 * 
 * @param list Ukazateľ na štruktúru Table listu
 */
void table_item_list_free_memory(Table_list *list){
    free(list->items);
}
