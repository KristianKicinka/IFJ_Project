// tests for lex_analysis


#include "../../scanner.h"
#include <stdio.h>
#include <stdlib.h>

void print_token(Token *token,int i);

int main(int argc, char const *argv[]){

    

    for (int i = 0; i < 5; i++){

        Token my_token;
        Token *my_tok = &my_token;

        Custom_string my_string;
        Custom_string *my_str = &my_string;

        custom_string_init(my_str);

        int error = generate_token(my_tok,my_str);
        printf("error : %d \n",error);

        if(error != 0){
            custom_string_free_memory(my_str);
            return 1;
        }
            
        print_token(my_tok,i);

        custom_string_free_memory(my_str);       
    }
    
    

    return 0;
}


void print_token(Token *token, int i){
    printf("######################################################\n");
    printf("TOKEN ( %d ) VALUES \n",i);
    printf("Token type : %d \n",token->type_of_token);
    printf("Token value int : %d \n",(int) token->token_info.integer_value);
    printf("Token value double : %f \n",token->token_info.double_value);
    if(token->has_str_val == true)
        printf("Token value string : %s \n",token->token_info.custom_string->string_value);
    printf("Token row number : %d \n",(int)token->row_number);
    printf("######################################################\n");
    
}