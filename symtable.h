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

//#include "scanner.h"
#include "function_data_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 30000

typedef enum {
    IS_DECLARED,
    IS_NOT_DEFINED,
    IS_DEFINED,
    IS_UNSET        // default
}Additional_info;

typedef enum {
    TYPE_VARIABLE,
    TYPE_FUNCTION
}Symbol_type;


typedef struct symbol_table_data {

    char *identificator;
    Symbol_type symbol_type;
    Token_type symbol_variable_type;
    Additional_info symbol_info;
    Data_list *list_of_parameters;
    Data_list *list_of_return_types;

}table_data;


typedef struct symbol_table_item {
    char *key;
    table_data data;
    struct symbol_table_item *next;

}table_item_t;

typedef table_item_t *symbol_table_t[SYMBOL_TABLE_SIZE];


int get_hash(char *key);
void table_init(symbol_table_t *table);

table_item_t *insert_symbol_variable(symbol_table_t *table, char *key);
table_item_t *insert_symbol_function(symbol_table_t *table, char *key);

void insert_function_parameter(symbol_table_t *table, table_item_t *item, Token_type parameter);
void insert_function_return_type(symbol_table_t *table, table_item_t *item, Token_type return_type);

table_item_t *search_item(symbol_table_t *table, char *key);

void delete_symbol(symbol_table_t *table, char *key);
void table_dispose(symbol_table_t *table);

// Getters
char *get_identificator(symbol_table_t *table, char *key);
Symbol_type *get_symbol_type(symbol_table_t *table, char *key);
Token_type *get_symbol_variable_type(symbol_table_t *table, char *key);
Additional_info *get_additional_info(symbol_table_t *table, char *key);
Data_list *get_parameters(symbol_table_t *table, char *key);
Data_list *get_return_types(symbol_table_t *table, char *key);

// Setters
void set_symbol_variable_type(symbol_table_t *table, table_item_t *item, Token_type type);
void set_additional_info(symbol_table_t *table, table_item_t *item, Additional_info info);


#endif // !SYMBOL_TABLE_H