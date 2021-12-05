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

void double_dosts_nt(){
    if(get_token()==TYPE_COMMA){
         if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
             double_dosts_nt();
         }    
    }
    //epsilon pravidla
    if(token==TYPE_KW_FUNCTION){

    }
    if(token==IS_GLOBAL){

    }
    if(token==TYPE_KW_IF){

    }
    if(token==TYPE_KW_LOCAL){

    }
    if(token==TYPE_KW_RETURN){

    }
    if(token==TYPE_KW_EOF){

    }
    pirnf("Syntax error\n");
    exit;
}

void double_dot_nt(){
    Token token;
    token=get_token();
    if(token.type_of_token==TYPE_COLON){
        token=get_token();
        if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
            double_dots_nt();
        }
    }else{
        start(token);
    }
    //epsilon pravidla
    
    printf("Syntax error\n");
    exit;
}

void params_nt(syntactic_data_t *parser_data){
    //semantic kontrola
    Token token;
    token=get_token();
    if(token.type_of_token==TYPE_COMMA){
        token=get_token();
         if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
            params_nt(&parser_data);
        }
    }else if(token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
        return; //koniec parametrov funkcie
    }
    printf("Syntax error\n");
    exit;
}

void param_nt(){
    Token token;
    token=get_token();
     if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
         params_nt(token);
     }else if(token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
         return; //funkcia ziadne paramterne nema
     }
}

void function_declaration(){
    Token token;
    token=get_token();
    if(token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
        //zapis do TS
        if(get_token().type_of_token==TYPE_COLON){
            if(get_token().type_of_token==TYPE_KW_FUNCTION){
                if(get_token().type_of_token==TYPE_LEFT_ROUND_BRACKET){
                    param_nt(); //parametre funkcie
                    double_dot_nt(); //navratove hodnoty funkcie

                    
                }
            }
        }
    }
    printf("Syntax error\n");
    exit;
}

void function_call(Token *token){

}



void function(Token *token){
    
}
*/
void start(syntactic_data_t *parser_data){

    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        //function_call(&parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){              //deklaracia funkcie
        //function_declaration();
    }
    if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
       // generate_token(&parser_data.token, &parser_data.my_string);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
            //function(&parser_data);
        }
    }
    if(parser_data->token.type_of_token==TYPE_KW_EOF){
        printf("Syntax ok\n");
    }
    printf("Syntax error\n");
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