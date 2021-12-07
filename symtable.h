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

/* typedef enum {
    IS_DECLARED,
    IS_NOT_DEFINED,
    IS_DEFINED,
    IS_UNSET        // default
}Additional_info; */

typedef enum {
    TYPE_VARIABLE,
    TYPE_FUNCTION
}Symbol_type;


typedef struct symbol_table_data {

    char *identificator;
    Symbol_type symbol_type;
    Token_type symbol_variable_type;
    //Additional_info symbol_info;
    bool is_defined;
    bool is_declared;
    Data_list *list_of_parameters;
    Data_list *list_of_return_types;

}table_data;


typedef struct symbol_table_item {
    char *key;
    table_data data;
    struct symbol_table_item *next;

}table_item_t;

typedef table_item_t *symbol_table_t[SYMBOL_TABLE_SIZE];


/**
 * @brief Funkcia slúži na vytvorenie hashu
 * 
 * @param key Reťazec s hashovacím kľúčom
 * @return int Hash v tabuľke symbolov
 */
int get_hash(char *key);


/**
 * @brief Funkcia slúži na inicializáciu tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 */
void table_init(symbol_table_t *table);


/**
 * @brief Funkcia slúži na vyhľadanie položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na nájdenú položku v tabuľke (v prípade neúspechu hodnota NULL)
 */
table_item_t *search_item(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na vloženie novej premennej do tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na aktuálnu položku
 */
table_item_t *insert_symbol_variable(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na vloženie novej funkcie do tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na aktuálnu položku
 */
table_item_t *insert_symbol_function(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na vloženie nového parametra do zoznamu parametrov definovanej funkcie
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param parameter Parameter, ktorý sa vloží do zoznamu
 */
void insert_function_parameter(symbol_table_t *table, table_item_t *item, Token_type parameter);


/**
 * @brief Funkcia slúži na vloženie nového návratového do zoznamu parametrov definovanej funkcie
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param parameter Návratový typ, ktorý sa vloží do zoznamu
 */
void insert_function_return_type(symbol_table_t *table, table_item_t *item, Token_type return_type);


/**
 * @brief Funkcia slúži na vymazanie tabuľky symbolov a uvoľnenie pamäti
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 */
void table_dispose(symbol_table_t *table);


// Getters

/**
 * @brief Funkcia slúži na získanie identifikátora položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return char* Identifikátor položky v tabuľke
 */
char *get_identificator(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na získanie typu položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Symbol_type* Typ položky v tabuľke symbolov
 */
Symbol_type *get_symbol_type(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na získanie typu premennej z tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Token_type* Typ premennej uloženej v tabuľke symbolov
 */
Token_type *get_symbol_variable_type(symbol_table_t *table, char *key);



bool *get_is_defined(symbol_table_t *table, char *key);

bool *get_is_declared(symbol_table_t *table, char *key);

/**
 * @brief Funkcia slúži na získanie parametrov z funkcie uloženej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Data_list* Zoznam parametrov uloženej funkcie
 */
Data_list *get_parameters(symbol_table_t *table, char *key);


/**
 * @brief Funkcia slúži na získanie návratových typov funkcie uloženej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Data_list* Zoznam návratových typov uloženej funkcie
 */
Data_list *get_return_types(symbol_table_t *table, char *key);


// Setters

/**
 * @brief Funkcia slúži na nastavenie typu premennej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param type Typ premennej, ktorý sa nastaví položke v tabuľke symbolov
 */
void set_symbol_variable_type(symbol_table_t *table, table_item_t *item, Token_type type);

void set_is_declared(symbol_table_t *table, table_item_t *item, bool value);

void set_is_defined(symbol_table_t *table, table_item_t *item, bool value);


#endif // !SYMBOL_TABLE_H