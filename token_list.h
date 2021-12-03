/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file token_list.h 
 * @author Kristián Kičinka (xkicin02)
 * @brief
 * 
 */


#ifndef TOKEN_LIST_H
#define TOKEN_LIST_H

#include "lexical_analysis.h"

typedef struct Token_list_element_t{
    Token *token;
    Token_list_t *next;
}Token_list_element;

typedef struct Token_list_t{
    Token_list_element *head;
}Token_list;

void token_list_init(Token_list *token_list);

void token_list_insert(Token_list *token_list, Token *token);

Token *token_list_get_token(Token_list *token_list);

bool token_list_is_empty(Token_list *token_list);

void token_list_dispose(Token_list *token_list);

#endif // !TOKEN_LIST_H