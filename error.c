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
        fprintf(stderr,"LEXICAL ANALYSIS FAIL\n");
        exit(1);
    }else if (err_type == SYNTAX_ANALYSIS_FAIL){
        fprintf(stderr,"SYNTAX ANALYSIS FAIL\n");
        exit(2);
    }else if (err_type == SEMANTIC_ANALYSIS_UNDEF_VAR){
        fprintf(stderr,"SEMANTIC ANALYSIS FAIL ( Undefined variable )\n");
        exit(3);
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN){
        fprintf(stderr,"SEMANTIC ANALYSIS FAIL ( Uncompatibile type )\n");
        exit(4);
    }else if (err_type == SEMANTIC_ANALYSIS_BAD_COUNT_PARAMETERS){
        fprintf(stderr,"SEMANTIC ANALYSIS FAIL ( Bad count of parameters )\n");
        exit(5);
    }else if (err_type == SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC){
        fprintf(stderr,"SEMANTIC ANALYSIS FAIL ( Uncompatibile aritmetic type )\n");
        exit(6);
    }else if (err_type == SEMANTIC_ANALYSIS_FAIL_OTHERS){
        fprintf(stderr,"SEMANTIC ANALYSIS FAIL ( Undefined error )\n");
        exit(7);
    }else if (err_type == RUNTIME_ERROR_WITH_NIL){
        fprintf(stderr,"RUNTIME ERROR ( NIL )\n");
        exit(8);
    }else if (err_type == RUNTIME_ERROR_DIVIDING_BY_ZERO){
        fprintf(stderr,"RUNTIME ERROR ( Dividing by zero )\n");
        exit(9);
    }else if (err_type == INTERNAL_FAILATURE){
        fprintf(stderr,"INTERNAL FAILATURE\n");
        exit(99);
    }

    return;
    
}
