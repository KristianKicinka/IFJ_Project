
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "custom_string.h"

#define CUSTOM_STRING_DEF_LEN 8

/**
 * @brief Funkcia inicializuje custom string
 * 
 * @param str 
 * @return true ak sa operácia podarila
 * @return false 
 */

bool custom_string_init(Custom_string *str){
    
    char *new_string = (char *) malloc(sizeof(char)*(CUSTOM_STRING_DEF_LEN));
    if(new_string == NULL){
        free(new_string);
        return false;
    }
        
    str->string_value = new_string;
    str->length = 0;
    str->string_value[str->length] = '\0';
    str->size_of_allocated_memory = CUSTOM_STRING_DEF_LEN;

    return true;
}

/**
 * @brief 
 * 
 * @param str 
 * @param character 
 * @return true 
 * @return false 
 */

bool custom_string_add_character(Custom_string *str, char character){

    if(str->size_of_allocated_memory <= str->length + 1){
        char *str_tmp;
        str_tmp = (char *) realloc(str->string_value,(str->size_of_allocated_memory + CUSTOM_STRING_DEF_LEN) * sizeof(char));

        if(str_tmp == NULL){
            free(str->string_value);
            return false;
        }

        str->size_of_allocated_memory = str->size_of_allocated_memory + CUSTOM_STRING_DEF_LEN;
    }

    str->string_value[str->length] = character;
    str->string_value[str->length + 1 ] = '\0';
    str->length++;

    return true;
}

/**
 * @brief 
 * 
 * @param str 
 * @param str_to_add 
 * @return true 
 * @return false 
 */

bool custom_string_add_another_string(Custom_string *str, char *str_to_add){

    int to_add_length = strlen(str_to_add);
    int length_after_add_string = str->length + to_add_length;
    int memory_after_add_string = length_after_add_string + 1;
    
    if(str->size_of_allocated_memory <= memory_after_add_string ){

        char *str_tmp;
        str_tmp = (char *) realloc(str->string_value,(str->size_of_allocated_memory + memory_after_add_string ) * sizeof(char));

        if(str_tmp == NULL){
            free(str->string_value);
            return false;
        }
        str->size_of_allocated_memory = memory_after_add_string;
    }

    strcat(str->string_value,str_to_add);
    str->length = length_after_add_string;
    str->string_value[str->length + 1] = '\0';

    return true;
}

/**
 * @brief 
 * 
 * @param source 
 * @param destination 
 * @return true 
 * @return false 
 */

bool custom_string_copy_string(Custom_string *source, Custom_string *destination){

    int new_dest_length = source->length;
    int new_dest_memory = new_dest_length + 1;
    
    if(destination->size_of_allocated_memory <= new_dest_memory ){

        char *str_tmp;
        str_tmp = (char *) realloc(destination->string_value,(destination->size_of_allocated_memory + new_dest_memory ) * sizeof(char));

        if(str_tmp == NULL){
            free(destination->string_value);
            return false;
        }
        destination->size_of_allocated_memory = new_dest_memory;
    }

    strcpy(destination->string_value,source->string_value);
    destination->length = new_dest_length;

    return true;
}

/**
 * @brief 
 * 
 * @param str 
 * @param str_to_add 
 * @return int [0] - ak sú stringy zhodné, [-1] - ak je prvý menší ako druhý, [1] - ak je prvý väčší ako druhý  
 */

int custom_string_compare_with_basic_string(Custom_string *str, char *str_to_compare){

   int ret_value =  strcmp(str->string_value,str_to_compare);

   if(ret_value == 0){
       return 0;
   }else if (ret_value < 0){
       return -1;
   }else{
       return 1;
   }

}

/**
 * @brief 
 * 
 * @param str 
 */

void custom_string_free_memory(Custom_string *str){
    free(str->string_value);
}

