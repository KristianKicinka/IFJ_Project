/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file recursive_syntactic.c
 * @author Andrej Ľupták (xlupta05)
 * @author Kristián Kičinka (xkicin02)
 * @brief Syntaktická a sémantická analýza (implementácia)
 * 
 */

#include "recursive_syntactic.h"
/*
void check_declaration(syntactic_data_t *parser_data){
    if(parser_data->in_declaration==true){
        set_is_declared(&parser_data->global_table, parser_data->current_item,true);
        parser_data->in_declaration=false;
    }
}
*/
void optional_ekv(syntactic_data_t *parser_data){
    //sem pridem s KW_ASSIGN <=>
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("po generovani tokenu v optional_ekv: %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){      //LOCAL A : = foo()
        function_call(parser_data);
        //alebo code????? oba by mali fungovat
    }else if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET || 
             parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE ||
             parser_data->token.type_of_token==TYPE_INT_NUMBER ||
             parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
             parser_data->token.type_of_token==TYPE_KW_NIL){          //LOCAL A : = a||2
             //TODO volat BOTTOM-UP
             //precedence_analysis(parser_data);
             check_retuned_tokens_from_expression_analysis(parser_data);
             printf("optional_ekv vola code s tokenom %d\n", parser_data->token.type_of_token);
             code(parser_data); //moze byt deklarovana a zaroven inicializovana iba jedna hodnota, po uspesnej precedencnej idem spat do kodu a cakam, co je dalsie
    }else{
        //code(parser_data); //toto je tu asi duplicitne ale Budis - ked ju raz zacnes pit uz neprestanes
        printf("SE at optional_ekv\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}
void assign_new(syntactic_data_t *parser_data){
    //sem pridem s KW_LOCAL
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        //SEMANTIC
        char *identificator=parser_data->token.token_info.custom_string->string_value;
        if(search_item(&parser_data->local_table,identificator)!=NULL){
            custom_string_free_memory(&parser_data->my_string);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        parser_data->current_item_var =  insert_symbol_variable(&parser_data->local_table, identificator);
        set_is_declared(&parser_data->local_table, parser_data->current_item_var, true);


        //END SEMANTIC

        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_COLON){               //<LOCAL> <ID> <:>
            check_retuned_tokens_from_expression_analysis(parser_data);
            if(parser_data->token.type_of_token==TYPE_KW_INTEGER ||
               parser_data->token.type_of_token==TYPE_KW_NUMBER ||
               parser_data->token.type_of_token==TYPE_KW_STRING ||
               parser_data->token.type_of_token==TYPE_KW_NIL){       //<LOCAL> <ID> <:> <INT>

                set_symbol_variable_type(&parser_data->local_table,parser_data->current_item_var, parser_data->token.type_of_token);

                check_retuned_tokens_from_expression_analysis(parser_data);
                if(parser_data->token.type_of_token==TYPE_ASSIGN){         //<LOCAL> <ID> <:> <INT> <=>
                    //assign_nt(parser_data);
                    printf("assign_new volam optional_EKV s tokenom %d\n" ,parser_data->token.type_of_token);   
                    optional_ekv(parser_data);
                }else{                                              //iny vstup ako <=> znamena iba deklraraciu bez inicializacie
                    printf("assign_new do code sa vraciam s tokenom %d\n" ,parser_data->token.type_of_token);
                    code(parser_data);
                }                
            }
        }
    }
}

void assign_values(syntactic_data_t *parser_data){
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //a=foo()
        code(parser_data);
    }
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("Token v assign_valueS %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
           parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION ||
           parser_data->token.type_of_token==TYPE_INT_NUMBER ||
           parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER){ // ...=a,b || ...=foo(), bar() || ...=2,3
            //volat BOTTOM UP
            //precedence_analysis(parser_data);
            assign_values(parser_data);
        }else{
            printf("SE at asssign_valueS\n");
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        code(parser_data);
    }
}

void assign_value(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("Token v assign_value %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
       parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION || 
       parser_data->token.type_of_token==TYPE_INT_NUMBER ||
       parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
       parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){ // ...=a || ...=foo() || ...=2
        //volat BOTTOM UP
        //precedence_analysis(parser_data);
        assign_values(parser_data);
    }else{
        printf("SE at asssign_value\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void to_assign2(syntactic_data_t *parser_data){
    //tu mi pride a,a 
    //a loopujem kym nenarazim na =
    //SEMANTIC

    char *identificator = parser_data->token.token_info.custom_string->string_value;
    parser_data->current_item_var=search_item(&parser_data->local_table, identificator);
    if(parser_data->current_item_var==NULL){    //snaha o priradenie do nedeklarovanej premennej
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
    //END SEMANTIC
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("token v to assing2 %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_ASSIGN){
        assign_value(parser_data); // a,a=
    }else if(parser_data->token.type_of_token==TYPE_COMMA){ //a,a,
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //a,a,a
            to_assign2(parser_data);
        }else{
            printf("SE at to_assign2\n");
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        printf("SE at to_assign\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void to_assign(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("token v to assing %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //a,a
        to_assign2(parser_data);
    }else{
        printf("SE at to_assign\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void assign_existing(syntactic_data_t *parser_data){
    //sem uz prislo IDcko, som pred = 
    //SEMANTIC

    char *identificator = parser_data->token.token_info.custom_string->string_value;
    parser_data->current_item_var = search_item(&parser_data->local_table, identificator);
    if(parser_data->current_item_var == NULL){    //snaha o priradenie do needeklarovanej premennej
        custom_string_free_memory(&parser_data->my_string);
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    }

    //END SEMANTIC
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("token v assign_existing %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){   // a,  
        to_assign(parser_data);       
    }else if(parser_data->token.type_of_token==TYPE_ASSIGN){ // a=
        assign_value(parser_data);  
    }else{
        printf("SE at assign_existing\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void while_nt(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("Token vo while %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
    parser_data->token.type_of_token==TYPE_KW_NUMBER || 
    parser_data->token.type_of_token==TYPE_KW_STRING || 
    parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //vchadzam do statemenetu
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
        //IF BOTOOM UP OK
        check_retuned_tokens_from_expression_analysis(parser_data); //dat doprec lebo semanticka vrati jeden token v tej structe
        if(parser_data->token.type_of_token==TYPE_KW_DO){
            parser_data->in_while=true;
            printf("Z while idem do code\n");
            check_retuned_tokens_from_expression_analysis(parser_data);
            code(parser_data);
        }else{
            printf("Syntax error in while\n");
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        printf("Syntax error in while\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void code_if_nt(syntactic_data_t *parser_data){
    printf("Do code_if_nt som prisiel s tokenom %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_KW_ELSE){ //if statement je prazdny, po else nasleduju dalsie prikazy
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }else{ //vo vetve if sa nachadza kod
        //check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
}

void if_nt(syntactic_data_t *parser_data){
     check_retuned_tokens_from_expression_analysis(parser_data);
     printf("Token v if_nt %d\n", parser_data->token.type_of_token);
     if(parser_data->token.type_of_token==TYPE_INT_NUMBER || 
        parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
        parser_data->token.type_of_token==TYPE_STRING ||
        parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
        //IF BOTTOM UP OK
        //precedence_analysis(parser_data);
        check_retuned_tokens_from_expression_analysis(parser_data);

        printf("Token v if_nt %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_KW_THEN){
            parser_data->in_if=true;
            check_retuned_tokens_from_expression_analysis(parser_data);
            code_if_nt(parser_data);
        }
    }
}


void double_dots_nt(syntactic_data_t *parser_data){
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
         check_retuned_tokens_from_expression_analysis(parser_data);
         //printf("dalsi tokenik is : %d \n",parser_data->token.type_of_token);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
             //printf("Daco\n");
             parser_data->parameter_index++; //prijaty dalsi navratovy typ

             // Semantic
/* TODO      if(*get_is_declared(&parser_data->global_table, parser_data->current_item->key)==false && parser_data->in_declaration==true){
                  insert_function_return_type(&parser_data->global_table,parser_data->current_item,parser_data->token.type_of_token);
             }else{ //ak je doeklarovana
                if(parser_data->token.type_of_token != parser_data->current_item->data.list_of_return_types->items[parser_data->parameter_index]){
                    custom_string_free_memory(&parser_data->my_string);
                    process_error(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN);
                }
             }  
        */
//SAME ako v double_dot, ale kontrolujes dalsi parameter rekurzivne
//global f : function (integer) : integer, INTEGER
//function f(x : integer) : integer, INTEGER                       
             double_dots_nt(parser_data);
           

         }else{
             custom_string_free_memory(&parser_data->my_string);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
        
         
    //navrat pre deklaraciu funkcie   
    }else if(parser_data->token.type_of_token==TYPE_KW_FUNCTION && !parser_data->in_function){
        //check_declaration(parser_data);
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_GLOBAL && !parser_data->in_function){
        //check_declaration(parser_data);
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && !parser_data->in_function){
        //printf("Tu by som sa mal vracat\n");
        //check_declaration(parser_data);
        start(parser_data);    
    }else if(parser_data->token.type_of_token==TYPE_KW_EOF && !parser_data->in_function){
        //check_declaration(parser_data);
        start(parser_data);
        return;
    //navrat pre definiciu funkcie
    }else if(parser_data->token.type_of_token==TYPE_KW_WHILE && parser_data->in_function){
        //parser_data->in_function=false;
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_IF && parser_data->in_function){
        //parser_data->in_function=false;
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && parser_data->in_function){
        //parser_data->in_function=false;
        //printf("NAPATE\n");
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_RETURN && parser_data->in_function){
        //parser_data->in_function=false;
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE && parser_data->in_function){
        //parser_data->in_function=false;
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_LOCAL && parser_data->in_function){
        //parser_data->in_function=false;
        //check_declaration(parser_data);
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function){ //funkcia bez navratovych hodnot
        //check_declaration(parser_data);
        check_retuned_tokens_from_expression_analysis(parser_data);
        start(parser_data);
    }else{
        //epsilon pravidla
        //printf("mam tuna token: %d\n", parser_data->token.type_of_token);
        //printf("tu som spadol\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }     
}


void double_dot_nt(syntactic_data_t *parser_data){

    parser_data->parameter_index=-1; //zatial funkcia nema ziadne navratove tyzy
    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("\ndouble dot nt token %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COLON){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
            parser_data->parameter_index=0; //funkcia ma prvy navratovy typ
            //semantic
            //printf("dadadadad\n");
/* TODO
            if(*get_is_declared(&parser_data->global_table, parser_data->current_item->key)==false && parser_data->in_declaration==true){
                 insert_function_return_type(&parser_data->global_table,parser_data->current_item,parser_data->token.type_of_token);
            }else{  
                if(parser_data->token.type_of_token != parser_data->current_item->data.list_of_return_types->items[parser_data->parameter_index]){
                    custom_string_free_memory(&parser_data->my_string);
                    printf("TUZHADNUJE<");
                    process_error(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN);
                }
            }
*/
//KONTROLA prvého return parametru funkcie //asi fix
//RETURN parameter deklarovanej funkcie musi byt zhondy s return parametrom definovanej funkcie
//global f : function (integer) : INTEGER, integer
//function f(x : integer) : INTEGER, integer

            // Generate
            //printf("dadadadad\n");
            double_dots_nt(parser_data);
        }
    }else if(!parser_data->in_function){
        start(parser_data);
        return;
    }else if(parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }
    //epsilon pravidla
    custom_string_free_memory(&parser_data->my_string);
    process_error(SYNTAX_ANALYSIS_FAIL);
}


void params_nt(syntactic_data_t *parser_data){
    //semantic kontrola
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_COMMA){
         check_retuned_tokens_from_expression_analysis(parser_data);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
            parser_data->parameter_index++;
            //semantic
            insert_function_parameter(&parser_data->global_table,parser_data->current_item, parser_data->token.type_of_token);
            // Generation
            params_nt(parser_data);
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
        printf("\njedna\n");
        return; //koniec parametrov funkcie
    }else{
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
    //printf("Syntax error\n");
}


void param_nt(syntactic_data_t *parser_data){
    parser_data->parameter_index=-1; //ked vchadzam do parametrov funkcie, prvotne predpokladam ze ziadny parameter nema
    check_retuned_tokens_from_expression_analysis(parser_data);
     if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
         parser_data->parameter_index=0; //funkcia ma jeden parameter
         //printf("\nidem do params nt\n");

        // SEMANTIC
        insert_function_parameter(&parser_data->global_table,parser_data->current_item, parser_data->token.type_of_token);
        printf("nazov strukuty je : %s typ parametra je : %d\n",parser_data->current_item->data.identificator ,parser_data->current_item->data.list_of_parameters->items[0]);
         params_nt(parser_data);
     }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
         //printf("\nfunkcia nema parametre\n");
         return; //funkcia ziadne paramterne nema
     }else{
         custom_string_free_memory(&parser_data->my_string);
         process_error(SYNTAX_ANALYSIS_FAIL);
     }
}


void function_declaration(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("Token at function declaration %d\n", parser_data->token.type_of_token);

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){


        // SEMANTIC

        char *identificator = parser_data->token.token_info.custom_string->string_value;

        //redelkaracia
        if(search_item(&parser_data->global_table,identificator) != NULL){
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }

        parser_data->current_item = insert_symbol_function(&parser_data->global_table,identificator);
        
        //set_additional_info(&parser_data->global_table, parser_data->current_item, IS_DECLARED);
        //set_symbol_variable_type(&parser_data->global_table, parser_data->current_item,TYPE_IDENTIFICATOR_FUNCTION);


        // END SEMANTIC
        check_retuned_tokens_from_expression_analysis(parser_data);
        //printf("Token at function declaration %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_COLON){
            check_retuned_tokens_from_expression_analysis(parser_data);
            //printf("Token at function declaration %d\n", parser_data->token.type_of_token);
            if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){
                check_retuned_tokens_from_expression_analysis(parser_data);
                //printf("Token at function declaration %d\n", parser_data->token.type_of_token);
                if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
                    //printf("function_declaration: idem do param_nt\n");
                    param_nt(parser_data); //parametre funkcie
                    
                   // printf("\nostal mi token: %d\n", parser_data->token.type_of_token);
                   // printf("\nVynoril som sa\n");
                    //printf("FUNKCIA MA %d parametrov +1\n",parser_data->parameter_index);

                    double_dot_nt(parser_data); //navratove hodnoty funkcie
                }
            }
        }
    }
    printf("SE at function declaration \n");
    custom_string_free_memory(&parser_data->my_string);
    process_error(SYNTAX_ANALYSIS_FAIL);
}

void call_params(syntactic_data_t *parser_data){
    parser_data->parameter_index++; //funkcia ma dalsi paramter (ziadny parameter je -1, jeden paramter je 0, ...)
    //printf("CALL PARAMS\n");
    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("Tokenik is : %d \n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        check_retuned_tokens_from_expression_analysis(parser_data);
        printf("dalsi tokenik is : %d \n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
        parser_data->token.type_of_token==TYPE_INT_NUMBER ||
        parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
        parser_data->token.type_of_token==TYPE_STRING)
        {
            call_params(parser_data);
        }else{
            printf("SE AT call_params\n");
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL); 
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia ma len jeden parameter
        printf("SKACEM Z CALL PARAMS NA START\n");
        //check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->in_function==true){
             check_retuned_tokens_from_expression_analysis(parser_data);
            code(parser_data);
        }else
            start(parser_data);
    }else{
        printf("SE AT call_params DOWN\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL); 
    }
}

void call_param(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    printf("Call params po generovani tokenu: %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
       parser_data->token.type_of_token==TYPE_KW_INTEGER ||
       parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
       parser_data->token.type_of_token==TYPE_STRING){
        call_params(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema parametre
       printf("Sem by som mal prist \n");
       check_retuned_tokens_from_expression_analysis(parser_data);
       if(parser_data->in_while==true){
           code(parser_data);
       }else{
           start(parser_data); 
       }
    }else{
        printf("SE AT call_param\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}


void function_call(syntactic_data_t *parser_data){

    //check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        char *identificator = parser_data->token.token_info.custom_string->string_value;
        parser_data->current_item=search_item(&parser_data->global_table, identificator);
        if(parser_data->current_item==NULL){
            custom_string_free_memory(&parser_data->my_string);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        if(*get_is_defined(&parser_data->global_table, parser_data->current_item->key)==false){
            custom_string_free_memory(&parser_data->my_string);
            printf("MAROS");
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
            parser_data->parameter_index=-1; //na zaciatku nema funkcia ziadny parameter
            call_param(parser_data);
            //start(parser_data);
        }else{
           custom_string_free_memory(&parser_data->my_string);
           process_error(SYNTAX_ANALYSIS_FAIL);
        }   
    }
}


void argument(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("token v argumente %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){ //funkcia ma viac parametrov
         check_retuned_tokens_from_expression_analysis(parser_data);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
            //printf("Anna_foj\n");
             //SEmantic
             char *identificator = parser_data->token.token_info.custom_string->string_value;
             if(search_item(&parser_data->local_table,identificator)!=NULL){
                 process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
             }

             parser_data->current_item_var = insert_symbol_variable(&parser_data->local_table,identificator);
             //printf("item name is :%s \n",parser_data->current_item_var->data.identificator);

             check_retuned_tokens_from_expression_analysis(parser_data);
             if(parser_data->token.type_of_token==TYPE_COLON){ //nasleduje dalsi parameter
                 check_retuned_tokens_from_expression_analysis(parser_data);
                 if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
                    parser_data->token.type_of_token==TYPE_KW_STRING || 
                    parser_data->token.type_of_token==TYPE_KW_NUMBER){
//PARAMETRE DEKLAROVANEJ FUNKCIE MUSIA BYT ZHODNE S PARAMETRAMI DEFINOVANEJ FUNKCIE
                    //v TS sa najde definovana funkcia podla ID
                    if(*get_is_declared(&parser_data->global_table, parser_data->current_item->key)==true){

                        if(parser_data->token.type_of_token != parser_data->current_item->data.list_of_parameters->items[parser_data->parameter_index]){
                            custom_string_free_memory(&parser_data->my_string);
                            process_error(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN);
                        }else{
                            parser_data->parameter_index++;
                        }
                    }
                    //Postupne sa rekurzivne kontroluju jej parametre
                    
                    //prvy s prvym, druhy s druhym,...    
                    //global f : function (INTEGER) : integer, integer // Poriesene
                    //function f(x : INTEGER) : integer, integer
            
                    //Semantic
                    set_symbol_variable_type(&parser_data->local_table,parser_data->current_item_var,parser_data->token.type_of_token);
                    argument(parser_data); //prijal som cely parameter, idem kontrolovat, ci neprisiel dalsi
                 }
             }else{
                //printf("SE argument\n");
                custom_string_free_memory(&parser_data->my_string);
                process_error(SYNTAX_ANALYSIS_FAIL);
             } 
         }else{
             //printf("SE argument\n");
             custom_string_free_memory(&parser_data->my_string);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //ziadny dalsi parameter nie je
        parser_data->in_function=true;
        //printf("argument: idem do doubledotnt\n");
        double_dot_nt(parser_data); //idem kontrolovat navratove hodnoty
    }else{
        //printf("SE argument dole\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void arg(syntactic_data_t *parser_data){
    //Semantic

    //SEmantic
    char *identificator = parser_data->token.token_info.custom_string->string_value;
    if(search_item(&parser_data->local_table,identificator)!=NULL){
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    }

    parser_data->current_item_var = insert_symbol_variable(&parser_data->local_table,identificator);
    printf("item name is :%s \n",parser_data->current_item_var->data.identificator);

    check_retuned_tokens_from_expression_analysis(parser_data);
    //printf("Token v arg %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COLON){
        check_retuned_tokens_from_expression_analysis(parser_data);
        //printf("Token v arg nizsie %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
            parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token == TYPE_KW_STRING){
            //printf("arg: idem do argumentu\n");
            //Semantic
            set_symbol_variable_type(&parser_data->local_table,parser_data->current_item_var,parser_data->token.type_of_token);
            printf("BASHKA is here %s\n",parser_data->current_item->data.identificator);


            if (*get_is_declared(&parser_data->global_table,parser_data->current_item->key) == true){
                printf("param index : %d\n",parser_data->parameter_index);
                if(parser_data->token.type_of_token != parser_data->current_item->data.list_of_parameters->items[parser_data->parameter_index]){
                    custom_string_free_memory(&parser_data->my_string);
                    process_error(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN);
                }else{
                    parser_data->parameter_index++;
                }
           }
           
            printf("BASHKA HAH,\n");
            
    
            //printf("data : %d\n",parser_data->current_item->data.symbol_variable_type);
           // printf("name : %s\n",parser_data->current_item->key);

            argument(parser_data);
        }else{
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        //printf("SE at arg");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
    //printf("END arg\n");
}

void function(syntactic_data_t *parser_data){

    //SEMANTIC
    char *identificator = parser_data->token.token_info.custom_string->string_value;
    printf("identific : %s\n",identificator);

//TEST DEKLARACIE FUNKCIE //asi fix
    
    /* if(search_item(&parser_data->global_table,identificator)==NULL){
        custom_string_free_memory(&parser_data->my_string); 
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    } */

    if(search_item(&parser_data->global_table,identificator) != NULL){
        if(*get_is_defined(&parser_data->global_table,identificator) == true){ //test redefinicie
        custom_string_free_memory(&parser_data->my_string); 
        printf("Daj pred to vypis\n");
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        parser_data->current_item = search_item(&parser_data->global_table,identificator);
    }else{
        parser_data->current_item = insert_symbol_function(&parser_data->global_table,identificator);
    }
    
    set_is_defined(&parser_data->global_table, parser_data->current_item,true);
    printf("current item %s\n",parser_data->current_item->data.identificator);
    //set_symbol_variable_type(&parser_data->global_table, parser_data->current_item,TYPE_IDENTIFICATOR_FUNCTION);

     check_retuned_tokens_from_expression_analysis(parser_data);
     //printf("token v function: %d\n", parser_data->token.type_of_token);
     if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
         check_retuned_tokens_from_expression_analysis(parser_data);
         //printf("token v function nizsie: %d\n", parser_data->token.type_of_token);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //funckia ma aspon jeden parameter
            //printf("function: idem do arg\n");
            //Semantic
            arg(parser_data);

         }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema ziadne parametre
            parser_data->in_function=true;
            //check_retuned_tokens_from_expression_analysis(parser_data);
            double_dot_nt(parser_data);
         }else{
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
         }
     }else{
          custom_string_free_memory(&parser_data->my_string);
          process_error(SYNTAX_ANALYSIS_FAIL);
     }
     printf("END function\n");
}

void check_ret_prarams(syntactic_data_t *parser_data){
    //sem mi pride ID, ktore je v returne
    parser_data->parameter_index++; //kazdy dalsi prijaty parameter
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_COMMA){ //funkcia ma viacero navratovych hodnot
       check_retuned_tokens_from_expression_analysis(parser_data);  
       if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE ||  //fixed variables
         parser_data->token.type_of_token==TYPE_INT_NUMBER || 
         parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
         parser_data->token.type_of_token==TYPE_STRING){
           check_ret_prarams(parser_data);
       }
    }if(parser_data->token.type_of_token==TYPE_KW_END){
        //parser_data->in_function=false; //vyloiezol som z funkcie, nastavuje sa v starte aby som neskipol podmienku
        //check_retuned_tokens_from_expression_analysis(parser_data); //na starte bude novy token
        start(parser_data); //nemoze byt funkcia vo funkcii, idem od znova
    }else{
        printf("SE at check ret params\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void return_nt(syntactic_data_t *parser_data){
    //sem mi pride <KW_RETRUN>
    parser_data->parameter_index=-1; //zatial je funkcia bez parametrov
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        check_ret_prarams(parser_data);
    }else{
        code(parser_data); //ak nema navratove hodnoty, pokracuje code
    }
}

void code(syntactic_data_t *parser_data){
    printf("dostal som sa do code s tokenom %d\n", parser_data->token.type_of_token);
    printf("v code in_function %d\n", parser_data->in_function);
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true && parser_data->in_if == false){
       parser_data->in_function=false;
       check_retuned_tokens_from_expression_analysis(parser_data);
       if(parser_data->token.type_of_token!=TYPE_KW_EOF){
           start(parser_data);
       }else{
           code(parser_data);
       }
    }
    
    if(parser_data->token.type_of_token==TYPE_KW_WHILE){
        printf("z code sa vola while\n");
        while_nt(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_IF){
        printf("z code sa vola if_nt\n");
        if_nt(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        printf("z code sa vola functioncall\n");
        function_call(parser_data);
    }  
    if(parser_data->token.type_of_token==TYPE_KW_RETURN && parser_data->in_function==true){
        return_nt(parser_data);
        //if in function and function has parameters
        //generate and call start 
    }
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        printf("z code sa vola assign_existing\n");
        assign_existing(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_LOCAL){
        printf("z code sa vola assign_new\n");
        assign_new(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_while==true && parser_data->in_function==true){
        parser_data->in_while=false;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
        //printf("\nSyntax ok code\n");
        //custom_string_free_memory(&parser_data->my_string);
        // exit(0);
    }
    if(parser_data->token.type_of_token==TYPE_KW_ELSE && parser_data->in_if==true){
        //EPS
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_if==true){
        parser_data->in_if=false;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==false){
        check_retuned_tokens_from_expression_analysis(parser_data);
        start(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true){
        //start(parser_data);
        parser_data->in_function=false;
        printf("\nSyntax ok code\n");
        custom_string_free_memory(&parser_data->my_string);
        exit(0);
    }  
}


void start(syntactic_data_t *parser_data){
    //check_retuned_tokens_from_expression_analysis(parser_data);
    printf("TOKEN NA STARTE %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        function_call(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){              //deklaracia funkcie
        printf("Start: idem do fucntion_declaration\n");
        parser_data->in_declaration=true;
        function_declaration(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
            printf("start: volam func_nt\n");
            table_dispose(&parser_data->local_table);
            function(parser_data);
        }
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true){
        parser_data->in_function=false;
        check_retuned_tokens_from_expression_analysis(parser_data);
        start(parser_data);
    } 
    if(parser_data->token.type_of_token==TYPE_KW_EOF){
        printf("\nSyntax ok\n");

        table_item_t item_s;
        table_item_t *item = &item_s;
        
        item = search_item(&parser_data->local_table,"x");

        printf("function name : %s \n",item->data.identificator);
        

        printf("get data type of x : %d\n",item->data.symbol_variable_type);

        /* item = search_item(&parser_data->global_table,"foo");

        printf("function name : %s \n",get_identificator(&parser_data->global_table,"foo"));
        
        printf("parameters :");
        for (int i = 0; i < item->data.list_of_parameters->items_count; i++){
            printf(" %d",item->data.list_of_parameters->items[i]);
        }
        printf("\n"); */

        /* item = search_item(&parser_data->global_table,"a");

        printf("function name : %s \n",get_identificator(&parser_data->global_table,"a"));
        
        printf("parameters :");
        for (int i = 0; i < item->data.list_of_parameters->items_count; i++){
            printf(" %d",item->data.list_of_parameters->items[i]);
        }
        printf("\n");


        //RET TYPES
        item = search_item(&parser_data->global_table,"g");

        printf("function name : %s \n",get_identificator(&parser_data->global_table,"g"));
        
        printf("ret types :");
        for (int i = 0; i < item->data.list_of_return_types->items_count; i++){
            printf(" %d",item->data.list_of_return_types->items[i]);
        }
        printf("\n");

        item = search_item(&parser_data->global_table,"foo");

        printf("function name : %s \n",get_identificator(&parser_data->global_table,"foo"));
        
        printf("ret types :");
        for (int i = 0; i < item->data.list_of_return_types->items_count; i++){
            printf(" %d",item->data.list_of_return_types->items[i]);
        }
        printf("\n");

        item = search_item(&parser_data->global_table,"a");

        printf("function name : %s \n",get_identificator(&parser_data->global_table,"a"));
        
        printf("ret types :");
        for (int i = 0; i < item->data.list_of_return_types->items_count; i++){
            printf(" %d",item->data.list_of_return_types->items[i]);
        } */
        printf("\n");


        custom_string_free_memory(&parser_data->my_string);
        table_dispose(&parser_data->global_table);
        table_dispose(&parser_data->local_table);

        /* token_list_insertfirst(&parser_data->list_of_tokens,parser_data->token);
        parser_data->list_of_tokens.activeElement = parser_data->list_of_tokens.firstElement; */

        exit(0);
    }
    printf("\nSE AT START\n");
    process_error(SYNTAX_ANALYSIS_FAIL);
}


void parser_data_init(syntactic_data_t *data){
    data->in_function=false;
    data->in_if=false;
    data->in_declaration=false;
    data->parameter_index=-1;
    token_list_init(&data->list_of_tokens);
}

void check_retuned_tokens_from_expression_analysis(syntactic_data_t *parser_data){
    if(parser_data->list_of_tokens.activeElement != NULL){
        parser_data->token = parser_data->list_of_tokens.activeElement->token;
        parser_data->list_of_tokens.activeElement = parser_data->list_of_tokens.activeElement->nextElement;
    }else{
        generate_token(&parser_data->token, &parser_data->my_string);
    }
    
}

void analyze(){
    syntactic_data_t parser_data;
    parser_data_init(&parser_data);
    //defaultne je parameter index na -1
    //parser_data.in_while=false; toto by tu malo byt ale ked to tam je tak sa to rozdrbe tak radsej nak to tam nie je xD

    custom_string_init(&parser_data.my_string);
    
    //inicializacia tabulky symbolov
    table_init(&parser_data.global_table);
    table_init(&parser_data.local_table);

    generate_token(&parser_data.token, &parser_data.my_string);

    printf("prvy vygenervany token %d \n", parser_data.token.type_of_token);
    if(parser_data.token.type_of_token==TYPE_KW_REQUIRE){
      generate_token(&parser_data.token, &parser_data.my_string);
      printf("druhy vygenervany token %d \n", parser_data.token.type_of_token);
        if(parser_data.token.type_of_token==TYPE_STRING){ 
            genertaor_start(&parser_data);
            generate_token(&parser_data.token, &parser_data.my_string);
            start(&parser_data); 
        }
    }

    custom_string_free_memory(&parser_data.my_string);

    //printf("Syntax error\n");
    //exit;
}