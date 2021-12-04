#ifndef EXPRESSION_ANALYSIS
#define EXPRESSION_ANALYSIS

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "lexical_analysis.h"

#define TABLE 17 // Size of the table

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

int precedence_analysis(Token token);

void stack_free_return(Error_type error);

#endif // !EXPRESSION_ANALYSIS