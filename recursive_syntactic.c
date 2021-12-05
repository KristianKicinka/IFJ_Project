#include "recursive_syntactic.h"
/*
Token get_token(){
    Token term;
    Token *actualterm = &term; 

    return //generate_token(actualterm, get_custom_string());
}

Custom_string get_custom_string(){
    Custom_string my_string;
    Custom_string *my_str = &my_string; 
        
    return custom_string_init(my_str);
}
*/
/*
void code(){
    Token token;
    token=get_token();

    if(token.type_of_token==TYPE_KW_WHILE){ //vstupujem do while
        while_nt();
    }
    if(token.type_of_token==TYPE_KW_IF){    //vstupujem do if
        if_nt();
    }
    if(token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volam funkciu
        function_call(token);
    }
    if(token.type_of_token==TYPE_KW_RETURN){    //som na konci funkcie
        check_return_parameters();
    }
    if(token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){   //idem priradyovat do uz existujucej variable
        assign_existing(token);
    }
    if(token.type_of_token==TYPE_KW_LOCAL){ //vytvaram novu variable
        token=get_token();
        if(token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
            assign_new(token);
        }
    }
    if(token.type_of_token==TYPE_KW_ELSE || token.type_of_token=TYPE_KW_END){
        code();
    }
    printf("Syntax error\n");
    exit;
}

void while_nt(){
    Token token;
    token=get_token();
    if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
    }
    printf("Syntax error\n");
    exit;
}

void if_nt(){
     if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
    }
}
*/

void double_dots_nt(syntactic_data_t *parser_data){
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    generate_token(&parser_data->token, &parser_data->my_string);
   // printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        generate_token(&parser_data->token, &parser_data->my_string);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
             printf("Daco\n");
             double_dots_nt(parser_data);
         }else{
             process_error(SYNTAX_ANALYSIS_FAIL);
         }    
    }else if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        printf("Tu by som sa mal vracat\n");
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_EOF){
        start(parser_data);
        return;
    }    
    //epsilon pravidla
    printf("mam tuna token: %d\n", parser_data->token.type_of_token);
    printf("tu som spadol\n");
    process_error(SYNTAX_ANALYSIS_FAIL);
}


void double_dot_nt(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_COLON){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
            double_dots_nt(parser_data);
        }
    }else{
        start(parser_data);
        return;
    }
    //epsilon pravidla
    process_error(SYNTAX_ANALYSIS_FAIL);
}


void params_nt(syntactic_data_t *parser_data){
    //semantic kontrola
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_COMMA){
         generate_token(&parser_data->token, &parser_data->my_string);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
            params_nt(parser_data);
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
        printf("\njedna\n");
        return; //koniec parametrov funkcie
    }
    printf("Syntax error\n");
}


void param_nt(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
     if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
         printf("\nidem do params nt\n");
         params_nt(parser_data);
     }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
         printf("\nfunkcia nema parametre\n");
         return; //funkcia ziadne paramterne nema
     }else{
         process_error(SYNTAX_ANALYSIS_FAIL);
     }
}


void function_declaration(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_COLON){
            generate_token(&parser_data->token, &parser_data->my_string);
            if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){
                generate_token(&parser_data->token, &parser_data->my_string);
                if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
                    param_nt(parser_data); //parametre funkcie
                    
                    printf("\nostal mi token: %d\n", parser_data->token.type_of_token);
                    printf("\nVynoril som sa\n");

                    double_dot_nt(parser_data); //navratove hodnoty funkcie
                }
            }
        }
    }
    process_error(SYNTAX_ANALYSIS_FAIL);
}

void call_params(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
        parser_data->token.type_of_token==TYPE_INT_NUMBER ||
        parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
        parser_data->token.type_of_token==TYPE_STRING)
        {
            call_params(parser_data);
        }else{
            process_error(SYNTAX_ANALYSIS_FAIL); 
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
        generate_token(&parser_data->token, &parser_data->my_string);
        start(parser_data);
    }else{
        process_error(SYNTAX_ANALYSIS_FAIL); 
    }
}

void call_param(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
    parser_data->token.type_of_token==TYPE_INT_NUMBER ||
    parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
    parser_data->token.type_of_token==TYPE_STRING)
    {
        call_params(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema parametre
       printf("Sem by som mal prist \n");
       generate_token(&parser_data->token, &parser_data->my_string);
       start(parser_data); 
    }else{
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}


void function_call(syntactic_data_t *parser_data){
    //generate_token(&parser_data->token, &parser_data->my_string);
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
            call_param(parser_data);
            //start(parser_data);
        }   
    }
}



void function(syntactic_data_t *parser_data){
    
}

void start(syntactic_data_t *parser_data){
    if(parser_data->token.type_of_token==TYPE_STRING){
        generate_token(&parser_data->token, &parser_data->my_string);
    }  
    printf("prijaty token %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        function_call(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){              //deklaracia funkcie
        function_declaration(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
       // generate_token(&parser_data.token, &parser_data.my_string);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
            //function(&parser_data);
        }
    }
    if(parser_data->token.type_of_token==TYPE_KW_EOF){
        printf("Syntax ok\n");
        exit(0);
    }
    process_error(SYNTAX_ANALYSIS_FAIL);
}
/*
void init_parser_data(syntactic_data_t *parser_data){
    table_init(&parser_data->global_table);
    table_init(&parser_data->local_table);
    
    parser_data->token=NULL; 
    
}
*/
void analyze(){
    syntactic_data_t parser_data;
    
    //Token term;
    //Token *actualterm = &term; 

    //Custom_string my_string;
    //Custom_string *my_str = &my_string;

    custom_string_init(&parser_data.my_string); 

    generate_token(&parser_data.token, &parser_data.my_string);
    printf("prvy vygenervany token %d \n", parser_data.token.type_of_token);
    if(parser_data.token.type_of_token==TYPE_KW_REQUIRE){
      generate_token(&parser_data.token, &parser_data.my_string);
      printf("druhy vygenervany token %d \n", parser_data.token.type_of_token);
        if(parser_data.token.type_of_token==TYPE_STRING){ 
            genertaor_start(&parser_data);           
            start(&parser_data); 
        }
    }

    custom_string_free_memory(&parser_data.my_string);

    //printf("Syntax error\n");
    //exit;
}