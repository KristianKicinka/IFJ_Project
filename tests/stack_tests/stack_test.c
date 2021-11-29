#include "../../stack.h"
//#include "../stack.c"
//#include <stdio.h>
//#include <stdbool.h>
//#include <stdlib.h>

void test_stack_insert(Stack_symbol_t *stack, Token_type term, nterms_type nterm, bool isterminal){
    int success=0;
        Stack_Push(stack, term, nterm, isterminal);
        printf("TEST STACK PUSH: %d\n", success);
}

void test_stack_print(Stack_symbol_t *stack){
    printf("TEST PRINT AND POP STACK: \n");
    int success=0;
    while(!Stack_Is_Empty(stack)){
        //printf("%d, %c\n", stack->top->stack_symbol, stack->top->stack_symbol_type);
        printf("%d, %d, %c\n", Stack_Top_Symbol_Terminal(stack), Stack_Top_Symbol_NonTerminal(stack), Stack_Top_Symbol_Type(stack));
        success=Stack_Pop(stack);
    }
     if(success){
         printf("TEST USPESNY: %d\n", success);
    }else{
        printf("TEST NEUSPESNY: %d\n", success);
    }
}
     
void test_till_top_terminal(Stack_symbol_t *stack){
    while(stack->top->isterminal==false){
        Stack_Pop(stack);
    }
    printf("Nasiel som terminal> %d, %c\n", Stack_Top_Symbol_Terminal(stack), Stack_Top_Symbol_Type(stack));
}

void test_stack_empty(Stack_symbol_t *stack){
    int empty=TRUE;
    empty=Stack_Is_Empty(stack);
    if(!empty){
        printf("Stack je prazdny: NIE\n");
    }else{
         printf("Stack je prazdny: ANO\n");
    }
}

int main(){
    Stack_symbol_t stack;
   // Stack_t *tmp;  

    Stack_Init (&stack);    

    test_stack_empty(&stack);

    test_stack_insert(&stack, TYPE_KW_WHILE, -42, true);

    test_stack_empty(&stack);
    
    test_till_top_terminal(&stack);

    test_stack_print(&stack);

    Stack_Free(&stack);

    return 0;
}

