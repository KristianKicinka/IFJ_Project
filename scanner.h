#ifndef SCANNER_H
#define SCANNER_H 

#include <stdio.h>
#include "custom_string.h"

typedef enum{
   //TO DO 
}Fsm_states;

typedef enum{
   //TO DO
}Token_type;

typedef enum{
   //TO DO 
}Key_word;
 
typedef union{
   Custom_string *custom_string;
   unsigned int integer_value;
   unsigned double double_value;
   Key_word key_word;

}Token_info;
 
typedef struct token_t {
   Token_type type_of_token;
   Token_info token_info;
}Token;

#endif // !SCANNER_H

 


 