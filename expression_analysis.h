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
    E,   // * ERROR
    U   //   UNTIL
} PSA_sign;

#endif // !EXPRESSION_ANALYSIS