/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file expression_analysis.h 
 * @author Michal Majer (xmajer22)
 * @brief  Zásobník pre precedenčnú analýzu
 * 
 */

#ifndef EXPRESSION_STACK
#define EXPRESSION_STACK

#include "expression_analysis.h"
#include "enums.h"

#define TRUE 1
#define FALSE 0

typedef struct stack_item
{
	PSA_symbol symbol;
	Token_type type;
	struct stack_item *next;
} Exp_stack_item;

typedef struct
{
    Exp_stack_item *top;
} Exp_stack_symbol;

void exp_stack_init(Exp_stack_symbol* );

bool exp_stack_push(Exp_stack_symbol* , PSA_symbol , Token_type);

bool exp_stack_pop(Exp_stack_symbol*);

Exp_stack_item* exp_stack_top(Exp_stack_symbol*);

bool exp_stack_free(Exp_stack_symbol*);

#endif