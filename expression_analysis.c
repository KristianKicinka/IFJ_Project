/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file expression_analysis.h 
 * @author Michal Majer (xmajer22)
 * @brief  Precedenčná analýza (implementácia)
 * 
 */

#include "expression_analysis.h"

Exp_stack_symbol stack;
Exp_stack_symbol help_stack;
//Custom_string *cstring;
token_list infix;
token_list postfix;

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
    case TYPE_IDENTIFICATOR_VARIABLE:
        return ID;
    
    case TYPE_LEFT_ROUND_BRACKET:
        return LBRACKET;
    
    case TYPE_RIGHT_ROUND_BRACKET:
        return RBRACKET;

    default: 
        return DOLLAR;
    }

}

void free_everything()
{
    token_list_dispose(&infix);
    token_list_dispose(&postfix);
    exp_stack_free(&stack);
    exp_stack_free(&help_stack);
}

void stack_insert_after_term(Exp_stack_symbol* stack, PSA_symbol symbol, Token_type type)
{
    Exp_stack_item *top;
    top = exp_stack_top(stack);

    if(top->symbol == EXPRESSION || top->symbol == EXPRESSION_I 
    || top->symbol == EXPRESSION_N || top->symbol == EXPRESSION_S)
    {
        exp_stack_push(&help_stack, top->symbol, top->type);    // na pomocnehy zasobnik si nahram top zasobniku
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

bool reduce_by_rules(int pushes, Token token, syntactic_data_t *data)
{
    Exp_stack_item *stacksym = exp_stack_top(&help_stack);

    if(pushes == 1)
    {
        if(stacksym->type == TYPE_STRING)
        {
            exp_stack_push(&stack, EXPRESSION_S, TYPE_STRING);
            exp_stack_pop(&help_stack);
            return true;

        }else if(stacksym->type == TYPE_INT_NUMBER){
            exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
            exp_stack_pop(&help_stack);
            return true;

        }else if(stacksym->type == TYPE_DOUBLE_NUMBER){
            exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
            exp_stack_pop(&help_stack);
            return true;

        }else{
            exp_stack_push(&stack, EXPRESSION, TYPE_UNSET);
            exp_stack_pop(&help_stack);
            return true;
        }

    }else if(pushes == 2){
        
        if(stacksym->type == TYPE_HASHTAG && stacksym->symbol == LENG){
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);
            if(stacksym->type == TYPE_STRING && stacksym->symbol == EXPRESSION_S)
            {
                exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
                return true;

            }else{
                stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
            }
        }else{
             stack_free_return(SEMANTIC_ANALYSIS_FAIL_OTHERS, data);
        }

    }else if(pushes == 3)
    {

        // E string
        if(stacksym->type == TYPE_STRING){              
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);

            // ..
            if(stacksym->type == TYPE_STRING_CONCAT){   
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_STRING){      // E string
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_S, TYPE_STRING);
                    return true;

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }
            // <, <=, >, >=, ~=, ==
            }else if(stacksym->type == TYPE_LTHEN || stacksym->type == TYPE_LEKV || stacksym->type == TYPE_GTHEN
                  || stacksym->type == TYPE_GEKV  || stacksym->type == TYPE_NEKV || stacksym->type == TYPE_EKV){     
                 exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_STRING){      // E string
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_S, TYPE_STRING);
                    return true;

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }
            }else{
                stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
            }

        // (
        }else if(stacksym->type == TYPE_LEFT_ROUND_BRACKET){
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);

            if(stacksym->type == TYPE_STRING){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_RIGHT_ROUND_BRACKET){
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_S, TYPE_STRING);
                    return true;

                }else{
                    stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
                }
            }else if(stacksym->type == TYPE_INT_NUMBER){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_RIGHT_ROUND_BRACKET){
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
                    return true;

                }else{
                    stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
                }
            }else if(stacksym->type == TYPE_DOUBLE_NUMBER){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_RIGHT_ROUND_BRACKET){
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
                    return true;

                }else{
                    stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
                }
            } 

        // E int    
        }else if(stacksym->type == TYPE_INT_NUMBER){
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);

            if(stacksym->type == TYPE_LTHEN || stacksym->type == TYPE_LEKV  || stacksym->type == TYPE_GTHEN
            || stacksym->type == TYPE_GEKV  || stacksym->type == TYPE_NEKV  || stacksym->type == TYPE_EKV
            || stacksym->type == TYPE_PLUS  || stacksym->type == TYPE_MINUS || stacksym->type == TYPE_MULTIPLICATE){

                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_INT_NUMBER){
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
                    return true;

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else if(stacksym->type == TYPE_DIVIDE_INT){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_INT_NUMBER){
                    // zero division handling
                    if(token.token_info.integer_value != 0){
                        exp_stack_pop(&help_stack);
                        exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
                        return true;
                    }else{
                        stack_free_return(RUNTIME_ERROR_DIVIDING_BY_ZERO, data);
                    }

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else if(stacksym->type == TYPE_DIVIDE){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_INT_NUMBER){
                    // zero division handling
                    if(token.token_info.integer_value != 0){
                        exp_stack_pop(&help_stack);
                        exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
                        return true;

                    }else{
                        stack_free_return(RUNTIME_ERROR_DIVIDING_BY_ZERO, data);
                    }

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else{
                stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
            }

        // E num    
        }else if(stacksym->type == TYPE_DOUBLE_NUMBER){
            exp_stack_pop(&help_stack);
            stacksym = exp_stack_top(&help_stack);

            if(stacksym->type == TYPE_LTHEN || stacksym->type == TYPE_LEKV  || stacksym->type == TYPE_GTHEN
            || stacksym->type == TYPE_GEKV  || stacksym->type == TYPE_NEKV  || stacksym->type == TYPE_EKV
            || stacksym->type == TYPE_PLUS  || stacksym->type == TYPE_MINUS || stacksym->type == TYPE_MULTIPLICATE){

                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_DOUBLE_NUMBER){
                    exp_stack_pop(&help_stack);
                    exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
                    return true;

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else if(stacksym->type == TYPE_DIVIDE){

                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_DOUBLE_NUMBER){
                    // zero division handling
                    if(token.token_info.double_value != 0.0){
                        exp_stack_pop(&help_stack);
                        exp_stack_push(&stack, EXPRESSION_N, TYPE_DOUBLE_NUMBER);
                        return true;

                    }else{
                        stack_free_return(RUNTIME_ERROR_DIVIDING_BY_ZERO, data);
                    }

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else if(stacksym->type == TYPE_DIVIDE_INT){
                exp_stack_pop(&help_stack);
                stacksym = exp_stack_top(&help_stack);

                if(stacksym->type == TYPE_DOUBLE_NUMBER){
                    // zero division handling
                    if(token.token_info.double_value != 0.0){
                        exp_stack_pop(&help_stack);
                        exp_stack_push(&stack, EXPRESSION_I, TYPE_INT_NUMBER);
                        return true;

                    }else{
                        stack_free_return(RUNTIME_ERROR_DIVIDING_BY_ZERO, data);
                    }

                }else{
                    stack_free_return(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC, data);
                }

            }else{
                stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
            }

        }else{
            stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
        }

    }else{
            stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
    }

    return false;
}

void stack_reduce(Exp_stack_symbol* stack, Token token, syntactic_data_t *data)
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

    reduce_by_rules(number_of_pushes, token, data);

}

Exp_stack_item *top_term(Exp_stack_symbol* stack)
{
    Exp_stack_item *top = exp_stack_top(stack);;
    Exp_stack_item *temp;

    exp_stack_push(&help_stack, top->symbol, top->type);    
    exp_stack_pop(stack);                                   
    top = exp_stack_top(stack);
    temp = exp_stack_top(&help_stack);                      
    exp_stack_push(stack, temp->symbol, temp->type);          
    exp_stack_pop(&help_stack);                             

    return top;
}


void precedence_analysis(syntactic_data_t *data)
{
    Token backup;
    exp_stack_init(&stack);
    exp_stack_init(&help_stack);  // inicializacia pomocneho zasobniku

    if(exp_stack_push(&stack, DOLLAR, TYPE_UNSET) == false)
    {
        stack_free_return(INTERNAL_FAILATURE, data);
    }

    bool success = false;

    Exp_stack_item *stack_top_term;
    PSA_symbol input_symbol;
    token_list_init(&infix);
    token_list_init(&postfix);

    char *identificator;
   

    do
    {
        if(data->token.type_of_token == TYPE_IDENTIFICATOR_VARIABLE){
            identificator = data->token.token_info.custom_string->string_value;

            printf("Identifikator je %s\n", identificator);
            printf("token value before %d\n", data->token.type_of_token);
            if(search_item(&data->local_table, identificator)==NULL){      
                stack_free_return(SEMANTIC_ANALYSIS_UNDEF_VAR, data);
            }else
            backup.type_of_token = data->token.type_of_token;
            data->token.type_of_token = *get_symbol_variable_type(&data->local_table, identificator);

            printf("token value after %d\n", data->token.type_of_token);
        }

        stack_top_term = exp_stack_top(&stack);
        input_symbol = symbol_from_token(&data->token);

        if(stack_top_term == NULL)
            stack_free_return(INTERNAL_FAILATURE, data);

        if(input_symbol == DOLLAR){
            if(data->list_of_tokens.firstElement == NULL){
                token_list_insertfirst(&data->list_of_tokens, data->token);
                data->list_of_tokens.lastElement = data->list_of_tokens.firstElement;
                data->list_of_tokens.activeElement = data->list_of_tokens.firstElement;
                printf("Toto je token ulozeny do listu: %d\n", data->list_of_tokens.activeElement->token.type_of_token);
            }
        }

        printf("-----------------------------------\n");
        printf("Vrch stacku: %u\n", stack_top_term->symbol);

        if(stack_top_term->symbol == EXPRESSION   || stack_top_term->symbol == EXPRESSION_I 
        || stack_top_term->symbol == EXPRESSION_N || stack_top_term->symbol == EXPRESSION_S)
        {
                    stack_top_term = top_term(&stack);
        }

        printf("Neterminal: %u\n", stack_top_term->symbol);
        printf("Vstup: %u\n", input_symbol);

        // TODO
        // ked dostanem ID tak overim ci je deklarovane a definovane. ak nie tak je to semanticka chyba v programe CHYBA 3
        // osetrenie prace s nil len ked je eq a not eq
        
        switch(PSA_table[stack_top_term->symbol][input_symbol])
        {
            case PA:          
                printf("PA\n");
                token_list_insertlast(&infix, data->token);
                stack_insert_after_term(&stack, input_symbol, data->token.type_of_token);
                generate_token(&data->token, &data->my_string);
                break;

            case R:
                printf("R\n");
                stack_reduce(&stack, data->token, data);
                break;

            case P:
                printf("P\n");
                token_list_insertlast(&infix, data->token);
                exp_stack_push(&stack, input_symbol, data->token.type_of_token);
                generate_token(&data->token, &data->my_string);
                break;

            case E:
                printf("E\n");
                token_list_insertlast(&infix, data->token);

                token_list_insertfirst(&data->list_of_tokens, backup);
                data->list_of_tokens.lastElement = data->list_of_tokens.firstElement;
                data->list_of_tokens.activeElement = data->list_of_tokens.firstElement;
                printf("Toto je token ulozeny do listu: %d\n", data->list_of_tokens.activeElement->token.type_of_token);

                generate_token(&data->token, &data->my_string);

                if(data->token.type_of_token == TYPE_ASSIGN || data->token.type_of_token == TYPE_COMMA 
                || data->token.type_of_token == TYPE_LEFT_ROUND_BRACKET){
                    
                    token_list_insertlast(&data->list_of_tokens, data->token);
                    printf("Toto je druhy token ulozeny do listu: %d\n", data->list_of_tokens.lastElement->token.type_of_token);
                    input_symbol = DOLLAR;

                }else{
                    stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
                }
                break;

            case U:
                printf("U\n");
                if (stack_top_term->symbol == DOLLAR && input_symbol == DOLLAR)
			    	success = true;
			    else
				    stack_free_return(SYNTAX_ANALYSIS_FAIL, data);
			    break;
            
            default:
                stack_free_return(SYNTAX_ANALYSIS_FAIL, data);

        }


    }while(success==false);

    
    printf("\n-------------------------------------------------------\n");
    token_list_activefirst(&infix);

    while (infix.activeElement != NULL)
    {
        printf("%u ", infix.activeElement->token.type_of_token);
        token_list_next(&infix);
    }
    printf("\n-------------------------------------------------------\n");


    stack_top_term = exp_stack_top(&stack);

    if(stack_top_term == NULL)
        stack_free_return(INTERNAL_FAILATURE, data);
    
    if(!(stack_top_term->symbol == EXPRESSION_I || stack_top_term->symbol == EXPRESSION_N || stack_top_term->symbol == EXPRESSION_S))
        stack_free_return(SYNTAX_ANALYSIS_FAIL, data);



    free_everything();

    printf("\n########################################\n\n");
    printf("#   Synatx analysis was succesfull !   #\n");
    printf("\n########################################\n");
}


void stack_free_return(Error_type error, syntactic_data_t *data)
{
        free_everything();
        custom_string_free_memory(&data->my_string);
        process_error(error);
}
