#ifndef SCANNER_H
#define SCANNER_H 

#include <stdio.h>
#include <stdio.h>
#include "custom_string.h"

typedef enum{
   //TO DO 
}Fsm_states;

typedef enum{

   TYPE_IDENTIFICATOR,
   TYPE_KEYWORD,
   TYPE_INT_NUMBER,
   TYPE_DOUBLE_NUMBER,
   TYPE_STRING,

   // Logical operators

   TYPE_EKV,                        // [ == ]
   TYPE_NEKV,                       // [ != ]
   TYPE_LTHEN,                      // [ < ]
   TYPE_GTHEN,                      // [ > ]
   TYPE_GEKV,                       // [ >= ]
   TYPE_LEKV,                       // [ <= ]

   // Aritmetic operators

   TYPE_PLUS,                       // [ + ]
   TYPE_MINUS,                      // [ - ]
   TYPE_MULTIPLICATE,               // [ * ]
   TYPE_DIVIDE,                     // [ / ]

   // Special symbols

   TYPE_SEMICOLON,                        // [ ; ]
   TYPE_RIGHT_ROUND_BRACKET,              // [ ) ]
   TYPE_LEFT_ROUND_BRACKET,               // [ ( ]
   TYPE_COMMA,                            // [ , ]
   TYPE_RIGHT_SQUARE_BRACKET,             // [ ] ]
   TYPE_LEFT_SQUARE_BRACKET,              // [ [ ]
   TYPE_RIGHT_CURLY_BRACKET,              // [ } ]
   TYPE_LEFT_CURLY_BRACKET,               // [ { ]
   TYPE_HASHTAG,                          // [ # ]


}Token_type;

typedef enum{
   KW_DO,
   KW_ELSE,
   KW_END,
   KW_FUNCTION,
   KW_GLOBAL,
   KW_IF,
   KW_INTEGER,
   KW_LOCAL,
   KW_NIL,
   KW_NUMBER,
   KW_REQUIRE,
   KW_RETURN,
   KW_STRING,
   KW_THEN,
   KW_WHILE

}Key_word;
 
typedef union{
   Custom_string *custom_string;
   Key_word key_word;
   int integer_value;
   double double_value;
   
}Token_info;
 
typedef struct token_t {
   Token_type type_of_token;
   Token_info token_info;
}Token;


void import_file_to_scan(FILE *file);

void process_identificator(Custom_string *string, Token *token);

void process_double_value(Custom_string *string, Token *token);

void process_integer_value(Custom_string *string, Token *token);

void declarate_custom_string(Custom_string *string);

int generate_token(Token *token);

#endif // !SCANNER_H

 


 