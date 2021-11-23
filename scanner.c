#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#include "error.h"
#include "scanner.h"


int process_identificator(Custom_string *string, Token *token, char character){
    if(custom_string_compare_with_basic_string(string->string_value,"do") == 0){
        token->type_of_token = TYPE_KW_DO;

    }else if(custom_string_compare_with_basic_string(string->string_value,"else") == 0){
        token->type_of_token = TYPE_KW_ELSE;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"end") == 0){
        token->type_of_token = TYPE_KW_END;
    
    }else if(custom_string_compare_with_basic_string(string->string_value,"function") == 0){
        token->type_of_token = TYPE_KW_FUNCTION;

    }else if(custom_string_compare_with_basic_string(string->string_value,"global") == 0){
        token->type_of_token = TYPE_KW_GLOBAL;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"if") == 0){
        token->type_of_token = TYPE_KW_IF;

    }else if(custom_string_compare_with_basic_string(string->string_value,"integer") == 0){
        token->type_of_token = TYPE_KW_INTEGER;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"local") == 0){
        token->type_of_token = TYPE_KW_LOCAL;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"nil") == 0){
        token->type_of_token = TYPE_KW_NIL;
    
    }else if(custom_string_compare_with_basic_string(string->string_value,"number") == 0){
        token->type_of_token = TYPE_KW_NUMBER;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"require") == 0){
        token->type_of_token = TYPE_KW_REQUIRE;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"return") == 0){
        token->type_of_token = TYPE_KW_RETURN;
    
    }else if(custom_string_compare_with_basic_string(string->string_value,"string") == 0){
        token->type_of_token = TYPE_KW_STRING;
    
    }else if(custom_string_compare_with_basic_string(string->string_value,"then") == 0){
        token->type_of_token = TYPE_KW_THEN;
        
    }else if(custom_string_compare_with_basic_string(string->string_value,"while") == 0){
        token->type_of_token = TYPE_KW_WHILE;

    }else if(character == '('){
        token->type_of_token = TYPE_IDENTIFICATOR_FUNCTION;
    }else{
        token->type_of_token = TYPE_IDENTIFICATOR_VARIABLE;
    }

    if (token->type_of_token == TYPE_IDENTIFICATOR_VARIABLE || token->type_of_token == TYPE_IDENTIFICATOR_FUNCTION ){
        bool error = custom_string_copy_string(string,token->token_info.custom_string);
        if(error == false){
            custom_string_free_memory(string);
            return process_error(SCANNER_ANALYSIS_FAIL);
        } 
    }

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);

}

int process_double_value(Custom_string *string, Token *token){
    char *ptr;
    double double_value = (double) strtod(string->string_value, &ptr);

    if(*ptr != NULL){
        custom_string_free_memory(string);
        return process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_DOUBLE_NUMBER;
    token->token_info.double_value = double_value;

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);
}

int process_integer_value(Custom_string *string, Token *token){
    char *ptr;
    int integer_value = (int) strtol(string->string_value, &ptr, 10);

    if(*ptr != NULL){
        custom_string_free_memory(string);
        return process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_INT_NUMBER;
    token->token_info.integer_value = integer_value;

    custom_string_free_memory(string);
    return process_error(SCANNER_ANALYSIS_SUCCESS);

}


int generate_token(Token *token, Custom_string *string){

    if(string == NULL){
        return process_error(INTERNAL_FAILATURE);
    }

    token->token_info.custom_string = string;

    Custom_string tmp_string;
    Custom_string *tmp_str = &tmp_string;

    int current_charcter;
    int current_state = SCANNER_START;
    char *ptr;
    bool is_double = false;

    if(custom_string_init(tmp_str) == 0){
        custom_string_free_memory(tmp_str);
        return process_error(INTERNAL_FAILATURE);
    }

    while (1){
        current_charcter = fgetc(stdin);

        switch (current_state){

            case SCANNER_START:

                if (isspace(current_charcter) && current_charcter == '\n' ){
                    token->token_info.row_number++;
                    continue;
                }else if (current_charcter == '='){
                    current_state = STATE_EQUALS_F;
                }else if (current_charcter == '<'){
                    current_state = STATE_LESS_THAN_F;
                }else if (current_charcter == '>'){
                    current_state = STATE_MORE_THAN_F;
                }else if (current_charcter == '.'){
                    current_state = STATE_STRING_CONCAT_F;
                }else if (current_charcter == '-'){
                    current_state = STATE_MINUS;
                }else if (current_charcter == '/'){
                    current_state = STATE_BACKSLASH_F;
                }else if (current_charcter == '"'){
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if (current_charcter == '~'){
                    current_state = STATE_NOT_EQUAL_F;
                }else if (current_charcter == EOF){
                    current_state = STATE_EOF_F;
                }else if (isspace(current_charcter)){
                    current_state = STATE_START_F;
                }else if (isalpha(current_charcter) || current_charcter == '_'){

                    int error = custom_string_add_character(tmp_str,(char) tolower(current_charcter));

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_IDENT_OR_KW;

                }else if (isdigit(current_charcter)){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    is_double = false;

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_F;
                    
                }else if (current_charcter == '{'){
                    token->type_of_token = TYPE_LEFT_CURLY_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == '}'){
                    token->type_of_token = TYPE_RIGHT_CURLY_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == '('){
                    token->type_of_token = TYPE_LEFT_ROUND_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == ')'){
                    token->type_of_token = TYPE_RIGHT_ROUND_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == '*'){
                    token->type_of_token = TYPE_MULTIPLICATE;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == '#'){
                    token->type_of_token = TYPE_HASHTAG;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == '+'){
                    token->type_of_token = TYPE_PLUS;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == ':'){
                    token->type_of_token = TYPE_COLON;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }else if (current_charcter == ','){
                    token->type_of_token = TYPE_COMMA;
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }

                break;
            
            case STATE_IDENT_OR_KW:

                if (isalpha(current_charcter) || current_charcter == '_'){

                    int error = custom_string_add_character(tmp_str,(char) tolower(current_charcter));

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_IDENT_OR_KW;

                }else{
                    ungetc(current_charcter,stdin);
                    return process_identificator(str,token,current_charcter);
                }
                break;

            case STATE_EQUALS_F:

                if(current_charcter == '=' ){
                    token->type_of_token = TYPE_EKV;
                }else{
                    ungetc(current_charcter,stdin);
                    token->type_of_token = TYPE_ASSIGN;
                }
                break;

            case STATE_MORE_THAN_F:

                if(current_charcter == '=' ){
                    token->type_of_token = TYPE_GEKV;
                }else{
                    ungetc(current_charcter,stdin);
                    token->type_of_token = TYPE_GTHEN;
                }
                break;

            case STATE_LESS_THAN_F:

                if(current_charcter == '=' ){
                    token->type_of_token = TYPE_LEKV;
                }else{
                    ungetc(current_charcter,stdin);
                    token->type_of_token = TYPE_LTHEN;
                }
                break;

            case STATE_NOT_EQUAL_F:

                if(current_charcter == '=' ){
                    token->type_of_token = TYPE_NEKV;
                }else{
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }
                break;

            case STATE_STRING_CONCAT_F:

                if(current_charcter == '.' ){
                    token->type_of_token = TYPE_STRING_CONCAT;
                }else{
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }
                break;

            case STATE_BACKSLASH_F:

                if(current_charcter == '/' ){
                    token->type_of_token = TYPE_DIVIDE_INT;
                }else{
                    ungetc(current_charcter,stdin);
                    token->type_of_token = TYPE_DIVIDE;
                }
                break;

            case STATE_NUMBER_F:

                if(isdigit(current_charcter)){
                    
                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_F;

                }else if (tolower(current_charcter) == 'e'){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_EXPONENT_N;

                }else if (current_charcter == '.'){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_DOT_N;

                }else if(is_double == true){
                    ungetc(current_charcter,stdin);
                    return process_double_value(tmp_str,token);
                }else{
                    ungetc(current_charcter,stdin);
                    return process_integer_value(tmp_str,token);
                }
                break;

            case STATE_NUMBER_DOT_N:

                if(isdigit(current_charcter)){

                    is_double = true;

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_F;

                }else{
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }
                break;
            
            case STATE_NUMBER_EXPONENT_N:
                if(current_charcter == '+' || current_charcter == '-'){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_EXPONENT_SIGN_N;

                }else if(isdigit(current_charcter)){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }
                break;

            case STATE_NUMBER_EXPONENT_SIGN_N:

                if(isdigit(current_charcter)){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }
                break;
            case STATE_NUMBER_EXPONENT_NUMBER_F:

                if(isdigit(current_charcter)){

                    int error = custom_string_add_character(tmp_str,current_charcter);

                    if(error == 0){
                        custom_string_free_memory(tmp_str);
                        return process_error(INTERNAL_FAILATURE);
                    }

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_charcter,stdin);
                    return process_double_value(tmp_str,token);
                }
                break;
            case STATE_ESCAPE_SEQ_N:

                if (current_character == '"' ){
                    current_state = STATE_ESC_SEQ_FINAL;
                }else if(current_character == '\\' ){
                    current_state = STATE_ESC_SEQ_SLASH_N;
                }else if(current_state < 32 || current_state == '#' || current_state == EOF){
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);
                }else{
                    int error = custom_string_copy_string(tmp_str,token->token_info.custom_string);

                    if(error == 0){
                    custom_string_free_memory(tmp_str);
                    return process_error(INTERNAL_FAILATURE);
                    }
                    current_state = STATE_ESCAPE_SEQ_N;
                }
                
                break;
            case STATE_ESC_SEQ_SLASH_N:
                if() //TODO
                break;

            case STATE_ESC_SEQ_FINAL:
                int error = custom_string_copy_string(tmp_str,token->token_info.custom_string);

                if(error == 0){
                    custom_string_free_memory(tmp_str);
                    return process_error(INTERNAL_FAILATURE);
                }

                token->type_of_token = TYPE_STRING;
                custom_string_free_memory(tmp_str);
                return process_error(SCANNER_ANALYSIS_SUCCESS);

                break;

            case STATE_MINUS:

                if(current_charcter == '-'){
                    current_state = STATE_LINE_COMMENTARY_F;
                }else{
                    token->type_of_token = TYPE_MINUS;
                    ungetc(current_charcter,stdin);
                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_SUCCESS);
                }
                break;

            case STATE_LINE_COMMENTARY_F:

                if(current_charcter == '\n' || current_charcter == EOF){
                    token->token_info.row_number++;
                    current_state = STATE_START_F;
                    ungetc(current_charcter,stdin);
                }else if (current_charcter == '['){
                    current_state = STATE_BLOCK_COMMENT_N;
                }else{
                    current_state = STATE_LINE_COMMENTARY_F;
                }
                break;

            case STATE_BLOCK_COMMENT_N:

                if(current_charcter == '['){
                    current_state = STATE_BLOCK_COMMENT_F;
                }else if(current_charcter == EOF){

                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);

                }else{
                    current_state = STATE_LINE_COMMENTARY_F;
                }
                break;

            case STATE_BLOCK_COMMENT_F:

                if(current_charcter == ']'){
                    current_state = STATE_END_BLOCK_COMMENT_N;
                }else if(current_charcter == EOF){

                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);

                }else{
                    current_state = STATE_BLOCK_COMMENT_F;
                }
                break;

            case STATE_END_BLOCK_COMMENT_N:

                if(current_charcter == ']'){
                    current_state = STATE_START_F;
                }else if(current_charcter == EOF){

                    custom_string_free_memory(tmp_str);
                    return process_error(SCANNER_ANALYSIS_FAIL);

                }else{
                    current_state = STATE_BLOCK_COMMENT_F;
                }
                break;

            case STATE_EOF_F:

                token->type_of_token = TYPE_EOF;
                ungetc(current_charcter,stdin);
                custom_string_free_memory(tmp_str);
                return process_error(SCANNER_ANALYSIS_SUCCESS);

                break;
            default:
                break;
        }


    }
    

}
