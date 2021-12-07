/**
 *
 * Project : Implementace překladače imperativního jazyka IFJ21.
 *
 * @file token_list.c
 * @author Michal Majer (xmajer22)
 * @brief
 *
 */

#include "token_list.h"

void token_list_init(token_list *list)
{
    list->firstElement = NULL;
    list->activeElement = NULL;
    list->lastElement = NULL;
}

void token_list_dispose(token_list *list)
{
    token_list_elementPtr ElemDel;

    while (list->firstElement != NULL)
    {
        ElemDel = list->firstElement;
        list->firstElement = list->firstElement->nextElement;
        free(ElemDel);
    }

    list->firstElement = NULL;
    list->activeElement = NULL;
    list->lastElement = NULL;
}

void token_list_insertfirst(token_list *list, Token token)
{
    token_list_elementPtr Elem = (token_list_elementPtr)malloc(sizeof(struct token_list_element));
    if (Elem == NULL)
    {
        // DLL_Error();
        return;
    }

    Elem->nextElement = list->firstElement;
    Elem->previousElement = NULL;
    Elem->token = token;

    if (list->firstElement == NULL)
        list->lastElement = Elem;
    else
        list->firstElement->previousElement = Elem;

    list->firstElement = Elem;
}

void token_list_insertlast(token_list *list, Token token)
{
    token_list_elementPtr Elem;
    Elem = (token_list_elementPtr)malloc(sizeof(struct token_list_element));
    if (Elem == NULL)
    {
        // token_list_Error();
        return;
    }

    Elem->nextElement = NULL;
    Elem->previousElement = list->lastElement;
    Elem->token = token;

    if (list->lastElement == NULL)
        list->firstElement = Elem;
    else
        list->lastElement->nextElement = Elem;

    list->lastElement = Elem;
}

void token_list_activefirst(token_list *list)
{
    list->activeElement = list->firstElement;
}

void token_list_activelast(token_list *list)
{
    list->activeElement = list->lastElement;
}

void token_list_getfirst(token_list *list, Token *dataPtr)
{
    if (list->firstElement != NULL)
    {
        *dataPtr = list->firstElement->token;
    }
    else
    {
        // token_list_Error();
        return;
    }
}

void token_list_getlast(token_list *list, Token *dataPtr)
{
    if (list->lastElement != NULL)
    {
        *dataPtr = list->lastElement->token;
    }
    else
    {
        // token_list_Error();
        return;
    }
}

void token_list_deletefirst(token_list *list)
{
    token_list_elementPtr FirstElem;
    FirstElem = list->firstElement;

    if (FirstElem != NULL)
    {
        if (list->lastElement == FirstElem)
            list->lastElement = NULL;
        else
            FirstElem->nextElement->previousElement = NULL;

        if (list->activeElement == FirstElem)
            list->activeElement = NULL;

        list->firstElement = FirstElem->nextElement;
        free(FirstElem);
    }
}

void token_list_deletelast(token_list *list)
{
    token_list_elementPtr LastElem;
    LastElem = list->lastElement;

    if (LastElem != NULL)
    {
        if (list->firstElement == LastElem)
            list->firstElement = NULL;
        else
            LastElem->previousElement->nextElement = NULL;

        if (list->activeElement == LastElem)
            list->activeElement = NULL;

        list->lastElement = LastElem->previousElement;
        free(LastElem);
    }
}

void token_list_next(token_list *list)
{
    list->activeElement = list->activeElement->nextElement;
}
