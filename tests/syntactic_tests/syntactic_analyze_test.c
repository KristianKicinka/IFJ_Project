//#include "syntactic_analyze.c"
//#include "../../syntactic_analyze.h"
//#include "../../LL_table.c"
#include "../../LL_table.h"

int main(){

    Stack_symbol_t stack; 
    Stack_Init(&stack);
    Stack_Push(&stack, false, -42, NT_PROLOG); //pushnem pociatocny neterminal
    int err=0;

    while(!feof(stdin) && err==0){
        err=CheckGrammar(stack);
        //printf("nic %d\n", err);
    }

    Stack_Free(&stack);


   /*
   REVERSE RULES
    for(int i=number_of_derivations-1, i>=0, i--){
        push();
    }*/


    //Stack_Free(&stack);
    return 0;
}   