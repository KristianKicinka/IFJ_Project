/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file recursive_syntactic.h
 * @author Andrej Ľupták (xlupta05)
 * @author Kristián Kičinka (xkicin02)
 * @brief Syntaktická a sémantická analýza (rozhranie)
 * 
 */

#ifndef _UZMATONEBAVI_H_
#define _UZMATONEBAVI_H_
#include <stdbool.h> 
#include "lexical_analysis.h"
#include "error.h"
#include "symtable.h"
#include "expression_analysis.h"
#include "generator.h"
#include "enums.h"
//#include "function_data_list.h"

void analyze();
void check_retuned_tokens_from_expression_analysis(syntactic_data_t *parser_data);
void parser_data_init(syntactic_data_t *data);
void start(syntactic_data_t *parser_data);
void double_dot_nt(syntactic_data_t *parser_data);
void double_dots_nt(syntactic_data_t *parser_data);
void function(syntactic_data_t *parser_data);
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
void optional_ekv(syntactic_data_t *parser_data);
void assign_new(syntactic_data_t *parser_data);
void argument(syntactic_data_t *parser_data);
void arg(syntactic_data_t *parser_data);
void check_ret_prarams(syntactic_data_t *parser_data);
void return_nt(syntactic_data_t *parser_data);

#endif