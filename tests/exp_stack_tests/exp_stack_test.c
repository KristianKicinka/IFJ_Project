#include "../../expression_stack.h"
#include <stdio.h>
#include <stdlib.h>

void print_stack_items(Exp_stack_item *item);

int main(){

    Exp_stack_symbol stack;
    Exp_stack_symbol *my_stack = &stack;
    
    exp_stack_init (my_stack);    

    bool err = exp_stack_push(my_stack,PLUS,TYPE_INT_NUMBER);
    bool err_3 = exp_stack_push(my_stack,PLUS,TYPE_STRING);

    if(err == false || err_3 == false )
        return 0;
    
    print_stack_items(exp_stack_top(my_stack));
    print_stack_items(exp_stack_top(my_stack)->next);

    bool err2 = exp_stack_free(my_stack);

    if(err2 == false)
        return 0;

    return 0;
}

void print_stack_items(Exp_stack_item *item){
    printf("#######################\n");
    printf("symbol : %d \n",item->symbol);
    printf("type : %d \n",item->type);
    printf("#######################\n");
}