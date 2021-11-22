#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "error.h"
#include "scanner.h"

FILE *file;
Custom_string *custom_str;


void import_file_to_scan(FILE *file);

int process_identificator(Custom_string *string, Token *token){
    if(custom_string_compare_with_basic_string(string->string_value,"do") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_DO;
    }else if(custom_string_compare_with_basic_string(string->string_value,"else") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_ELSE;
    }else if(custom_string_compare_with_basic_string(string->string_value,"end") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_END;
    }else if(custom_string_compare_with_basic_string(string->string_value,"function") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_FUNCTION;
    }else if(custom_string_compare_with_basic_string(string->string_value,"global") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_GLOBAL;
    }else if(custom_string_compare_with_basic_string(string->string_value,"if") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_IF;
    }else if(custom_string_compare_with_basic_string(string->string_value,"integer") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_INTEGER;
    }else if(custom_string_compare_with_basic_string(string->string_value,"local") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_LOCAL;
    }else if(custom_string_compare_with_basic_string(string->string_value,"nil") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_NIL;
    }else if(custom_string_compare_with_basic_string(string->string_value,"number") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_NUMBER;
    }else if(custom_string_compare_with_basic_string(string->string_value,"require") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_ELSE;
    }else if(custom_string_compare_with_basic_string(string->string_value,"return") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_RETURN;
    }else if(custom_string_compare_with_basic_string(string->string_value,"string") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_STRING;
    }else if(custom_string_compare_with_basic_string(string->string_value,"then") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_THEN;
    }else if(custom_string_compare_with_basic_string(string->string_value,"while") == 0){
        token->type_of_token = TYPE_KEYWORD;
        token->token_info.key_word = KW_WHILE;
    }else{
        token->type_of_token = TYPE_IDENTIFICATOR;
    }

    if (token->type_of_token == TYPE_IDENTIFICATOR){
        bool error = custom_string_copy_string(string,token->token_info.custom_string);
        if(error == false){
            custom_string_free_memory(string);
            return process_error(SCANNER_ANALYSIS_FAIL);
        } 
    }

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);

}

int process_double_value(Custom_string *string, Token *token){
    char *ptr;
    double double_value = (double) strtod(string->string_value, &ptr);

    if(*ptr != NULL){
        custom_string_free_memory(string);
        return process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_DOUBLE_NUMBER;
    token->token_info.double_value = double_value;

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);
}

int process_integer_value(Custom_string *string, Token *token){
    char *ptr;
    int integer_value = (int) strtol(string->string_value, &ptr, 10);

    if(*ptr != NULL){
        custom_string_free_memory(string);
        return process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_INT_NUMBER;
    token->token_info.integer_value = integer_value;

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);

}

//void declarate_custom_string(Custom_string *string);

//int generate_token(Token *token);
