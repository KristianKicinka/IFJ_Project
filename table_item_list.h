/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file table_item_list.h 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovanie itemov z tabulky symbolov.
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


void table_item_list_init(Table_list *list);

void table_item_list_insert(Table_list *list, table_item_t *item);

void table_item_list_free_memory(Table_list *list);

#endif // TABLE_ITEM_LIST_H