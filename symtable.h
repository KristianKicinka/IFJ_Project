#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "scanner.h"

#define SYMBOL_TABLE_SIZE 30000 

typedef enum {
    TYPE_STRING,
    TYPE_NIL,
    TYPE_NUMBER,
    TYPE_INTEGER
}Symbol_type;

typedef enum {
    IS_GLOBAL,
    IS_LOCAL
}Global_var;

typedef enum {
    IS_DEFINED,
    IS_NOT_DEFINED
}Defined_function;

typedef struct symbol_table_symbol {

    char *identificator;
    Symbol_type type_of_symbol;
    Global_var global_var;
    Defined_function defined_function;
    // add parameters (Parameters *parameters)

}table_symbol_t;


typedef struct symbol_table_item {
    char *key;
    table_symbol_t data;
    struct table_item_t *next;

}table_item_t;

typedef table_item_t *symbol_table_t[SYMBOL_TABLE_SIZE];


int get_hash(char *key);
void table_init(symbol_table_t *table);

void insert_symbol(symbol_table_t *table, char *key ,Token *token);
void delete_symbol(symbol_table_t *table, char *key);

table_item_t *search(table_symbol_t *table, char *key);
table_item_t *get_value(table_symbol_t *table, char *key);

void insert_function_parameter(table_symbol_t *table, char *key, Token *token);
void table_dispose(symbol_table_t *table);



#endif // !SYMBOL_TABLE_H