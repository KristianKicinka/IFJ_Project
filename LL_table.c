#include "LL_table.h"

const rule_t RULES[NUMBER_OF_RULES]={
  /*                                             počet derivácii na pravej strane | prva derivacia                                              druha derivacia                             tretia derivacia                            štvrtá derivácia                        piata derivácia                                    šiesta derivácia                             siedma derivácia                    ôsma derivácia              */
  /*  0 - prolog_nt -> <kw_require> <string_const> start */                              
                                                        {.number_of_derivations=3, {{.isterminal=true,  .term=TYPE_KW_REQUIRE},             {.isterminal=true, .term=TYPE_STRING},                      {.isterminal=false, .nterm=NT_START}}},
  /*  1 - start_nt -> func_call_nt start_nt */          {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_START}}},
  /*  2 - start_nt -> func_dec_nt start_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_DEC},                {.isterminal=false, .nterm=NT_START}}},
  /*  3 - start_nt -> func_nt start_nt */               {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC},                    {.isterminal=false, .nterm=NT_START}}},
  /*  4 - start_nt -> end           */                  {.number_of_derivations=1, {{.isterminal=false, .nterm=TYPE_KW_END}}},
  /*  code_nt -> eps */             
  /*  5 - code_nt -> while_nt code_nt */                {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_WHILE},                   {.isterminal=false, .nterm=NT_CODE}}},
  /*  6 - code_nt -> if_nt code_nt */                   {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_IF},                      {.isterminal=false, .nterm=NT_CODE}}},    
  /*  7 - code_nt -> func_call_nt code_nt */            {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_CODE}}},
  /*  8 - code_nt -> return_nt code_nt */               {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_RETURN},                  {.isterminal=false, .nterm=NT_CODE}}},
  /*  9 - code_nt -> assign_existing_nt code_nt */      {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_ASSIGN_EXISTING},         {.isterminal=false, .nterm=NT_CODE}}},
  /* 10 - code_nt -> assign_new_nt code_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_ASSIGN_NEW},              {.isterminal=false, .nterm=NT_CODE}}},
  /* 11 - code_if_nt -> code_nt code_if_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_CODE},                    {.isterminal=false, .nterm=NT_CODE_IF}}},                
  /* 12 - while_nt -> <kw_while> expression_nt <kw_do> code_nt <kw_end> */  
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_KW_WHILE},                {.isterminal=false, .nterm=NT_EXPRESSION},                   {.isterminal=true, .term=TYPE_KW_DO},                  {.isterminal=false, .nterm=NT_CODE},                              {.isterminal=true, .term=TYPE_KW_END}}},
  /* 13 - if_nt -> <kw_if> expression_nt <kw_then> code_nt <kw_else> code_nt <kw_end> */
                                                        {.number_of_derivations=7, {{.isterminal=true, .term=TYPE_KW_IF},                   {.isterminal=false, .nterm=NT_EXPRESSION},                   {.isterminal=true, .term=TYPE_KW_THEN},                {.isterminal=false, .nterm=NT_CODE},                              {.isterminal=true, .term=TYPE_KW_ELSE},                     {.isterminal=false, .nterm=NT_CODE},        {.isterminal=true, .term=TYPE_KW_END}}},
  /* 14 - func_dec -> <kw_global> <func_id> <:> <kw_function> <(> param_nt <)> double_dot_nt start*/
                                                        {.number_of_derivations=9, {{.isterminal=true, .term=TYPE_KW_GLOBAL},               {.isterminal=true,  .term=TYPE_IDENTIFICATOR_FUNCTION},      {.isterminal=true,  .term=TYPE_LEFT_ROUND_BRACKET},    {.isterminal=false, .nterm=NT_ARG},                               {.isterminal=true, .nterm=TYPE_RIGHT_ROUND_BRACKET},        {.isterminal=false, .nterm=NT_DOUBLE_DOT},  {.isterminal=false, .nterm=NT_CODE},    {.isterminal=true, .term=TYPE_KW_END}, {.isterminal=false, .nterm=NT_START}}},
  /* 15 - double_dot_nt -> <:> datatype double_dots_nt*/{.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COLON},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_DOUBLE_DOTS}}},
  /* 16 - double_dots_nt -> , datatype double_dots_nt */{.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_DOUBLE_DOTS}}},                                                                                                 
  /* 17 - param_nt -> datatype params_nt */             {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_DATA_TYPE},               {.isterminal=false, .nterm=NT_PARAMS}}},
  /* 18 - params_nt -> , datatype params_nt */          {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_PARAMS}}},
  /* 19 - check_eof_nt -> end */                        {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_END}}},
  /* 20 - check_eof_nt -> start   */                    {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_START}}},
  /* 21 - func_nt -> <kw_function> <func_id> <(> arg_nt <)> double_dot_nt code_nt <kw_end>*/
                                                        {.number_of_derivations=8, {{.isterminal=true, .term=TYPE_KW_FUNCTION},             {.isterminal=true, .term=TYPE_IDENTIFICATOR_FUNCTION},       {.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET},     {.isterminal=false, .nterm=NT_ARG},                               {.isterminal=true, .term=TYPE_RIGHT_ROUND_BRACKET},     {.isterminal=false, .nterm=NT_DOUBLE_DOT},  {.isterminal=false, .nterm=NT_CODE},   {.isterminal=true, .term=TYPE_KW_END}}},
  /*O22 - arg_nt -> <id> <:> datatype argument_nt  */   {.number_of_derivations=4, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=true, .term=TYPE_COLON},                        {.isterminal=false, .nterm=NT_DATA_TYPE},              {.isterminal=false, .nterm=NT_ARGUMENT}}},
  /*O23 - argument_nt -> , <id> <:> datatype argument_nt */  
                                                        {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=true, .term=TYPE_COLON},                        {.isterminal=false, .nterm=NT_DATA_TYPE}}},  
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=true, .term=TYPE_COLON},                        {.isterminal=false, .nterm=NT_DATA_TYPE},              {.isterminal=true, .term=TYPE_COMMA},                             {.isterminal=false, .nterm=NT_ARGUMENT}}},
  /*O24 - return_nt -> <KW_RETURN> check_ret_params_nt*/{.number_of_derivations=2, {{.isterminal=true, .term=TYPE_KW_RETURN},               {.isterminal=false, .nterm=NT_CHECK_RET_PARAMS}}}, 
  /*O25 - check_ret_params_nt -> value returns_nt */    {.number_of_derivations=3, {{.isterminal=true, .nterm=VALUS},              {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_RETURNS}}},
  /*O26 - returns_nt -> , value returns_nt          */  {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_SEMICOLON},               {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_RETURNS}}},
  /* 27 - func_call_nt -> <func_id> <(> call_param_nt <)> check_eof_nt*/
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_FUNCTION},  {.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET},           {.isterminal=false, .nterm=NT_CALL_PARAM},             {.isterminal=true, .term=TYPE_RIGHT_ROUND_BRACKET},             {.isterminal=false, .nterm=NT_CHECK_EOF}}},
  /* 28 - call_param_nt -> value call_params_nt */      {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_VALUE},                   {.isterminal=false, .nterm=NT_CALL_PARAMS}}},
  /* 29 - call_params_nt -> , value call_params_nt */   {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_CALL_PARAMS}}},
  /* 30 - assign_existing_nt -> to_assign_nt <=> assign_value_nt */ 
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_TO_ASSIGN},               {.isterminal=true, .term=TYPE_EKV},                          {.isterminal=false, .nterm=NT_ASSIGN_VALUE}}},                                             
  /* 31 - to_assign_nt -> <id> to_assign2_nt */         {.number_of_derivations=2, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=NT_TO_ASSIGN2}}},
  /* 32 - to_assign2_nt -> , <id> to_assign2_nt */      {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},       {.isterminal=false, .nterm=NT_TO_ASSIGN2}}},
  /* 33 - assign_value_nt -> value assign_values_nt */  {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_VALUE},                   {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},  
  /* 34 - assign_value_nt -> func_call_nt assign_values_nt // a=foo(b) */
                                                        {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_ASSIGN_VALUE}}},
  /* 35 - assign_values_nt -> , value assign_values_nt*/{.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},         
  /* 36 - assign_values_nt -> , func_call_nt assign_values_nt */
                                                        {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_FUNC_CALL},                    {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},                                            
  /* 37 - assign_new_nt -> <kw_local> <id> <:> datatype <=> assign_nt */
                                                        {.number_of_derivations=6, {{.isterminal=true, .term=TYPE_KW_LOCAL},                {.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},       {.isterminal=true, .term=NT_DOUBLE_DOT},               {.isterminal=false, .nterm=NT_DATA_TYPE},                           {.isterminal=true, .term=TYPE_EKV},             {.isterminal=false, .nterm=NT_ASSIGN}}}, 
  /* 38 - assign_nt -> value */                         {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_VALUE}}}, 
  /* 39 - assign_nt -> func_call_nt */                  {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_FUNC_CALL}}},
  /* VALUES, DATATYPES, ASSIGNING VALUES */
  /* 40 - value-> <int_const> */                        {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_INT_NUMBER}}},
  /* 41 - value-> <number_const> */                     {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_DOUBLE_NUMBER}}},
  /* 42 - value-> <string_const> */                     {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_STRING}}},
  /* 43 - value-> <id>  */                              {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},                                     
  /* 44 - assval_nt-> <int> */                          {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},
  /* 45 - assval_nt-> <number> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NUMBER}}},
  /* 46 - assval_nt-> <string> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_STRING}}},
  /* 47 - assval_nt-> <id> */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},
  /* 48 - assval_nt-> <nil> */                          {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NIL}}},                                                        
  /* 49 - datatype->int */                              {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_INTEGER}}},
  /* 50 - datatype->number */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NUMBER}}},
  /* 51 - datatype->string */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_STRING}}},
  /*E52 - end -> <token_eof_t> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_EOF}}}  
  /* EXPRESSIONS */ 
  /* 52 - expression_nt -> (expression_nt) TODO */          


};

int LLtable[NUMBER_OF_NTERMS][NUMBER_OF_TERMS]={
/*                      REQUIRE  DO  ELSE  END  FUNCTION  GLOBAL  IF  LOCAL  NIL  NUMBER  RETURN  THEN  WHILE  SEMICOLN  R_BRACKET L_BRACKET  COMMA  DOUBLEDOT  EQUAL  EOF   ID  FUNC_ID  INT  STRING   STRING_CONST  INT_CONST  NUMBER_CONST    PLUS    MINUS    MULTIPLY  DIV  DOUBLEDIV   CONCAT   LESS   LE   GREATER   GE   NOTEQUAL   $ */
/*prolog*/              {  0,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, //1     */
/*value_nt*/            { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  42,    SE,    SE,   SE,        SE,          40,         41,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assval_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   48,   45,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  47,    SE,    44,   46,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, 
/*datatype_nt*/         { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   50,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    49,   51,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*expression_n   TODO*/ { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*func_dec*/            { SE,    SE,  SE,   SE,    SE,      14,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*param_nt*/            { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   17,     SE,    SE,    SE,     SE,       EPS,      SE,       17?,     SE,      SE,   SE,  SE,    SE,    17,   17,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, 
/*params_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       18,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*func_nt*/             { SE,    SE,  SE,   SE,    21,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*arg_nt*/              { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       SE,      SE,      SE,   SE,  22,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*argument_nt  CHECK*/  { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       23,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*ret_arg_nt   VOID*/   { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*ret_args_nt  VOID*/   { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*code_nt*/             { SE,    SE,  SE,  EPS,    SE,      SE,    5,    9,   SE,   SE,      7,    SE,     4,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   8,     6,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},        /*   }
/*return_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     24,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*check_ret_params_nt*/ {}
/*returns_nt not ready*/{ SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,  SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},

/*func_call_nt */
/*call_param_nt*/
/*call_params_nt*/
/*assign_existing_nt*/
/*to_assign_nt*/
/*assign_value_nt*/
/*assign_values_nt*/
/*to_assign2_nt*/
/*assign_new_nt*/
/*assign_nt*/
/*while_nt*/
/*if_nt*/
/*start*/
/*double_dot_nt*/
/*double_dots_nt*/
/*check_eof_nt*/
/*code_if_nt*/
/*end_nt*/

};

