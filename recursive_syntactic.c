#include "LL_table.h"

Token get_token(){
    Token term;
    Token *actualterm = &term; 

    return generate_token(actualterm, get_custom_string());
}

Custom_string get_custom_string(){
    Custom_string my_string;
    Custom_string *my_str = &my_string; 
        
    return custom_string_init(my_str);
}

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

void double_dot_nt(){
    Token token;
    token=get_token();
    if(token.type_of_token==TYPE_COLON){
        if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){

        }
    }
}

void params_nt(Token *token){
    //semantic kontrola
    if(get_token()==TYPE_COMMA){
        token=get_token();
         if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
            params_nt(token);
        }
    }
    if(get_token==TYPE_RIGHT_ROUND_BRACKET){
        double_dot_nt();
    }
    printf("Syntax error\n");
    exit;
}

void param_nt(){
    Token token;
    token=get_token();
     if(token.type_of_token==TYPE_KW_INTEGER || token.type_of_token==TYPE_KW_NUMBER || token.type_of_token==TYPE_KW_STRING){
         params_nt(token);
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
                    param_nt();
labelfunctiodeclaration:
                    
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

void start(){
    Token token;
    token=get_token();

    if(token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        function_call(token);
    }
    if(token.type_of_token==TYPE_KW_GLOBAL{              //deklaracia funkcie
        function_declaration();
    }
    if(token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
        token=get_token();
        if(token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
            function(token);
        }
    }
    }
    if(token.type_of_token==TYPE_KW_EOF){
        printf("Syntax ok\n");
    }
    printf("Syntax error\n");
}


void analyze(){
    if(get_token().type_of_token==TYPE_KW_REQUIRE){
        if(get_token().type_of_token==TYPE_STRING){            
            start(); 
        }
    }
    printf("Syntax error\n");
    exit;
}