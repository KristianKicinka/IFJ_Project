#ifndef ENUMS
#define ENUMS

#include "lexical_analysis.h"
#include "symtable.h"

typedef enum 
{
    PLUS = 0,      //  +
    MINUS = 1,     //  -
    MUL = 2,       //  *
    DIV = 3,       //  /
    DDIV = 4,      //  //
    CONC = 5,      //  ..
    LENG = 6,      //  #
    LESS = 7,      //  <
    LESSOE = 8,    //  <=
    MORE = 9,      //  >
    MOREOE = 10,   //  >=
    EQ = 11,       //  ==
    NOTEQ = 12,    //  ~=
    ID = 13,       //  IDENTIFIER
    LBRACKET = 14, //  (
    RBRACKET = 15, //  )
    DOLLAR = 16,     //  $$

    EXPRESSION,
    EXPRESSION_S,   // string
    EXPRESSION_N,   // number
    EXPRESSION_I,   // integer
    PUSH_SYMBOL
} PSA_symbol;

typedef enum
{
    PA, // < PUSH ADD
    R,  // > REDUCE
    P,  // = PUSH
    E,  // * ERROR
    U   //   UNTIL
} PSA_sign;

typedef enum
{
    LENG_E,        // E -> # E      string
    E_MUL_E,       // E -> E * E    int, num
    E_DIV_E,       // E -> E / E    int/int -> num, num
    E_DDIV_E,      // E -> E // E   num//num -> int, int
    E_PLUS_E,      // E -> E + E    int, num
    E_MINUS_E,     // E -> E - E    int, num
    E_CONC_E,      // E -> E .. E   string
    E_LESS_E,      // E -> E < E    string, int, num
    E_MORE_E,      // E -> E > E    string, int, num
    E_LESSOE_E,    // E -> E <= E   string, int, num
    E_MOREOE_E,    // E -> E >= E   string, int, num
    E_EQ_E,        // E -> E = E    string, int, num
    E_NOTEQ_E,     // E -> E ~= E   string, int, num
    OPERAND,       // E -> i        string, int, num
    LBRAC_E_RBRAC, // E -> (E)      string, int, num
    INVALID        // Non existing rule
} PSA_rules;

typedef struct syntactic_data_t{
    symbol_table_t global_table;
    symbol_table_t local_table;

    Token token;

    token_list list_of_tokens;

    Custom_string my_string;

    //Additional_info info;
    
    Symbol_type type_of_symbol;

    int parameter_index; //index 0 je prvý parameter, index -1 je bez parametrov
    //int return_type_index; //index 0 je prvý return, index -1 je bez returnov
    int label_index;

    bool in_function;
    bool in_statement;
    bool in_while;
    bool in_if;
    bool in_declaration;

    table_item_t *current_item;
    table_item_t *current_item_var;

}syntactic_data_t;

#endif