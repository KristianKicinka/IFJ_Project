/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file custom_string.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Vlastná verzia stringu (implementácia)
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "custom_string.h"


/**
 * @brief Funkcia slúži na  inicializáciu štruktúry custom string
 * 
 * @param str Ukazateľ na štruktúru custom string
 */

void custom_string_init(Custom_string *str){

    int length = 0;
    int memory = 1; 
    
    char *new_string = (char *) malloc(sizeof(char)*(memory));
    if(new_string == NULL){
        process_error(INTERNAL_FAILATURE);
    }
        
    str->string_value = new_string;
    str->length = length;
    str->string_value[str->length] = '\0';
    str->size_of_allocated_memory = memory;
}

/**
 * @brief Funkcia slúži na pridanie znaku do custom stringu
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param character Znak, ktorý sa pridá do stringu 
 */

void custom_string_add_character(Custom_string *str, char character){


    if(str->size_of_allocated_memory <= str->length + 1){

        char *str_tmp;
        str_tmp = (char *) realloc(str->string_value,(str->size_of_allocated_memory + 2) * sizeof(char));

        if(str_tmp == NULL){
            process_error(INTERNAL_FAILATURE);
        }

        str->string_value = str_tmp;
        str->size_of_allocated_memory = str->size_of_allocated_memory + 2 ;
    }

    str->string_value[str->length] = character;
    str->length++;
    str->string_value[str->length] = '\0';
    
}

/**
 * @brief Funkcia slúži na pridanie reťazca znakov do custom stringu
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param str_to_add Reťazec, ktorý pridávame do custom stringu
 */

void custom_string_add_another_string(Custom_string *str, char *str_to_add){

    int to_add_length = strlen(str_to_add);
    int length_after_add_string = str->length + to_add_length;
    int memory_after_add_string = length_after_add_string + 2;
    
    if(str->size_of_allocated_memory <= memory_after_add_string ){

        char *str_tmp;
        str_tmp = (char *) realloc(str->string_value,( memory_after_add_string ) * sizeof(char));
    
        if(str_tmp == NULL){
            process_error(INTERNAL_FAILATURE);
        }
        str->string_value = str_tmp;
        str->size_of_allocated_memory = memory_after_add_string;
    }

    strcat(str->string_value,str_to_add);
    str->length = length_after_add_string;
    str->string_value[str->length + 1] = '\0';

}

/**
 * @brief Funkcia slúži na kopírovanie custom stringu do iného custom stringu
 * 
 * @param source Ukazateľ na zdrojovú štruktúru custom string
 * @param destination Ukazateľ na cieľovú štruktúru custom string
 */

void custom_string_copy_string(Custom_string *source, Custom_string *destination){

    int new_dest_length = source->length;
    int new_dest_memory = new_dest_length + 1;
    
    if(destination->size_of_allocated_memory <= new_dest_memory ){

        char *str_tmp;
        str_tmp = (char *) realloc(destination->string_value,( new_dest_memory ) * sizeof(char));

        if(str_tmp == NULL){
            process_error(INTERNAL_FAILATURE);
        }
        destination->string_value = str_tmp;
        destination->size_of_allocated_memory = new_dest_memory;
    }

    strcpy(destination->string_value,source->string_value);
    destination->length = new_dest_length;

}

/**
 * @brief Funkcia slúži na porovnanie custom stringu s reťazcom
 * 
 * @param str Ukazateľ na štruktúru custom string
 * @param str_to_add Reťazec s ktorým sa porovnáva
 * @return int Vráti 0 ak sú zhodné
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
 * @brief Funkcia slúži na vyčistenie pamäti
 * 
 * @param str Ukazateľ na štruktúru custom string
 */

void custom_string_free_memory(Custom_string *str){
    free(str->string_value);
}


