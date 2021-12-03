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

void process_error(Error_type err_type){

    if(err_type == LEXICAL_ANALYSIS_FAIL){
        fprintf("LEXICAL ANALYSIS FAIL\n",stderr);
        exit(1);
    }else if (err_type == SYNTAX_ANALYSIS_FAIL){
        fprintf("SYNTAX ANALYSIS FAIL\n",stderr);
        exit(2);
    }else if (err_type == SEMANTIC_ANALYSIS_UNDEF_VAR){
        fprintf("SEMANTIC ANALYSIS FAIL ( Undefined variable )\n",stderr);
        exit(3);
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN){
        fprintf("SEMANTIC ANALYSIS FAIL ( Uncompatibile type )\n",stderr);
        exit(4);
    }else if (err_type == SEMANTIC_ANALYSIS_BAD_COUNT_PARAMETERS){
        fprintf("SEMANTIC ANALYSIS FAIL ( Bad count of parameters )\n",stderr);
        exit(5);
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC){
        fprintf("SEMANTIC ANALYSIS FAIL ( Uncompatibile aritmetic type )\n",stderr);
        exit(6);
    }else if (err_type == SEMANTIC_ANALYSIS_FAIL_OTHERS){
        fprintf("SEMANTIC ANALYSIS FAIL ( Undefined error )\n",stderr);
        exit(7);
    }else if (err_type == RUNTIME_ERROR_WITH_NIL){
        fprintf("RUNTIME ERROR ( NIL )\n",stderr);
        exit(8);
    }else if (err_type == RUNTIME_ERROR_DIVIDING_BY_ZERO){
        fprintf("RUNTIME ERROR ( Dividing by zero )\n",stderr);
        exit(9);
    }else if (err_type == INTERNAL_FAILATURE){
        fprintf("INTERNAL FAILATURE\n",stderr);
        exit(99);
    }

    return 0;
    
}