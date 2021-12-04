#ifndef _LL_TABLE_H
#define _LL_TABLE_H

#include <stdbool.h> 
#include "stack.h" //odst
#include "nterms.h"
#include "lexical_analysis.h"
#include "error.h"
#include "symtable.h"
#include "expression_analysis.h"
//#include "function_data_list.h"
#include "semantic_analyze.h"

#define SE -1
#define EPS -2
#define NUMBER_OF_RULES 74
#define NUMBER_OF_TERMS 40 //45?
#define NUMBER_OF_NTERMS 37
#define NUMBER_OF_DERIVATIONS 10
/*
typedef enum{
    //term keywords 0-19
    //scanner enum zdielanu s tymto enum
    //scanner odlisi ID FN, a ID
    -T_KW_REQUIRE=0, 
    -T_KW_DO=1,
    -T_KW_ELSE=2,
    -T_KW_END=3,
    -T_KW_FUNCTION=4,
    -T_KW_GLOBAL=5,
    -T_KW_IF=6,
    -T_KW_LOCAL=7,
    -T_KW_NIL=8,
    -T_TYPE_NUMBER=9,
    -T_KW_RETURN=10,
    -T_KW_THEN=11,
    -T_KW_WHILE=12,

    -T_TYPE_SEMICOLON=13,                  // [ ; ]
    -T_TYPE_RIGHT_BRACKET=14,              // [ ) ]
    -T_TYPE_LEFT_BRACKET=15,               // [ ( ]
    -T_TYPE_COMMA=16,                      // [ , ]
    -T_TYPE_DOUBLE_DOT=17,                 // [ : ]
    -T_EQUAL=18,                           // [ = ]
    -T_TOKEN_EOF=19,

    //term types 
    -T_TYPE_ID=20, //variable name
    -T_TYPE_FUNC_ID=21, //function name  //+FUNC_ID
    -T_TYPE_INT=22,              
    -T_TYPE_STRING=23,
    //pridane
    -T_STRING_CONST=24,
    -T_INT_CONST=25,
    -T_NUMBER_CONST=26,
    //koniec pridanych

    //TODO pridat expression + - * / ,...
    //spolu 38 vraj upravit aj define pocet
    -T_ADDITION=27,                         // [ + ]
    T_DIFFERENCE=28,                        // [ - ]
    T_MULTIPLICATION=29,                    // [ * ]
    T_DIVISION=30,                          // [ / ]
    T_DOUBLE_DIVISION=31,                   // [ // ]
    T_CONCATENATE=32,                       // [ .. ]
    T_LESS=33,                              // [ < ]
    T_LESS_OR_EQUAL=34,                     // [ <= ]
    T_GREATER=35,                           // [ > ]
    T_GREATER_OR_EQUAL=36,                  // [ >= ]
    T_NOT_EQUAL=37                          // [ ~= ]

}terms_type;
*/

typedef struct symbol_t {
    bool isterminal;
    Token_type term; 
    nterms_type nterm;
}symbol_t;

typedef struct rules_t{
    unsigned number_of_derivations;
    struct symbol_t right_side_of_derivation[NUMBER_OF_DERIVATIONS];
}rule_t;

/*

typedef struct syntactic_data_t{
    symbol_table_t global_table;
    symbol_table_t local_table;

    Token token;

    Additional_info info;
    Symbol_type type_of_symbol;

    //table_item_t *current_item;

}syntactic_data_t;
*/
//struktura pre preposielanie tokenov medzi syntaktickou a precedencnou
typedef struct prec_struct_t{
     int number_of_prec_ret_tokens; //pocet vratenych tokenov od precedencnej
     Token token[3];                //array tokenov vratenych od precedencnej
}prec_struct_t;
    

//void InitSyntacticData(syntactic_data_t *);

int CheckGrammar();


#endif