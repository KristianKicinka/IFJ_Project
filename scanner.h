#ifndef SCANNER_H
#define SCANNER_H 

#include <stdio.h>
#include <stdio.h>
#include "custom_string.h"

typedef enum{
   STATE_START_F = 100,
   STATE_EOL_F = 101,
   STATE_EOF_F = 102,
   STATE_LESS_THAN_F = 103,
   STATE_MORE_THAN_F = 104,
   STATE_EQUALS_F = 105,
   STATE_BACKSLASH_F = 106,
   STATE_STRING_CONCAT_F = 107,
   STATE_LINE_COMMENTARY_F = 108,
   STATE_BLOCK_COMMENT_N = 109,
   STATE_BLOCK_COMMENT_F = 110,
   STATE_END_BLOCK_COMMENT_N = 111,
   STATE_END_BLOCK_COMMENT_F = 112,
   STATE_TILDA_N = 113,
   STATE_NOT_EQUAL_F = 114,
   STATE_NUMBER_F = 115,
   STATE_MINUS = 116,
   STATE_STR_CONCATE_F = 117,
   STATE_ESCAPE_SEQ_N = 118,
   STATE_IDENT_OR_KW = 119,
   STATE_NUMBER_DOT_N = 120,
   STATE_NUMBER_EXPONENT_N = 121,
   STATE_NUMBER_EXPONENT_SIGN_N = 122,
   STATE_NUMBER_EXPONENT_NUMBER_F = 123,
   STATE_NUMBER_DEC_F = 124,
   STATE_ESC_SEQ_SLASH_N = 125,
   STATE_ESC_SEQ_NUMBER_1_N = 126,
   STATE_ESC_SEQ_NUMBER_2_N = 127,
   STATE_ESC_SEQ_FINAL = 128

   
}Fsm_states;

typedef enum{

   TYPE_IDENTIFICATOR_FUNCTION,
   TYPE_IDENTIFICATOR_VARIABLE,
   TYPE_INT_NUMBER,
   TYPE_DOUBLE_NUMBER,
   TYPE_STRING,
   TYPE_UNDEFINED,

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
   TYPE_DIVIDE_INT,                 // [ // ]

   // String operations

   TYPE_STRING_CONCAT,              // [ .. ]

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
   TYPE_COLON,                            // [ : ]
   TYPE_DOT,                              // [ . ]
   TYPE_ASSIGN,                           // [ = ]

   // KEYWORDS
   TYPE_KW_EOF,
   TYPE_KW_DO,
   TYPE_KW_ELSE,
   TYPE_KW_END,
   TYPE_KW_FUNCTION,
   TYPE_KW_GLOBAL,
   TYPE_KW_IF,
   TYPE_KW_INTEGER,
   TYPE_KW_LOCAL,
   TYPE_KW_NIL,
   TYPE_KW_NUMBER,
   TYPE_KW_REQUIRE,
   TYPE_KW_RETURN,
   TYPE_KW_STRING,
   TYPE_KW_THEN,
   TYPE_KW_WHILE

}Token_type;

typedef union{
   Custom_string *custom_string;
   int integer_value;
   double double_value;
   int row_number;
   
}Token_info;
 
typedef struct token_t {
   Token_type type_of_token;
   Token_info token_info;
}Token;



void process_identificator(Custom_string *string, Token *token, char character);

void process_double_value(Custom_string *string, Token *token);

void process_integer_value(Custom_string *string, Token *token);

int generate_token(Token *token, Custom_string *string);

#endif // !SCANNER_H

 


 