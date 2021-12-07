/**
 *
 * Project : Implementace překladače imperativního jazyka IFJ21.
 *
 * @file token_list.h
 * @author Michal Majer (xmajer22)
 * @brief
 *
 */

#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "lexical_analysis.h"
#include "error.h"

#define FALSE 0
#define TRUE 1

typedef struct token_list_element
{
    Token token;
    struct token_list_element *previousElement;
    struct token_list_element *nextElement;
} * token_list_elementPtr;

typedef struct
{
    token_list_elementPtr firstElement;
    token_list_elementPtr activeElement;
    token_list_elementPtr lastElement;
} token_list;

void token_list_init(token_list *);

void token_list_dispose(token_list *);

void token_list_insertfirst(token_list *, Token);

void token_list_insertlast(token_list *, Token);

void token_list_activefirst(token_list *);

void token_list_activelast(token_list *);

void token_list_getfirst(token_list *, Token *);

void token_list_getlast(token_list *, Token *);

void token_list_deletefirst(token_list *);

void token_list_deletelast(token_list *);

void token_list_next(token_list *);

#endif // !TOKEN_LIST_H