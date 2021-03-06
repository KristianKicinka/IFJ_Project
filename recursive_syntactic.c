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

void optional_ekv(syntactic_data_t *parser_data){
    //sem pridem s KW_ASSIGN <=>
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){      //LOCAL A : = foo()
        function_call(parser_data);

    }else if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET || 
             parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE ||
             parser_data->token.type_of_token==TYPE_INT_NUMBER ||
             parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
             parser_data->token.type_of_token==TYPE_KW_NIL){          //LOCAL A : = a||2
             //BOTTOM-UP
             precedence_analysis(parser_data);
             check_retuned_tokens_from_expression_analysis(parser_data);
             code(parser_data); //moze byt deklarovana a zaroven inicializovana iba jedna hodnota, po uspesnej precedencnej idem spat do kodu a cakam, co je dalsie
    }else{
        jonwick_the_memory_cleaner(parser_data);
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
            jonwick_the_memory_cleaner(parser_data);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        parser_data->current_item_var =  insert_symbol_variable(&parser_data->local_table, identificator);
        set_is_declared(&parser_data->local_table, parser_data->current_item_var, true);
        //END SEMANTIC

        create_declaration_variable(identificator);

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
                    optional_ekv(parser_data);
                }else{                          //iny vstup ako <=> znamena iba deklraraciu bez inicializacie
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

    if(parser_data->token.type_of_token==TYPE_COMMA){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
           parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION ||
           parser_data->token.type_of_token==TYPE_INT_NUMBER ||
           parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER){ // ...=a,b || ...=foo(), bar() || ...=2,3
            //BOTTOM UP
            precedence_analysis(parser_data);
            assign_values(parser_data);
        }else{;
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        code(parser_data);
    }
}

void assign_value(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
       parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION || 
       parser_data->token.type_of_token==TYPE_INT_NUMBER ||
       parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
       parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET ||
       parser_data->token.type_of_token==TYPE_STRING){ // ...=a || ...=foo() || ...=2
        //BOTTOM UP
        precedence_analysis(parser_data);
        assign_values(parser_data);
    }else{
        jonwick_the_memory_cleaner(parser_data);
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
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
    //END SEMANTIC
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_ASSIGN){
        assign_value(parser_data); // a,a=
    }else if(parser_data->token.type_of_token==TYPE_COMMA){ //a,a,
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //a,a,a
            to_assign2(parser_data);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void to_assign(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //a,a
        to_assign2(parser_data);
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void assign_existing(syntactic_data_t *parser_data){
    //sem uz prislo IDcko, som pred = 
    //SEMANTIC

    char *identificator = parser_data->token.token_info.custom_string->string_value;
    parser_data->current_item_var = search_item(&parser_data->local_table, identificator);
    if(parser_data->current_item_var == NULL){    //snaha o priradenie do needeklarovanej premennej
        jonwick_the_memory_cleaner(parser_data);
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    }

    //END SEMANTIC
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_COMMA){   // a,  
        to_assign(parser_data);       
    }else if(parser_data->token.type_of_token==TYPE_ASSIGN){ // a=
        assign_value(parser_data);  
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void while_nt(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
    parser_data->token.type_of_token==TYPE_KW_NUMBER || 
    parser_data->token.type_of_token==TYPE_KW_STRING || 
    parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //vchadzam do statemenetu
        //BOTTOM UP
        precedence_analysis(parser_data);
        check_retuned_tokens_from_expression_analysis(parser_data); //dat doprec lebo semanticka vrati jeden token v tej structe
       
        if(parser_data->token.type_of_token==TYPE_KW_DO){
            parser_data->in_while=true;
            
            check_retuned_tokens_from_expression_analysis(parser_data);
            code(parser_data);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void code_if_nt(syntactic_data_t *parser_data){
 
    create_if_start(parser_data->statement_index);
    if(parser_data->token.type_of_token==TYPE_KW_ELSE){ //if statement je prazdny, po else nasleduju dalsie prikazy
        parser_data->nof_else++;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }else{ //vo vetve if sa nachadza kod
 
        code(parser_data);
    }
}

void if_nt(syntactic_data_t *parser_data){
    parser_data->statement_index++;
     check_retuned_tokens_from_expression_analysis(parser_data);
    
     if(parser_data->token.type_of_token==TYPE_INT_NUMBER || 
        parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER ||
        parser_data->token.type_of_token==TYPE_STRING ||
        parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        //BOTTOM UP
        precedence_analysis(parser_data);
        check_retuned_tokens_from_expression_analysis(parser_data);

        if(parser_data->token.type_of_token==TYPE_KW_THEN){
            parser_data->nof_if++;
            parser_data->in_if=true;  
                  
            check_retuned_tokens_from_expression_analysis(parser_data);
            code_if_nt(parser_data);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }
}


void double_dots_nt(syntactic_data_t *parser_data){
   
    check_retuned_tokens_from_expression_analysis(parser_data);
 
    if(parser_data->token.type_of_token==TYPE_COMMA){
         check_retuned_tokens_from_expression_analysis(parser_data);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
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
            create_function_return(parser_data->parameter_index,parser_data->token.token_info.custom_string->string_value);
            double_dots_nt(parser_data);
         }else{
             jonwick_the_memory_cleaner(parser_data);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
         
    }else if(parser_data->token.type_of_token==TYPE_KW_FUNCTION && !parser_data->in_function){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_GLOBAL && !parser_data->in_function){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && !parser_data->in_function){
        start(parser_data);    
    }else if(parser_data->token.type_of_token==TYPE_KW_EOF && !parser_data->in_function){
        start(parser_data);
        return;
    }else if(parser_data->token.type_of_token==TYPE_KW_WHILE && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_IF && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_RETURN && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_LOCAL && parser_data->in_function){
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function){ //funkcia bez navratovych hodnot
        check_retuned_tokens_from_expression_analysis(parser_data);
        start(parser_data);
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }     
}


void double_dot_nt(syntactic_data_t *parser_data){

    parser_data->parameter_index=-1; //zatial funkcia nema ziadne navratove tyzy
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_COLON){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
            parser_data->parameter_index=0; //funkcia ma prvy navratovy typ
            //semantic
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
            create_function_return(parser_data->parameter_index, parser_data->token.token_info.custom_string->string_value);
            double_dots_nt(parser_data);
        }
    }else if(!parser_data->in_function){
        start(parser_data);
        return;
    }else if(parser_data->in_function){
        code(parser_data);
    }
    jonwick_the_memory_cleaner(parser_data);
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
        return; //koniec parametrov funkcie
    }else{
        jonwick_the_memory_cleaner(parser_data);;
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}


void param_nt(syntactic_data_t *parser_data){
    parser_data->parameter_index=-1; //ked vchadzam do parametrov funkcie, prvotne predpokladam ze ziadny parameter nema
    check_retuned_tokens_from_expression_analysis(parser_data);
     if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
         parser_data->parameter_index=0; //funkcia ma jeden parameter

        // SEMANTIC
        insert_function_parameter(&parser_data->global_table,parser_data->current_item, parser_data->token.type_of_token);
         params_nt(parser_data);
     }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
         return; //funkcia ziadne paramterne nema
     }else{
         jonwick_the_memory_cleaner(parser_data);
         process_error(SYNTAX_ANALYSIS_FAIL);
     }
}


void function_declaration(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){

        // SEMANTIC
        char *identificator = parser_data->token.token_info.custom_string->string_value;
        //redelkaracia
        if(search_item(&parser_data->global_table,identificator) != NULL){
            jonwick_the_memory_cleaner(parser_data);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }

        parser_data->current_item = insert_symbol_function(&parser_data->global_table,identificator);
        
        //set_additional_info(&parser_data->global_table, parser_data->current_item, IS_DECLARED);
        //set_symbol_variable_type(&parser_data->global_table, parser_data->current_item,TYPE_IDENTIFICATOR_FUNCTION);

        // END SEMANTIC

        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_COLON){
            check_retuned_tokens_from_expression_analysis(parser_data);
            if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){
                check_retuned_tokens_from_expression_analysis(parser_data);
                if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
                    param_nt(parser_data); //parametre funkcie
                    double_dot_nt(parser_data); //navratove hodnoty funkcie
                }
            }
        }
    }
    jonwick_the_memory_cleaner(parser_data);
    process_error(SYNTAX_ANALYSIS_FAIL);
}

void call_params(syntactic_data_t *parser_data){
    parser_data->parameter_index++; //funkcia ma dalsi paramter (ziadny parameter je -1, jeden paramter je 0, ...)
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
        parser_data->token.type_of_token==TYPE_INT_NUMBER ||
        parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
        parser_data->token.type_of_token==TYPE_STRING)
        {
            call_params(parser_data);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL); 
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia ma len jeden parameter
         if(parser_data->in_function==true){
            check_retuned_tokens_from_expression_analysis(parser_data);
            code(parser_data);
        }else
            start(parser_data);
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL); 
    }
}

void call_param(syntactic_data_t *parser_data){

    check_retuned_tokens_from_expression_analysis(parser_data);

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
       parser_data->token.type_of_token==TYPE_KW_INTEGER ||
       parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
       parser_data->token.type_of_token==TYPE_STRING){
        call_params(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema parametre
       check_retuned_tokens_from_expression_analysis(parser_data);
       if(parser_data->in_function==true){
           code(parser_data);
       }else{
           start(parser_data); 
       }
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}


void function_call(syntactic_data_t *parser_data){
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        char *identificator = parser_data->token.token_info.custom_string->string_value;
       
        parser_data->current_item=search_item(&parser_data->global_table, identificator);
         
        create_function_call(identificator);    
        if(parser_data->current_item==NULL){
            jonwick_the_memory_cleaner(parser_data);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        if(*get_is_defined(&parser_data->global_table, parser_data->current_item->key)==false){
            jonwick_the_memory_cleaner(parser_data);
            process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        check_retuned_tokens_from_expression_analysis(parser_data); 
        if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
            parser_data->parameter_index=-1; //na zaciatku nema funkcia ziadny parameter
            call_param(parser_data);
            //start(parser_data);
        }else{
           jonwick_the_memory_cleaner(parser_data);
           process_error(SYNTAX_ANALYSIS_FAIL);
        }   
    }
}


void argument(syntactic_data_t *parser_data){
    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_COMMA){ //funkcia ma viac parametrov
         check_retuned_tokens_from_expression_analysis(parser_data);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
             parser_data->parameter_index++;
             //SEmantic
             char *identificator = parser_data->token.token_info.custom_string->string_value;
             if(search_item(&parser_data->local_table,identificator)!=NULL){
                 jonwick_the_memory_cleaner(parser_data);
                 process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
             }
             parser_data->current_item_var = insert_symbol_variable(&parser_data->local_table,identificator);

            create_function_parameter(parser_data->parameter_index, identificator);

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
                            jonwick_the_memory_cleaner(parser_data);
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
                jonwick_the_memory_cleaner(parser_data);
                process_error(SYNTAX_ANALYSIS_FAIL);
             } 
         }else{
             jonwick_the_memory_cleaner(parser_data);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //ziadny dalsi parameter nie je
        parser_data->in_function=true;
        double_dot_nt(parser_data); //idem kontrolovat navratove hodnoty
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void arg(syntactic_data_t *parser_data){
    //Semantic

    //SEmantic
    char *identificator = parser_data->token.token_info.custom_string->string_value;
    if(search_item(&parser_data->local_table,identificator)!=NULL){
        jonwick_the_memory_cleaner(parser_data);
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    }

    parser_data->current_item_var = insert_symbol_variable(&parser_data->local_table,identificator);

    create_function_parameter(parser_data->parameter_index, identificator);

    check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_COLON){
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
            parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token == TYPE_KW_STRING){
            //Semantic
            set_symbol_variable_type(&parser_data->local_table,parser_data->current_item_var,parser_data->token.type_of_token);
            if (*get_is_declared(&parser_data->global_table,parser_data->current_item->key) == true){
                if(parser_data->token.type_of_token != parser_data->current_item->data.list_of_parameters->items[parser_data->parameter_index]){
                    jonwick_the_memory_cleaner(parser_data);
                    process_error(SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN);
                }else{
                    parser_data->parameter_index++;
                }
           }
            argument(parser_data);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        jonwick_the_memory_cleaner(parser_data);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void function(syntactic_data_t *parser_data){
    parser_data->parameter_index=-1;
    //SEMANTIC
    char *identificator = parser_data->token.token_info.custom_string->string_value;

    create_function_label(identificator);
    //TEST DEKLARACIE FUNKCIE //asi fix
    
    /* if(search_item(&parser_data->global_table,identificator)==NULL){
        custom_string_free_memory(&parser_data->my_string); 
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
    } */

    if(search_item(&parser_data->global_table,identificator) != NULL){
        if(*get_is_defined(&parser_data->global_table,identificator) == true){ //test redefinicie
        jonwick_the_memory_cleaner(parser_data);
        process_error(SEMANTIC_ANALYSIS_UNDEF_VAR);
        }
        parser_data->current_item = search_item(&parser_data->global_table,identificator);
    }else{
        parser_data->current_item = insert_symbol_function(&parser_data->global_table,identificator);
    }
    
    set_is_defined(&parser_data->global_table, parser_data->current_item,true);
    
    //set_symbol_variable_type(&parser_data->global_table, parser_data->current_item,TYPE_IDENTIFICATOR_FUNCTION);

     check_retuned_tokens_from_expression_analysis(parser_data);
    
     if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
         check_retuned_tokens_from_expression_analysis(parser_data);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //funckia ma aspon jeden parameter
            parser_data->parameter_index=0;
            arg(parser_data);

         }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema ziadne parametre
            parser_data->in_function=true;
            //check_retuned_tokens_from_expression_analysis(parser_data);
            //create_function_end(parser_data->current_item->data.identificator);
            double_dot_nt(parser_data);
         }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
         }
     }else{
          jonwick_the_memory_cleaner(parser_data);
          process_error(SYNTAX_ANALYSIS_FAIL);
     }
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
        jonwick_the_memory_cleaner(parser_data);
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
    if(parser_data->token.type_of_token==TYPE_KW_WHILE){
        while_nt(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_IF){
        if_nt(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        function_call(parser_data);
    }  
    if(parser_data->token.type_of_token==TYPE_KW_RETURN && parser_data->in_function==true){
        return_nt(parser_data);
        //if in function and function has parameters
        //generate and call start 
    }
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        assign_existing(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_LOCAL){
        assign_new(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_while==true){
        parser_data->in_while=false;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_ELSE && (parser_data->statement_index>0 || parser_data->in_if==true)){
        parser_data->nof_else++;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_if==true){
        parser_data->in_if=false;
        parser_data->statement_index--;
        check_retuned_tokens_from_expression_analysis(parser_data);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==false){
        check_retuned_tokens_from_expression_analysis(parser_data);
        start(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true && parser_data->in_if == false){
       parser_data->in_function=false;
       create_function_end(parser_data->current_item->data.identificator);
       check_retuned_tokens_from_expression_analysis(parser_data);
       if(parser_data->statement_index>0){
           code(parser_data);
       }if(parser_data->token.type_of_token!=TYPE_KW_EOF){
           start(parser_data);
       }else{
           code(parser_data);
       }
    }
}


void start(syntactic_data_t *parser_data){
    //check_retuned_tokens_from_expression_analysis(parser_data);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        function_call(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){              //deklaracia funkcie
        parser_data->in_declaration=true;
        function_declaration(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
        check_retuned_tokens_from_expression_analysis(parser_data);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
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
        if(parser_data->nof_else==parser_data->nof_if){
            jonwick_the_memory_cleaner(parser_data);

        /* token_list_insertfirst(&parser_data->list_of_tokens,parser_data->token);
        parser_data->list_of_tokens.activeElement = parser_data->list_of_tokens.firstElement; */
            generator_end();
            exit(0);
        }else{
            jonwick_the_memory_cleaner(parser_data);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
        
    }
    jonwick_the_memory_cleaner(parser_data);
    process_error(SYNTAX_ANALYSIS_FAIL);
}

void jonwick_the_memory_cleaner(syntactic_data_t *babajaga){
     custom_string_free_memory(&babajaga->my_string);
     table_dispose(&babajaga->global_table);
     table_dispose(&babajaga->local_table);
     token_list_dispose(&babajaga->list_of_tokens);
}

void parser_data_init(syntactic_data_t *data){
    data->in_function=false;
    data->in_if=false;
    data->in_declaration=false;
    data->in_while=false;
    data->parameter_index=-1;
    data->statement_index=0;
    data->nof_else=0;
    data->nof_if=0;
    token_list_init(&data->list_of_tokens);

    data->current_item = insert_symbol_function(&data->global_table, "read");
    set_is_defined(&data->global_table, data->current_item , true);
    data->current_item = insert_symbol_function(&data->global_table, "reads");
    set_is_defined(&data->global_table, data->current_item , true);
    data->current_item = insert_symbol_function(&data->global_table, "readi");
    set_is_defined(&data->global_table, data->current_item , true);
    data->current_item = insert_symbol_function(&data->global_table, "readn");
    set_is_defined(&data->global_table, data->current_item , true);
    data->current_item = insert_symbol_function(&data->global_table, "main");
    set_is_defined(&data->global_table, data->current_item, true);
    data->current_item = insert_symbol_function(&data->global_table, "write");
    set_is_defined(&data->global_table, data->current_item, true);
    data->current_item = NULL;
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

    custom_string_init(&parser_data.my_string);
    
    //inicializacia tabulky symbolov
    table_init(&parser_data.global_table);
    table_init(&parser_data.local_table);

    generate_token(&parser_data.token, &parser_data.my_string);

    if(parser_data.token.type_of_token==TYPE_KW_REQUIRE){
      generate_token(&parser_data.token, &parser_data.my_string);
        if(parser_data.token.type_of_token==TYPE_STRING){ 
            genertaor_start(&parser_data);
            generate_token(&parser_data.token, &parser_data.my_string);
            start(&parser_data); 
        }
    }
    jonwick_the_memory_cleaner(&parser_data);
    process_error(SYNTAX_ANALYSIS_FAIL);
}