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



void while_nt(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("Token vo while %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
    parser_data->token.type_of_token==TYPE_KW_NUMBER || 
    parser_data->token.type_of_token==TYPE_KW_STRING || 
    parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //vchadzam do statemenetu
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
        //IF BOTOOM UP OK
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_KW_DO){
            parser_data->in_while=true;
            printf("Z while idem do code\n");
            generate_token(&parser_data->token, &parser_data->my_string);
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
        generate_token(&parser_data->token, &parser_data->my_string);
        code(parser_data);
    }else{ //vo vetve if sa nachadza kod
        //generate_token(&parser_data->token, &parser_data->my_string);
        code(parser_data);
    }
}

void if_nt(syntactic_data_t *parser_data){
     generate_token(&parser_data->token, &parser_data->my_string);
     printf("Token v if_nt %d\n", parser_data->token.type_of_token);
     if(parser_data->token.type_of_token==TYPE_KW_INTEGER || 
        parser_data->token.type_of_token==TYPE_KW_NUMBER ||
        parser_data->token.type_of_token==TYPE_KW_STRING ||
        parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        //volat BOOTOM-UP a poslat jej token
        //TODO vratene tokeny
        //IF BOTTOM UP OK
        generate_token(&parser_data->token, &parser_data->my_string);
        printf("Token v if_nt %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_KW_THEN){
            parser_data->in_if=true;
            generate_token(&parser_data->token, &parser_data->my_string);
            code_if_nt(parser_data);
        }
    }
}


void double_dots_nt(syntactic_data_t *parser_data){
    //printf("tokenik is : %d \n",parser_data->token.type_of_token);
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("tokenik is : %d \n",parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        generate_token(&parser_data->token, &parser_data->my_string);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
             printf("Daco\n");
             double_dots_nt(parser_data);
         }else{
             custom_string_free_memory(&parser_data->my_string);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
    //navrat pre deklaraciu funkcie   
    }else if(parser_data->token.type_of_token==TYPE_KW_FUNCTION && !parser_data->in_function){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_GLOBAL && !parser_data->in_function){
        start(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && !parser_data->in_function){
        printf("Tu by som sa mal vracat\n");
        start(parser_data);    
    }else if(parser_data->token.type_of_token==TYPE_KW_EOF && !parser_data->in_function){
        start(parser_data);
        return;
    //navrat pre definiciu funkcie
    }else if(parser_data->token.type_of_token==TYPE_KW_WHILE && parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_IF && parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION && parser_data->in_function){
        //parser_data->in_function=false;
        printf("NAPATE\n");
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_RETURN && parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE && parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_LOCAL && parser_data->in_function){
        //parser_data->in_function=false;
        code(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function){ //funkcia bez navratovych hodnot
        generate_token(&parser_data->token, &parser_data->my_string);
        start(parser_data);
    }else{
        //epsilon pravidla
        printf("mam tuna token: %d\n", parser_data->token.type_of_token);
        printf("tu som spadol\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }     
}


void double_dot_nt(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("\ndouble dot nt token %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COLON){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
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
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_COMMA){
         generate_token(&parser_data->token, &parser_data->my_string);
         if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
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
    generate_token(&parser_data->token, &parser_data->my_string);
     if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || parser_data->token.type_of_token==TYPE_KW_STRING){
         printf("\nidem do params nt\n");
         params_nt(parser_data);
     }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
         printf("\nfunkcia nema parametre\n");
         return; //funkcia ziadne paramterne nema
     }else{
         custom_string_free_memory(&parser_data->my_string);
         process_error(SYNTAX_ANALYSIS_FAIL);
     }
}


void function_declaration(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("Token at function declaration %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
        generate_token(&parser_data->token, &parser_data->my_string);
        printf("Token at function declaration %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_COLON){
            generate_token(&parser_data->token, &parser_data->my_string);
            printf("Token at function declaration %d\n", parser_data->token.type_of_token);
            if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){
                generate_token(&parser_data->token, &parser_data->my_string);
                printf("Token at function declaration %d\n", parser_data->token.type_of_token);
                if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
                    printf("function_declaration: idem do param_nt\n");
                    param_nt(parser_data); //parametre funkcie
                    
                    printf("\nostal mi token: %d\n", parser_data->token.type_of_token);
                    printf("\nVynoril som sa\n");

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
    printf("CALL PARAMS\n");
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("Tokenik is : %d \n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
        parser_data->token.type_of_token==TYPE_KW_INTEGER ||
        parser_data->token.type_of_token==TYPE_KW_NUMBER || 
        parser_data->token.type_of_token==TYPE_KW_STRING)
        {
            call_params(parser_data);
        }else{
            printf("SE AT call_params\n");
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL); 
        }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){
        printf("SKACEM Z CALL PARAMS NA START\n");
        //generate_token(&parser_data->token, &parser_data->my_string);
        start(parser_data);
    }else{
        printf("SE AT call_params DOWN\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL); 
    }
}

void call_param(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE || 
       parser_data->token.type_of_token==TYPE_KW_INTEGER ||
       parser_data->token.type_of_token==TYPE_DOUBLE_NUMBER || 
       parser_data->token.type_of_token==TYPE_STRING){
        call_params(parser_data);
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema parametre
       printf("Sem by som mal prist \n");
       generate_token(&parser_data->token, &parser_data->my_string);
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


void argument(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("token v argumente %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COMMA){ //funkcia ma viac parametrov
         generate_token(&parser_data->token, &parser_data->my_string);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){
             generate_token(&parser_data->token, &parser_data->my_string);
             if(parser_data->token.type_of_token==TYPE_COLON){ //nasleduje dalsi parameter
                 generate_token(&parser_data->token, &parser_data->my_string);
                 if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_STRING || parser_data->token.type_of_token==TYPE_KW_NUMBER){
                     argument(parser_data); //prijal som cely parameter, idem kontrolovat, ci neprisiel dalsi
                 }
             }else{
                printf("SE argument\n");
                custom_string_free_memory(&parser_data->my_string);
                process_error(SYNTAX_ANALYSIS_FAIL);
             } 
         }else{
             printf("SE argument\n");
             custom_string_free_memory(&parser_data->my_string);
             process_error(SYNTAX_ANALYSIS_FAIL);
         }
    }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //ziadny dalsi parameter nie je
        parser_data->in_function=true;
        printf("argument: idem do doubledotnt\n");
        double_dot_nt(parser_data); //idem kontrolovat navratove hodnoty
    }else{
        printf("SE argument dole\n");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
}

void arg(syntactic_data_t *parser_data){
    generate_token(&parser_data->token, &parser_data->my_string);
    printf("Token v arg %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_COLON){
        generate_token(&parser_data->token, &parser_data->my_string);
        printf("Token v arg nizsie %d\n", parser_data->token.type_of_token);
        if(parser_data->token.type_of_token==TYPE_KW_INTEGER || parser_data->token.type_of_token==TYPE_KW_NUMBER || TYPE_KW_STRING){
            printf("arg: idem do argumentu\n");
            argument(parser_data);
        }else{
            custom_string_free_memory(&parser_data->my_string);
            process_error(SYNTAX_ANALYSIS_FAIL);
        }
    }else{
        printf("SE at arg");
        custom_string_free_memory(&parser_data->my_string);
        process_error(SYNTAX_ANALYSIS_FAIL);
    }
    printf("END arg\n");
}

void function(syntactic_data_t *parser_data){
     generate_token(&parser_data->token, &parser_data->my_string);
     printf("token v function: %d\n", parser_data->token.type_of_token);
     if(parser_data->token.type_of_token==TYPE_LEFT_ROUND_BRACKET){
         generate_token(&parser_data->token, &parser_data->my_string);
         printf("token v function nizsie: %d\n", parser_data->token.type_of_token);
         if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){ //funckia ma aspon jeden parameter
            printf("function: idem do arg\n");
            arg(parser_data);
         }else if(parser_data->token.type_of_token==TYPE_RIGHT_ROUND_BRACKET){ //funkcia nema ziadne parametre
            parser_data->in_function=true;
            generate_token(&parser_data->token, &parser_data->my_string);
            code(parser_data);
         }else{
            process_error(SYNTAX_ANALYSIS_FAIL);
         }
     }else{
          process_error(SYNTAX_ANALYSIS_FAIL);
     }
     printf("END function\n");
}


void code(syntactic_data_t *parser_data){
    printf("dostal som sa do code s tokenom %d\n", parser_data->token.type_of_token);
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
    if(parser_data->token.type_of_token==TYPE_KW_RETURN){

    }
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_VARIABLE){

    }
    if(parser_data->token.type_of_token==TYPE_KW_LOCAL){

    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_while==true && parser_data->in_function==true){
        parser_data->in_while=false;
        generate_token(&parser_data->token, &parser_data->my_string);
        code(parser_data);
        //printf("\nSyntax ok code\n");
        //custom_string_free_memory(&parser_data->my_string);
        // exit(0);
    }
    if(parser_data->token.type_of_token==TYPE_KW_ELSE && parser_data->in_if==true){
        //EPS
        generate_token(&parser_data->token, &parser_data->my_string);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_if==true){
        parser_data->in_if=false;
        generate_token(&parser_data->token, &parser_data->my_string);
        code(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true){
        parser_data->in_function=false;
        printf("\nSyntax ok code\n");
        custom_string_free_memory(&parser_data->my_string);
        exit(0);
    }  
}


void start(syntactic_data_t *parser_data){
    //generate_token(&parser_data->token, &parser_data->my_string);
    printf("TOKEN NA STARTE %d\n", parser_data->token.type_of_token);
    if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){ //volanie funkcie
        function_call(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_GLOBAL){              //deklaracia funkcie
        printf("Start: idem do fucntion_declaration\n");
        function_declaration(parser_data);
    }
    if(parser_data->token.type_of_token==TYPE_KW_FUNCTION){           //definicia funkcie
        generate_token(&parser_data->token, &parser_data->my_string);
        if(parser_data->token.type_of_token==TYPE_IDENTIFICATOR_FUNCTION){
            printf("start: volam func_nt\n");
            function(parser_data);
        }
    }
    if(parser_data->token.type_of_token==TYPE_KW_END && parser_data->in_function==true){
        parser_data->in_function=false;
        generate_token(&parser_data->token, &parser_data->my_string);
        start(parser_data);
    } 
    if(parser_data->token.type_of_token==TYPE_KW_EOF){
        printf("\nSyntax ok\n");
        custom_string_free_memory(&parser_data->my_string);
        exit(0);
    }
    printf("\nSE AT START\n");
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
    parser_data.in_function=false;
    parser_data.in_if=false;
    //parser_data.in_while=false; toto by tu malo byt ale ked to tam je tak sa to rozdrbe tak radsej nak to tam nie je xD
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
            generate_token(&parser_data.token, &parser_data.my_string);
            start(&parser_data); 
        }
    }

    custom_string_free_memory(&parser_data.my_string);

    //printf("Syntax error\n");
    //exit;
}