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
    int label_index;

    bool in_function;
    bool in_statement;
    bool in_while;
    bool in_if;

    //table_item_t *current_item;

}syntactic_data_t;


void analyze();

void start(syntactic_data_t *parser_data);

void double_dot_nt(syntactic_data_t *parser_data);

void double_dots_nt(syntactic_data_t *parser_data);

void function_call(syntactic_data_t *parser_data);

void function_declaration(syntactic_data_t *parser_data);

void call_param(syntactic_data_t *parser_data);

void call_params(syntactic_data_t *parser_data);

void param_nt(syntactic_data_t *parser_data);

void params_nt(syntactic_data_t *parser_data);

void if_nt(syntactic_data_t *parser_data);

void code(syntactic_data_t *parser_data);

void code_if(syntactic_data_t *parser_data);

void code_if_nt(syntactic_data_t *parser_data);

void while_nt(syntactic_data_t *parser_data);

void assign_existing(syntactic_data_t *parser_data);

void to_assign(syntactic_data_t *parser_data);

void to_assign2(syntactic_data_t *parser_data);

void assign_value(syntactic_data_t *parser_data);

void assign_values(syntactic_data_t *parser_data);

#endif