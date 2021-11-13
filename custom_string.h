
#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <stdbool.h>


typedef struct custom_string_t
{
 char *string_value;
 int length;
 int size_of_allocated_memory;

} Custom_string;


/**
 * @brief Funkcia inicializuje custom string
 * 
 * @param str 
 * @return true ak sa operácia podarila
 * @return false 
 */

bool custom_string_init(Custom_string *str);

/**
 * @brief 
 * 
 * @param str 
 * @param character 
 * @return true 
 * @return false 
 */

bool custom_string_add_character(Custom_string *str, char character);

/**
 * @brief 
 * 
 * @param str 
 * @param str_to_add 
 * @return true 
 * @return false 
 */

bool custom_string_add_another_string(Custom_string *str, char *str_to_add);

/**
 * @brief 
 * 
 * @param source 
 * @param destination 
 * @return true 
 * @return false 
 */

bool custom_string_copy_string(Custom_string *source, Custom_string *destination);

/**
 * @brief 
 * 
 * @param str 
 * @param str_to_add 
 * @return int 
 */

int custom_string_compare_with_basic_string(Custom_string *str, char *str_to_add);

/**
 * @brief 
 * 
 * @param str 
 */


void custom_string_free_memory(Custom_string *str);

#endif // !CUSTOM_STRING_H
