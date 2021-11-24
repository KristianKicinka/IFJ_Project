// tests for lex_analysis


#include "../../scanner.h"
#include <stdio.h>

void print_token(Token *token);

int main(int argc, char const *argv[])
{
    Custom_string my_string;
    Custom_string *my_str = &my_string;

    Token my_token;
    Token *my_tok = &my_token;

    Token my_token_2;
    Token *my_tok_2 = &my_token_2;

    init_token(my_tok);
    init_token(my_tok_2);

    //print_token(my_tok);

    custom_string_init(my_str);

    // gen 1 tok
    generate_token(my_tok,my_str);

    print_token(my_tok);

    //gen 2 tok

    custom_string_init(my_str);

    generate_token(my_tok_2,my_str);

    print_token(my_tok_2);

    //gen 3 tok

    custom_string_init(my_str);

    generate_token(my_tok,my_str);

    print_token(my_tok);

    custom_string_free_memory(my_str);

    return 0;
}


void print_token(Token *token){
    printf("######################################################\n");
    printf("TOKEN VALUES \n");
    printf("Token type : %d \n",token->type_of_token);
    printf("Token value int : %d \n",(int) token->token_info.integer_value);
    printf("Token value double : %f \n",token->token_info.double_value);
    printf("Token value string : %s \n",token->token_info.custom_string->string_value);
    printf("Token row number : %d \n",(int)token->token_info.row_number);
    printf("######################################################\n");
    
}