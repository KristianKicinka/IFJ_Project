#include "stack.h"
#include "error.h"

void Stack_Init(Stack_symbol_t *stack){ 
	stack->top=NULL;
}

bool Stack_Pop(Stack_symbol_t *stack){
    if(!Stack_Is_Empty(stack)){
        Stack_t *topop=stack->top;
        stack->top=topop->next;
        free(topop);
        if(stack->top==NULL){
           // printf("STACK POP> posledny znak bol popnuty\n");
            return TRUE; 
        }
        return TRUE; //zo zasobnika sa pop podaril
    }
    return FALSE; //pop sa nepodaril
}

bool Stack_Push(Stack_symbol_t *stack, bool isterminal, Token_type term, nterms_type nterm){
       Stack_t *new_symbol = (Stack_t*)malloc(sizeof(Stack_t));
       if(new_symbol==NULL){
          // printf("Malloc noveho itemu do stacku zlyhal\n");
           process_error(INTERNAL_FAILATURE));
           return FALSE; //malloc sa nepodaril
       }
       new_symbol->term=term;
       new_symbol->nterm=nterm;
       new_symbol->isterminal=isterminal;
       new_symbol->next=stack->top;
       stack->top=new_symbol;
       return TRUE; //znak sa uspesne pushol na stack
}
bool Stack_Is_Empty(Stack_symbol_t *stack){
    if(stack->top==NULL){
        //printf("STACK IS EMPTY> Zasobnik je prazdny\n");
        return TRUE; //FALSE - zasobnik je prazdny
    }else{
        return FALSE; //TRUE - zasobnik nie je prazdny
    }
    
}
 //tuto funkciu ani nebude treba
Stack_t *Stack_Top(Stack_symbol_t *stack){
    if(Stack_Is_Empty(stack)){ //zasobnik je prazdny
        //printf("STACK TOP> zasobnik je uz prazdny\n");
        return NULL;
    }else{
        return stack->top; //NULL v pripade, ze je prazdny
    }
}

Token_type Stack_Top_Terminal(Stack_symbol_t *stack){
    if(Stack_Is_Empty(stack)){ //zasobnik je prazdny
        //printf("STACK TOP TYPE> zasobnik je uz prazdny\n");
        return FALSE;
    }else{
        return stack->top->term;
    }
}

nterms_type Stack_Top_NonTerminal(Stack_symbol_t *stack){
    if(Stack_Is_Empty(stack)){ //zasobnik je prazdny
        //printf("STACK TOP TYPE> zasobnik je uz prazdny\n");
        return FALSE;
    }else{
        return stack->top->nterm;
    }
}

bool Stack_Top_Symbol_Type(Stack_symbol_t *stack){
    if(Stack_Is_Empty(stack)){ //zasobnik je prazdny
        //printf("STACK TOP TYPE> zasobnik je uz prazdny\n");
        return FALSE;
    }else{
        return stack->top->isterminal;
    }
}

void Stack_Pop_Many(Stack_symbol_t *stack, int count){
    //TODO navratova hodnota
    for (int i = 0; i < count; i++){
      Stack_Pop(stack); //TRUE uspesne, FALSE neuspesne
    }
}    
//popuje, az kym sa neuvolni cely zasobnik
bool Stack_Free(Stack_symbol_t *stack){
    while(!Stack_Is_Empty(stack)){
       // printf("cistim\n");
        (Stack_Pop(stack)); //vracia FALSE ked je zasobnik prazndy 
    }
    return(!stack->top); //vracia TRUE ked sa zasobnik uspesne vyprazdnil
}