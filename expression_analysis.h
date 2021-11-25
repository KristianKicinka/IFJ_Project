#ifndef EXPRESSION_ANALYSIS
#define EXPRESSION_ANALYSIS

#include <stdio.h>
#include <stdlib.h>

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
    DOLAR = 16     //  $$
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
    LENG_E,        // E -> # E
    E_MUL_E,       // E -> E * E
    E_DIV_E,       // E -> E / E
    E_DDIV_E,      // E -> E // E
    E_PLUS_E,      // E -> E + E
    E_MINUS_E,     // E -> E - E
    E_CONC_E,      // E -> E .. E
    E_LESS_E,      // E -> E < E
    E_MORE_E,      // E -> E > E
    E_LESSOE_E,    // E -> E <= E
    E_MOREOE_E,    // E -> E >= E
    E_EQ_E,        // E -> E = E
    E_NOTEQ_E,     // E -> E ~= E
    OPERAND,       // E -> i
    LBRAC_E_RBRAC, // E -> (E)
    INVALID        // Non existing rule
} PSA_rules;

#endif // !EXPRESSION_ANALYSIS