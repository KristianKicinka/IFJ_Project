/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file symtable.h 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Tybuľka symbolov (rozhranie)
 * 
 */


#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scanner.h"
#include "funct_params_list.h"

#define SYMBOL_TABLE_SIZE 30000 

typedef enum {
    TYPE_STRING,
    TYPE_NIL,
    TYPE_NUMBER,
    TYPE_INTEGER
}Symbol_type;

typedef enum {
    IS_GLOBAL,
    IS_LOCAL,
    IS_DEFINED,
    IS_NOT_DEFINED
}Additional_info;


typedef struct symbol_table_data {

    char *identificator;
    bool is_function;
    Symbol_type type_of_symbol;
    Additional_info symbol_info;
    Parameters_list *list_of_parameters;

}table_data;


typedef struct symbol_table_item {
    char *key;
    table_data data;
    struct table_item_t *next;

}table_item_t;

typedef table_item_t *symbol_table_t[SYMBOL_TABLE_SIZE];


int get_hash(char *key);
void table_init(symbol_table_t *table);

void insert_symbol_variable(symbol_table_t *table, char *key , char *id, Symbol_type type, Additional_info *info);
void delete_symbol(symbol_table_t *table, char *key);

table_item_t *search(table_symbol_t *table, char *key);
table_item_t *get_value(table_symbol_t *table, char *key);

void insert_function_parameter(table_symbol_t *table, char *key, Token *token);
void table_dispose(symbol_table_t *table);



#endif // !SYMBOL_TABLE_H