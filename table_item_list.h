/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file table_item_list.h 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie položiek v tabuľke symbolov (rozhranie)
 * 
 */

#ifndef TABLE_ITEM_LIST_H
#define TABLE_ITEM_LIST_H

#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct table_item_list_t {
    table_item_t **items;
    int items_count;
    int allocated_memory;
}Table_list;




/**
 * @brief Funkcia slúži na inicializáciu štruktúty Table list
 * 
 * @param list Ukazateľ na štruktúru Table list
 */
void table_item_list_init(Table_list *list);


/**
 * @brief Funkcia slúži na vloženie nového prvku do listu
 * 
 * @param list Ukazateľ na štruktúru Table listu
 * @param item Položka, ktorá sa vkladá do listu
 */
void table_item_list_insert(Table_list *list, table_item_t *item);


/**
 * @brief Funkcia slúži na uvoľnenie pamäti
 * 
 * @param list Ukazateľ na štruktúru Table listu
 */
void table_item_list_free_memory(Table_list *list);

#endif // TABLE_ITEM_LIST_H