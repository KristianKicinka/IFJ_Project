/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file custom_string.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Vlastná verzia stringu (rozhranie)
 * 
 */

#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <stdbool.h>
#include "error.h"

typedef struct custom_string_t
{
 char *string_value;
 int length;
 int size_of_allocated_memory;

} Custom_string;


/**
 * @brief Funkcia slúži na  inicializáciu štruktúry custom string
 * 
 * @param str Ukazateľ na štruktúru custom string
 */
void custom_string_init(Custom_string *str);


/**
 * @brief Funkcia slúži na pridanie znaku do custom stringu
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param character Znak, ktorý sa pridá do stringu 
 */
void custom_string_add_character(Custom_string *str, char character);

/**
 * @brief Funkcia slúži na pridanie reťazca znakov do custom stringu
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param str_to_add Reťazec, ktorý pridávame do custom stringu
 */
void custom_string_add_another_string(Custom_string *str, char *str_to_add);


/**
 * @brief Funkcia slúži na kopírovanie custom stringu do iného custom stringu
 * 
 * @param source Ukazateľ na zdrojovú štruktúru custom string
 * @param destination Ukazateľ na cieľovú štruktúru custom string
 */
void custom_string_copy_string(Custom_string *source, Custom_string *destination);

/**
 * @brief Funkcia slúži na porovnanie custom stringu s reťazcom
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param str_to_add Reťazec s ktorým sa porovnáva
 * @return int Vráti 0 ak sú zhodné
 */
int custom_string_compare_with_basic_string(Custom_string *str, char *str_to_add);

/**
 * @brief Funkcia slúži na vyčistenie pamäti
 * 
 * @param str Ukazateľ na štruktúru custom string
 */
void custom_string_free_memory(Custom_string *str);

#endif // !CUSTOM_STRING_H

