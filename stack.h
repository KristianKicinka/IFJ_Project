#ifndef _STACK_H
#define _STACK_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Stack_t{
    char stack_symbol;
    bool isterminal;
    struct Stack_t *next;
    //typ (ne)terminalu na vrchu
}Stack_t;

typedef struct Stack_symmbol_t{
    Stack_t *top; 
}Stack_symbol_t;

void Stack_Init(Stack_symbol_t *);

bool Stack_Push(Stack_symbol_t *, char, bool);

bool Stack_Pop(Stack_symbol_t *);

char Stack_Top_Symbol(Stack_symbol_t *);

char Stack_Top_Symbol_Type(Stack_symbol_t *);

void Stack_Pop_Many(Stack_symbol_t *, int count);

Stack_t *Stack_Top(Stack_symbol_t *);

bool Stack_Is_Empty(Stack_symbol_t *);

bool Stack_Is_Full(Stack_symbol_t *);

bool Stack_Free(Stack_symbol_t *stack);

#endif