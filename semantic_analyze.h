#ifndef _SEMANTIC_ANALYZE_H
#define _SEMANTIC_ANALYZE_H

#include "LL_table.h"

typedef struct syntactic_data_t{

    symbol_table_t local_table;
    symbol_table_t global_table;

    table_item_t *current_item;
    
}Syntactic_data;


void process_semantic(Token *token,Syntactic_data *data);




#endif