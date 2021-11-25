#ifndef SCANNER_H
#define SCANNER_H 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "custom_string.h"

#define COUNT_OF_KEYWORDS 15

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
   STATE_ESC_SEQ_FINAL = 128,
   STATE_ESC_SEQ_WHITE = 129

   
}Fsm_states;

typedef enum{

   // KEYWORDS
   TYPE_KW_REQUIRE = 0,
   TYPE_KW_DO = 1,
   TYPE_KW_ELSE = 2,
   TYPE_KW_END = 3,
   TYPE_KW_FUNCTION = 4,
   TYPE_KW_GLOBAL = 5,
   TYPE_KW_IF = 6,
   TYPE_KW_LOCAL = 7,
   TYPE_KW_NIL = 8,
   TYPE_KW_NUMBER = 9,
   TYPE_KW_RETURN = 10,
   TYPE_KW_THEN = 11,
   TYPE_KW_WHILE = 12,
   TYPE_SEMICOLON = 13,                        // [ ; ]
   TYPE_RIGHT_ROUND_BRACKET = 14,              // [ ) ]
   TYPE_LEFT_ROUND_BRACKET = 15,               // [ ( ]
   TYPE_COMMA = 16,                            // [ , ]
   TYPE_COLON = 17,                            // [ : ]
   TYPE_EKV = 18,                              // [ == ]
   TYPE_KW_EOF = 19,                           
   TYPE_IDENTIFICATOR_VARIABLE = 20,
   TYPE_IDENTIFICATOR_FUNCTION = 21,

   //KW
   TYPE_KW_INTEGER = 22,
   TYPE_KW_STRING = 23,                //string type string
   
   //CONST
   TYPE_STRING = 24,                   //string const "abcd"
   TYPE_INT_NUMBER = 25,
   TYPE_DOUBLE_NUMBER = 26,

   // Aritmetic operators
   TYPE_PLUS = 27,                       // [ + ]
   TYPE_MINUS = 28,                      // [ - ]
   TYPE_MULTIPLICATE = 29,               // [ * ]
   TYPE_DIVIDE = 30,                     // [ / ]
   TYPE_DIVIDE_INT = 31,                 // [ // ]

   // String operations
   TYPE_STRING_CONCAT = 32,              // [ .. ]

   // Logical operators
   TYPE_LTHEN = 33,                      // [ < ]
   TYPE_LEKV = 34,                       // [ <= ]
   TYPE_GTHEN = 35,                      // [ > ]
   TYPE_GEKV = 36,                       // [ >= ]
   TYPE_NEKV = 37,                       // [ != ]

   //END of Terminals = total: 38
   
   // Special symbols
   TYPE_UNDEFINED,
   TYPE_RIGHT_SQUARE_BRACKET,             // [ ] ]
   TYPE_LEFT_SQUARE_BRACKET,              // [ [ ]
   TYPE_RIGHT_CURLY_BRACKET,              // [ } ]
   TYPE_LEFT_CURLY_BRACKET,               // [ { ]
   TYPE_HASHTAG,                          // [ # ]
 
   TYPE_DOT,                              // [ . ]
   TYPE_ASSIGN                            // [ = ]

}Token_type;

typedef union{
   Custom_string *custom_string;
   int integer_value;
   double double_value;
}Token_info;
 
typedef struct token_t {
   Token_type type_of_token;
   Token_info token_info;
   int row_number;
   bool has_str_val;
}Token;



int process_identificator(Custom_string *string, Token *token, char character);

int process_double_value(Custom_string *string, Token *token);

int process_integer_value(Custom_string *string, Token *token);

int generate_token(Token *token, Custom_string *string);


#endif // !SCANNER_H

 


 