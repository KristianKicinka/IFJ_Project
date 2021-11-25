//#include "../syntactic_analyze.c"
//#include "../syntactic_analyze.h"
#include "../../LL_table.c"

int main(){

    Stack_symbol_t stack;
    Stack_Init(&stack);
    Stack_Push(&stack, FALSE, NULL, NT_PROLOG);
    Token token;
    token.type_of_token=TYPE_KW_REQUIRE;
    CheckGrammar(&token, &stack);

    for(int i=number_of_derivations-1, i>=0, i--){
        push();
    }


    Stack_Free(&stack);
    return 0;
}   