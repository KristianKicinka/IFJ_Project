#ifndef _SYNTACTIC_ANALYZE_H
#define _SYNTACTIC_ANALYZE_H

#include "error.h"
#include "scanner.h"
#include "stack.h"
#include "LL_table.h"
//#include "scanner.c"

typedef enum{
    op_plus,  //+
    op_minus, //-
    op_multiplication,  //*,
    op_division,    // /
    op_less, // <
    op_greater, //>
    op_equal, //=
    op_lessorequal, //<=
    op_greaterorequal, //>=
    op_leftbracket, // (
    op_rightbracket, // )
} operands;

typedef enum{
    FUNCTION_ARGUMENT_INT = 1,
    FUNCTION_ARGUMETN_DOUBLE = 2,
    FUNCTION_ARGUMENT_IDENTIFICATOR = 3,
    FUNCTION_ARGUMENT_NUMBER = 4,
    FUNCTION_ARGUMEMNT_STRING = 5,
} function_arguments;

typedef struct Function_Args_t{
    function_arguments function_arguments;
    struct Function_Args_t *next_function_argument;
   

} Function_Args_t;

typedef struct Function_Declaration_t{
    char *function_name;
    struct Function_Args_t *arguments;
    int number_of_args;
    struct Function_Declaration_t *next;

} *Function_Declaration_ptr;

typedef struct{
    Function_Declaration_ptr prttofirst;
    Function_Declaration_ptr ptrtolast;
} LList_Function_t;

#endif