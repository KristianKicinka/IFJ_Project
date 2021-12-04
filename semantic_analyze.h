#ifndef _SEMANTIC_ANALYZE_H
#define _SEMANTIC_ANALYZE_H

#include "LL_table.h"

typedef enum {
    S_START,
    S_FUNCTION_DEC,
    S_FUNCTION_PARAMETERS,
    S_FUNCTION_PARAMETER_LOAD,
    S_FUNCTION_PARAMETERS_LOAD,
    S_FUNCTION_RETURNS,
    S_FUNCTION_RETURN_LOAD,
    S_FUNCTION_RETURNS_LOAD,
    S_FUNCTION_IMPLEMENT,
    S_FUNCTION_CALL,
    S_VARIABLE_DEC
}Syntactic_state;

static Syntactic_state current_state = S_START;

typedef struct syntactic_data_t{

    symbol_table_t local_table;
    symbol_table_t global_table;

    table_item_t *current_item;

    Syntactic_state current_state;
    Token *token;
    nterms_type nterm;
    
}Syntactic_data;


void process_semantic(Syntactic_data *data);




#endif