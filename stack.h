#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "scanner.h"
//#include "LL_table.h"
#include "nterms.h"

//typedef enum nterms_type nterms_type;

#define TRUE 1
#define FALSE 0

typedef struct Stack_t{
    Token_type term; 
    nterms_type nterm;
    bool isterminal;
    struct Stack_t *next;
    //typ (ne)terminalu na vrchu
}Stack_t;

typedef struct Stack_symbol_t{
    Stack_t *top; 
}Stack_symbol_t;

void Stack_Init(Stack_symbol_t *);

bool Stack_Push(Stack_symbol_t *, bool, Token_type, nterms_type);

bool Stack_Pop(Stack_symbol_t *);

Token_type Stack_Top_Symbol_Terminal(Stack_symbol_t *);

nterms_type Stack_Top_Symbol_NonTerminal(Stack_symbol_t *);

bool Stack_Top_Symbol_Type(Stack_symbol_t *);

void Stack_Pop_Many(Stack_symbol_t *, int count);

Stack_t *Stack_Top(Stack_symbol_t *);

bool Stack_Is_Empty(Stack_symbol_t *);

bool Stack_Is_Full(Stack_symbol_t *);

bool Stack_Free(Stack_symbol_t *stack);

#endif