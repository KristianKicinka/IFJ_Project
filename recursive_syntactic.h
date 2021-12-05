#ifndef _UZMATONEBAVI_H_
#define _UZMATONEBAVI_H_
#include <stdbool.h> 
#include "lexical_analysis.h"
#include "error.h"
#include "symtable.h"
#include "expression_analysis.h"
#include "generator.h"
//#include "function_data_list.h"



typedef struct syntactic_data_t{
    symbol_table_t global_table;
    symbol_table_t local_table;

    Token token;

    Custom_string my_string;
    

    Additional_info info;
    Symbol_type type_of_symbol;

    int parameter_index;
    //table_item_t *current_item;

}syntactic_data_t;


void analyze();

#endif