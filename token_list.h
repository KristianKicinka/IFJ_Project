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

typedef struct Token_list_t{
    Token *token;
    Token_list_t *next;
}Token_list;

void token_list_init(Token_list *token_list);

void token_list_insert(Token_list *token_list, Token *token);

void get_

#endif // !TOKEN_LIST_H