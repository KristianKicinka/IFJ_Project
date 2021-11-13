#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "error.h"
#include "custom_string.h"

FILE *file;
Custom_string *custom_str;


void import_file_to_scan(FILE *file);

int process_identificator(Custom_string *string, Token *token);

int process_double_value(Custom_string *string, Token *token);

int process_integer_value(Custom_string *string, Token *token);

void declarate_custom_string(Custom_string *string);

int generate_token(Token *token);

int end_scanner(Custom_string *str , int code);