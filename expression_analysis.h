/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file lexical_analysis.h 
 * @author Michal Majer (xmajer22)
 * @brief  Precedenčná analýza
 * 
 */

#ifndef EXPRESSION_ANALYSIS
#define EXPRESSION_ANALYSIS

#include "lexical_analysis.h"
#include "error.h"
#include "custom_string.h"
#include "token_list.h"
#include "expression_stack.h"
#include "enums.h"
#include "recursive_syntactic.h"
#include <stdio.h>
#include <stdlib.h>

#define TABLE 17 // Size of the table

int precedence_analysis(syntactic_data_t *data);

void stack_free_return(Error_type error);

#endif // !EXPRESSION_ANALYSIS