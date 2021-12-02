#include "expression_stack.h"

void exp_stack_init(Exp_stack_symbol *stack)
{
    stack->top = NULL;
}

bool empty_stack(Exp_stack_symbol *stack)
{
    if (stack->top == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool exp_stack_push(Exp_stack_symbol *stack, PSA_symbol symbol, Token_type type)
{
    Exp_stack_item *item = (Exp_stack_item *)malloc(sizeof(Exp_stack_item));

    if (item == NULL)
        return false;

    item->type = type;
    item->symbol = symbol;
    item->next = stack->top;

    stack->top = item;

    return true;
}

bool exp_stack_pop(Exp_stack_symbol *stack)
{
    if (stack->top != NULL)
    {
        Exp_stack_item *temp = stack->top;
        stack->top = temp->next;
        free(temp);

        return true;
    }
    return false;
}

Exp_stack_item *exp_stack_top(Exp_stack_symbol *stack)
{
    return stack->top;
}

bool exp_stack_free(Exp_stack_symbol *stack)
{
    while (!empty_stack(stack))
    {
        (exp_stack_pop(stack));
    }
    return (!stack->top);
}