/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file error.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie chybových stavov (implementácia)
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "error.h"

int process_error(Error_type err_type){

    if(err_type == LEXICAL_ANALYSIS_FAIL){
        return 1;
    }else if (err_type == SYNTAX_ANALYSIS_FAIL){
        return 2;
    }else if (err_type == SEMANTIC_ANALYSIS_UNDEF_VAR){
        return 3;
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN){
        return 4;
    }else if (err_type == SEMANTIC_ANALYSIS_BAD_COUNT_PARAMETERS){
        return 5;
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC){
        return 6;
    }else if (err_type == SEMANTIC_ANALYSIS_FAIL_OTHERS){
        return 7;
    }else if (err_type == RUNTIME_ERROR_WITH_NIL){
        return 8;
    }else if (err_type == RUNTIME_ERROR_DIVIDING_BY_ZERO){
        return 9;
    }else if (err_type == INTERNAL_FAILATURE){
        return 99;
    }

    return 0;
    
}