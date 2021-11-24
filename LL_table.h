#ifndef _LL_TABLE_H
#define _LL_TABLE_H

#include <stdbool.h> 
#include "scanner.h"
#define SE -1
#define EPS -2
#define NUMBER_OF_RULES 70
#define NUMBER_OF_TERMS 38 //45?
#define NUMBER_OF_NTERMS 34
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
    -T_ADDITION=27,                          // [ + ]
    T_DIFFERENCE=28,                        // [ - ]
    T_MULTIPLICATION=29,                    // [ * ]
    T_DIVISION=30,                          // [ / ]
    T_DOUBLE_DIVISION=31,                   // [ // ]
    T_CONCATENATE=32,                       // [ .. ]
    T_LESS=33,                              // [ < ]
    T_LESS_OR_EQUAL=34,                     // [ <= ]
    T_GREATER=35,                           // [ > ]
    T_GREATER_OR_EQUAL=36,                   // [ >= ]
    T_NOT_EQUAL=37                          // [ ~= ]

}terms_type;
*/
typedef enum{
    //neterminaly
    NT_PROLOG=0,
    NT_VALUE=1,
    NT_ASSVAL=2,
    NT_DATA_TYPE=3,
    NT_EXPRESSION=4,
    NT_FUNC_DEC=5,
    NT_PARAM=6,
    NT_PARAMS=7,
    NT_FUNC=8,
    NT_ARG=9,
    NT_ARGUMENT=10,
    NT_RET_ARG=11,
    NT_RET_ARGS=12,
    NT_CODE=13,
    NT_RETURN=14,
    NT_CHECK_RET_PARAMS=15,
    NT_RETURNS=16,
    NT_FUNC_CALL=17,
    NT_CALL_PARAM=18,
    NT_CALL_PARAMS=19,
    NT_ASSIGN_EXISTING=20,
    NT_TO_ASSIGN=21,
    NT_ASSIGN_VALUE=22,
    NT_ASSIGN_VALUES=23,
    NT_TO_ASSIGN2=24,
    NT_ASSIGN_NEW=25,
    NT_ASSIGN=26,
    NT_WHILE=27,
    NT_IF=28,
    NT_START=29,
    NT_DOUBLE_DOT=30,
    NT_DOUBLE_DOTS=31,
    NT_CHECK_EOF=32,
    NT_CODE_IF=33,
    NT_END=34
   

}nterms_type;

typedef struct symbol_t {
    bool isterminal;
    Token_type term; 
    nterms_type nterm;
}symbol_t;

typedef struct rules_t{
    unsigned number_of_derivations;
    struct symbol_t right_side_of_derivation[NUMBER_OF_DERIVATIONS];
}rule_t;


#endif