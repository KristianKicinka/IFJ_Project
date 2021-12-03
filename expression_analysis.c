#include "expression_analysis.h"
#include "lexical_analysis.h"
//#include "generator.h"
#include "error.h"
#include "expression_stack.h"

Exp_stack_symbol stack;

int PSA_table[TABLE][TABLE] =
{
//             | + | - | * | / | // | .. | # | < | <= | > | >= | == | ~= | ID | ( | ) | $$ |
/*|  + |*/     { R , R, PA , PA, PA , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R },
/*|  - |*/     { R , R, PA , PA, PA , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R },
/*|  * |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*|  / |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*| // |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*| .. |*/     { E , E , E , E , E  , R , E  , E , E  , E , E  , R  , R  , PA , PA, R , R },
/*|  # |*/     { R , R , R , R , R  , E , E  , R , R  , R , R  , R  , R  , PA , PA, R , R },  
/*|  < |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| <= |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*|  > |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| >= |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| == |*/     { PA, PA, PA, PA, PA , PA, PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| ~= |*/     { PA, PA, PA, PA, PA , PA, PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| ID |*/     { R , R , R , R , R  , R , E  , R , R  , R , R  , R  , R  , E  , E , R , R },
/*|  ( |*/     { PA, PA, PA, PA, PA , PA, PA , E , E  , E , E  , E  , E  , PA , PA, P , E },
/*|  ) |*/     { R , R , R , R , R  , R , E  , R , R  , R , R  , R  , R  , E  , E , R , R },
/*| $$ |*/     { PA, PA, PA, PA, PA , PA, PA , PA, PA , PA, PA , PA , PA , PA , PA, E , U }
};

static PSA_symbol symbol_from_token(Token* token)
{
    switch (token->type_of_token)
    {
    case TYPE_PLUS:
        return PLUS;
    
    default: 
        return DOLLAR;
    }

}

int precedence_analysis(Token token)  //TODO naplnit tokenom
{
    exp_stack_init(&stack);

    if(!exp_stack_push(&stack, DOLLAR, TYPE_UNSET))
    {
        stack_free_return(INTERNAL_FAILATURE);
    }

    bool success = false;

    Exp_stack_item *stack_top_term;
    PSA_symbol input_symbol;

    do
    {
        stack_top_term = exp_stack_top(&stack);
        input_symbol = symbol_from_token(&token);

        if(stack_top_term == NULL)
            stack_free_return(INTERNAL_FAILATURE);

        /*
        switch(PSA_table[get_prec_table_index(stack_top_terml->symbol)][get_prec_table_index(actual_symbol)])
        {
            case PA:
            case R:
            case P:
            case E:
            case U:
        }

        */

    }while(success==false);



    return 0;
}


int stack_free_return(Error_type ret_val)
{
        exp_stack_free(&stack);
        return ret_val;
}


