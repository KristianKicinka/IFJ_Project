/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file lexical_analysis.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Lexikálna analýza (implementácia)
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

#include "lexical_analysis.h"

// Definition of constant escape sequencies 
#define HASH_SEQUENCE "035"
#define SLASH_A_SEQUENCE "007"
#define SLASH_B_SEQUENCE "008"
#define SLASH_F_SEQUENCE "012"
#define SLASH_R_SEQUENCE "013"
#define SLASH_T_SEQUENCE "009"
#define SLASH_N_SEQUENCE "010"
#define SLASH_V_SEQUENCE "011"
#define SLASH_SLASH_SEQUENCE "092"
#define QUOT_MARK_S_SEQUENCE "039"
#define QUOT_MARK_D_SEQUENCE "034"


char *keywords_array[COUNT_OF_KEYWORDS] = {
   "do","else","end","function",
   "global","if","integer","local",
   "nil","number","require","return",
   "string","then","while"
};

Token_type keywords_enum_array[COUNT_OF_KEYWORDS] = {
   TYPE_KW_DO,TYPE_KW_ELSE,TYPE_KW_END,TYPE_KW_FUNCTION,
   TYPE_KW_GLOBAL,TYPE_KW_IF,TYPE_KW_INTEGER,TYPE_KW_LOCAL,
   TYPE_KW_NIL,TYPE_KW_NUMBER,TYPE_KW_REQUIRE,TYPE_KW_RETURN,
   TYPE_KW_STRING,TYPE_KW_THEN,TYPE_KW_WHILE
};


void process_identificator(Custom_string *string, Token *token, char character){

    bool keyword_is_set = false;

    for (int i = 0; i < COUNT_OF_KEYWORDS; i++){
        if(custom_string_compare_with_basic_string(string,keywords_array[i]) == 0){
            token->type_of_token = keywords_enum_array[i];
            keyword_is_set = true;
            break;
        }
    }

    if(keyword_is_set == false){
        if(character == '('){
            token->type_of_token = TYPE_IDENTIFICATOR_FUNCTION;
        }else{
            token->type_of_token = TYPE_IDENTIFICATOR_VARIABLE;
        }
    }
    

    custom_string_copy_string(string,token->token_info.custom_string);

    token->has_str_val = true;
    return;

}

void process_double_value(Custom_string *string, Token *token){
    char *ptr;
    double double_value = (double) strtod(string->string_value, &ptr);

    if(*ptr){
        custom_string_free_memory(string);
        process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_DOUBLE_NUMBER;
    token->token_info.double_value = double_value;

    custom_string_free_memory(string);
    return;
}

void process_integer_value(Custom_string *string, Token *token){
    char *ptr;
    int integer_value = (int) strtol(string->string_value, &ptr, 10);

    if(*ptr){
        custom_string_free_memory(string);
        process_error(INTERNAL_FAILATURE);
    }

    token->type_of_token = TYPE_INT_NUMBER;
    token->token_info.integer_value = integer_value;

    custom_string_free_memory(string);
    return;
}


void generate_token(Token *token, Custom_string *string){

    if(string == NULL){
        process_error(INTERNAL_FAILATURE);
    }

    token->token_info.custom_string = string;
    token->has_str_val = false;

    Custom_string tmp_string;
    Custom_string *tmp_str = &tmp_string;

    char current_character;
    int current_state = STATE_START_F;
    bool is_double = false;
    char escape_numbers[4] = {0,0,0};

    custom_string_init(tmp_str);

    while (1){

        current_character = (char) fgetc(stdin);

        switch (current_state){

            case STATE_START_F:
                if(isspace(current_character)){
                    current_state = STATE_START_F;
                }else if (isspace(current_character) && current_character == '\n' ){
                    token->row_number++ ;
                    current_state = STATE_START_F;
                }else if (current_character == '='){
                    current_state = STATE_EQUALS_F;
                }else if (current_character == '<'){
                    current_state = STATE_LESS_THAN_F;
                }else if (current_character == '>'){
                    current_state = STATE_MORE_THAN_F;
                }else if (current_character == '.'){
                    current_state = STATE_STRING_CONCAT_F;
                }else if (current_character == '-'){
                    current_state = STATE_MINUS;
                }else if (current_character == '/'){
                    current_state = STATE_BACKSLASH_F;
                }else if (current_character == '"'){
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if (current_character == '~'){
                    current_state = STATE_NOT_EQUAL_F;
                }else if (current_character == EOF){
                    current_state = STATE_EOF_F;
                }else if (isalpha(current_character) || current_character == '_'){

                    custom_string_add_character(tmp_str,(char) tolower(current_character));

                    current_state = STATE_IDENT_OR_KW;

                }else if (isdigit(current_character)){

                    custom_string_add_character(tmp_str,current_character);

                    is_double = false;

                    current_state = STATE_NUMBER_F;
                    
                }else if (current_character == '{'){
                    token->type_of_token = TYPE_LEFT_CURLY_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == '}'){
                    token->type_of_token = TYPE_RIGHT_CURLY_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == '('){
                    token->type_of_token = TYPE_LEFT_ROUND_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == ')'){
                    token->type_of_token = TYPE_RIGHT_ROUND_BRACKET;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == '*'){
                    token->type_of_token = TYPE_MULTIPLICATE;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == '#'){
                    token->type_of_token = TYPE_HASHTAG;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == '+'){
                    token->type_of_token = TYPE_PLUS;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == ':'){
                    token->type_of_token = TYPE_COLON;
                    custom_string_free_memory(tmp_str);
                    return;
                }else if (current_character == ','){
                    token->type_of_token = TYPE_COMMA;
                    custom_string_free_memory(tmp_str);
                    return;
                }

                break;
            
            case STATE_IDENT_OR_KW:

                if (isalpha(current_character) || current_character == '_'){

                    custom_string_add_character(tmp_str,(char) tolower(current_character));

                    current_state = STATE_IDENT_OR_KW;

                }else{
                    ungetc(current_character,stdin);
                    process_identificator(tmp_str,token,current_character);
                }
                break;

            case STATE_EQUALS_F:

                if(current_character == '=' ){
                    token->type_of_token = TYPE_EKV;
                }else{
                    ungetc(current_character,stdin);
                    token->type_of_token = TYPE_ASSIGN;
                }

                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_MORE_THAN_F:

                if(current_character == '=' ){
                    token->type_of_token = TYPE_GEKV;
                }else{
                    ungetc(current_character,stdin);
                    token->type_of_token = TYPE_GTHEN;
                }

                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_LESS_THAN_F:

                if(current_character == '=' ){
                    token->type_of_token = TYPE_LEKV;
                }else{
                    ungetc(current_character,stdin);
                    token->type_of_token = TYPE_LTHEN;
                }
                
                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_NOT_EQUAL_F:

                if(current_character == '=' ){
                    token->type_of_token = TYPE_NEKV;
                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }

                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_STRING_CONCAT_F:

                if(current_character == '.' ){
                    token->type_of_token = TYPE_STRING_CONCAT;
                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }

                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_BACKSLASH_F:

                if(current_character == '/' ){
                    token->type_of_token = TYPE_DIVIDE_INT;
                }else{
                    ungetc(current_character,stdin);
                    token->type_of_token = TYPE_DIVIDE;
                }

                custom_string_free_memory(tmp_str);
                return;

                break;

            case STATE_NUMBER_F:

                if(isdigit(current_character)){
                    
                    custom_string_add_character(tmp_str,(char) current_character);

                    current_state = STATE_NUMBER_F;

                }else if (tolower(current_character) == 'e'){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_EXPONENT_N;

                }else if (current_character == '.'){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_DOT_N;

                }else{
                    ungetc(current_character,stdin);
                    if(is_double == true){
                        process_double_value(tmp_str,token);
                    }else{
                        process_integer_value(tmp_str,token);
                    }
                }
                break;

            case STATE_NUMBER_DOT_N:

                if(isdigit(current_character)){

                    is_double = true;

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_F;

                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }
                break;
            
            case STATE_NUMBER_EXPONENT_N:
                if(current_character == '+' || current_character == '-'){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_EXPONENT_SIGN_N;

                }else if(isdigit(current_character)){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }
                break;

            case STATE_NUMBER_EXPONENT_SIGN_N:

                if(isdigit(current_character)){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }
                break;

            case STATE_NUMBER_EXPONENT_NUMBER_F:

                if(isdigit(current_character)){

                    custom_string_add_character(tmp_str,current_character);

                    current_state = STATE_NUMBER_EXPONENT_NUMBER_F;

                }else{
                    ungetc(current_character,stdin);
                    process_double_value(tmp_str,token);
                }
                break;

            case STATE_ESCAPE_SEQ_N:

                if (current_character == '"' ){
                    current_state = STATE_ESC_SEQ_FINAL;
                }else if(current_character == '\\' ){
                    current_state = STATE_ESC_SEQ_SLASH_N;
                }else if(current_character < 32 || current_character == EOF){
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }else{

                    custom_string_add_character(tmp_str,(char) current_character);

                    current_state = STATE_ESCAPE_SEQ_N;
                }
                break;

            case STATE_ESC_SEQ_SLASH_N:{

                if(current_character == 'a' ){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_A_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 'b'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_B_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 'f'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_F_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 'r'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_R_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 't'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_T_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 'v'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_V_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == '\\'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_SLASH_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == '"'){
                    custom_string_add_character(tmp_str,(char) atoi(QUOT_MARK_D_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == '\''){
                    custom_string_add_character(tmp_str,(char) atoi(QUOT_MARK_S_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == 'n'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_N_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == '\n'){
                    custom_string_add_character(tmp_str,(char) atoi(SLASH_N_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;
                }else if(current_character == '#'){
                    custom_string_add_character(tmp_str,(char) atoi(HASH_SEQUENCE));
                    current_state = STATE_ESCAPE_SEQ_N;

                }else if(current_character == 'z'){
                    current_state = STATE_ESC_SEQ_WHITE;
                }else if(isdigit(current_character)){
                    escape_numbers[0] = current_character;
                    current_state = STATE_ESC_SEQ_NUMBER_1_N;
                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }

                break;
            }

            case STATE_ESC_SEQ_WHITE:
                if(isspace(current_character)){
                    current_state = STATE_ESC_SEQ_WHITE;
                }else{
                    current_state = STATE_ESCAPE_SEQ_N;
                }
                break;

            case STATE_ESC_SEQ_NUMBER_1_N:
                if(isdigit(current_character)){
                    escape_numbers[1] = current_character;
                    current_state = STATE_ESC_SEQ_NUMBER_2_N;
                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }
                break;

            case STATE_ESC_SEQ_NUMBER_2_N:
                if(isdigit(current_character)){

                    escape_numbers[2] = current_character;
                    char *ptr;
                    char *ptr_int;
                    char tmp_char = (char) strtol(escape_numbers,&ptr,10);
                    int tmp_int = (int) strtol(escape_numbers,&ptr_int,10);

                    if(*ptr && *ptr_int){
                        ungetc(current_character,stdin);
                        custom_string_free_memory(tmp_str);
                        process_error(INTERNAL_FAILATURE);
                    }else{
                        if(tmp_int >= 1 && tmp_int <= 255){
                            custom_string_add_character(tmp_str,tmp_char);
                            current_state = STATE_ESCAPE_SEQ_N;
                        }else{
                            ungetc(current_character,stdin);
                            custom_string_free_memory(tmp_str);
                            process_error(LEXICAL_ANALYSIS_FAIL);
                        }
                    }
                    
                }else{
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);
                }
                break;

            case STATE_ESC_SEQ_FINAL:{

                custom_string_copy_string(tmp_str,token->token_info.custom_string);

                token->type_of_token = TYPE_STRING;
                token->has_str_val = true;

                ungetc(current_character,stdin);
                custom_string_free_memory(tmp_str);
                return;

                break;
            }
            
            case STATE_MINUS:

                if(current_character == '-'){
                    current_state = STATE_LINE_COMMENTARY_F;
                }else{
                    token->type_of_token = TYPE_MINUS;
                    ungetc(current_character,stdin);
                    custom_string_free_memory(tmp_str);
                    return;
                }
                break;

            case STATE_LINE_COMMENTARY_F:

                if(current_character == '\n' || current_character == EOF){
                    token->row_number++;
                    current_state = STATE_START_F;
                    ungetc(current_character,stdin);
                }else if (current_character == '['){
                    current_state = STATE_BLOCK_COMMENT_N;
                }else{
                    current_state = STATE_LINE_COMMENTARY_F;
                }
                break;

            case STATE_BLOCK_COMMENT_N:

                if(current_character == '['){
                    current_state = STATE_BLOCK_COMMENT_F;
                }else if(current_character == EOF){

                    custom_string_free_memory(tmp_str);
                    return;

                }else if(current_character == '\n'){
                    token->row_number++;
                    current_state = STATE_START_F;
                }else{
                    current_state = STATE_LINE_COMMENTARY_F;
                }
                break;

            case STATE_BLOCK_COMMENT_F:

                if(current_character == ']'){
                    current_state = STATE_END_BLOCK_COMMENT_N;
                }else if(current_character == EOF){

                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);

                }else{
                    current_state = STATE_BLOCK_COMMENT_F;
                }
                break;

            case STATE_END_BLOCK_COMMENT_N:

                if(current_character == ']'){
                    current_state = STATE_START_F;
                }else if(current_character == EOF){

                    custom_string_free_memory(tmp_str);
                    process_error(LEXICAL_ANALYSIS_FAIL);

                }else{
                    current_state = STATE_BLOCK_COMMENT_F;
                }
                break;

            case STATE_EOF_F:

                token->type_of_token = TYPE_KW_EOF;
                ungetc(current_character,stdin);
                custom_string_free_memory(tmp_str);
                process_error(LEXICAL_ANALYSIS_SUCCESS);

                break;
        }


    }
    

}

