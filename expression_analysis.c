#include "expression_analysis.h"
#include "lexical_analysis.h"
//#include "generator.h"
#include "error.h"
#include "expression_stack.h"

Exp_stack_symbol stack;
Exp_stack_symbol help_stack;

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

    case TYPE_MINUS:
        return MINUS;
    
    case TYPE_MULTIPLICATE:
        return MUL;

    case TYPE_DIVIDE:
        return DIV;

    case TYPE_DIVIDE_INT:
        return DDIV;
    
    case TYPE_STRING_CONCAT:
        return CONC;
    
    case TYPE_HASHTAG:
        return LENG;

    case TYPE_LTHEN:
        return LESS;

    case TYPE_LEKV:
        return LESSOE;
    
    case TYPE_GTHEN:
        return MORE;

    case TYPE_GEKV:
        return MOREOE;

    case TYPE_EKV:
        return EQ;
    
    case TYPE_NEKV:
        return NOTEQ;
    
    case TYPE_STRING:
    case TYPE_INT_NUMBER:
    case TYPE_DOUBLE_NUMBER:
        return ID;
    
    case TYPE_LEFT_ROUND_BRACKET:
        return LBRACKET;
    
    case TYPE_RIGHT_ROUND_BRACKET:
        return RBRACKET;
    
    default: 
        return DOLLAR;
    }

}

void stack_insert_after_term(Exp_stack_symbol* stack, PSA_symbol symbol, Token_type type)
{
    Exp_stack_item *top;
    top = exp_stack_top(stack);

    if(top->symbol == EXPRESSION || top->symbol == EXPRESSION_I 
    || top->symbol == EXPRESSION_N || top->symbol == EXPRESSION_S)
    {
        exp_stack_push(&help_stack, top->symbol, top->type);    // na pomocnehy zasobnik si nahram tom zasobniku
        exp_stack_pop(stack);                                   // odstranim vrch zasobniku
        exp_stack_push(stack, PUSH_SYMBOL, TYPE_UNSET);         // na zasobnik nahram <
        top = exp_stack_top(&help_stack);                       // top si naplnim hodnotou na pomocnom zasobniku
        exp_stack_push(stack, top->symbol, top->type);          // na zasobnik nahram top z pomocneho zasobniku
        exp_stack_push(stack, symbol, type);                    // na zasobnik nahram prichadzajuci symbol
        exp_stack_pop(&help_stack);                             // vyprazdnim pomocny zasobnik
    }else{  // ak na vrchole zasobnika nie s
        exp_stack_push(stack, PUSH_SYMBOL, TYPE_UNSET);         // na zasobnik nahram <
        exp_stack_push(stack, symbol, type);                    // na zasobnik nahram prichadzajuci symbol
    }
}

void reduce_by_rules(int pushes)
{
    Exp_stack_item *stacksym = exp_stack_top(&help_stack);
    if(pushes == 1)
    {
        if(stacksym->type == TYPE_STRING)
        {
            exp_stack_push(&stack, EXPRESSION_S, TYPE_STRING);
            exp_stack_pop(&help_stack);

        }else if(stacksym->type == TYPE_INT_NUMBER){
            exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
            exp_stack_pop(&help_stack);

        }else if(stacksym->type == TYPE_DOUBLE_NUMBER){
            exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
            exp_stack_pop(&help_stack);

        }else{
            exp_stack_push(&stack, EXPRESSION, TYPE_UNSET);
            exp_stack_pop(&help_stack);
        }

    }else if(pushes == 2){
        
        if(stacksym->type == TYPE_HASHTAG && stacksym->symbol == LENG){
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);
            if(stacksym->type == TYPE_STRING && stacksym->symbol == EXPRESSION_S)
            {
                exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);

            }else{
                stack_free_return(SYNTAX_ANALYSIS_FAIL);
            }
        }else{
             stack_free_return(SYNTAX_ANALYSIS_FAIL);
        }

    }else if(pushes == 3)
    {
        //TODO vsetko ostatne
    }
}

void stack_reduce(Exp_stack_symbol* stack)
{   
    Exp_stack_item *top = exp_stack_top(stack);
    int number_of_pushes = 0;

    while(top->symbol != PUSH_SYMBOL)
    {
        exp_stack_push(&help_stack, top->symbol, top->type);
        number_of_pushes++;
        exp_stack_pop(stack);
        top = exp_stack_top(stack);
    }

    if(top->symbol == PUSH_SYMBOL)
        exp_stack_pop(stack);

    reduce_by_rules(number_of_pushes);

    
}

int precedence_analysis(Token token)
{
    exp_stack_init(&stack);
    exp_stack_init(&help_stack);  // inicializacia pomocneho zasobniku


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

        // TODO
        // ked dostanem ID tak overim ci je deklarovane a definovane. ak nie tak je to semanticka chyba v programe CHYBA 3
        // osetrenie prace s nil len ked je eq a not eq
        //  osetrenie deleneie nulou
        
        switch(PSA_table[stack_top_term->symbol][input_symbol])
        {
            case PA:
                stack_insert_after_term(&stack, input_symbol, token.type_of_token);
                //TODO precitaj dalsi symbol zo vstupu
                break;
            case R:
                stack_reduce(&stack);
                break;
            case P:
                exp_stack_push(&stack, input_symbol, token.type_of_token);
                //TODO precitaj dalsi symbol zo vstupu
                break;

            case E:
                stack_free_return(SYNTAX_ANALYSIS_FAIL);
                //TODO overit ci dalsie nie je ID a ciarka
                break;
            case U:
               if (stack_top_term->symbol == DOLLAR && input_symbol == DOLLAR)
			    	success = true;
			    else
				    stack_free_return(SYNTAX_ANALYSIS_FAIL);
			    break;
        }


    }while(success==false);



    return 0;
}


void stack_free_return(Error_type error)
{
        exp_stack_free(&stack);
        exp_stack_free(&help_stack);
        process_error(error);
}


