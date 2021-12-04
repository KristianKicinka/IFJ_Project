#include "LL_table.h"
#include "nterms.h"
//F - fixed
//R - need repair 
//C - check rule twice
//A - need to be add to LLtable
const rule_t RULES[NUMBER_OF_RULES]={
  /*                                             počet derivácii na pravej strane | prva derivacia                                              druha derivacia                             tretia derivacia                            štvrtá derivácia                        piata derivácia                                    šiesta derivácia                             siedma derivácia                    ôsma derivácia              */
  /*  0 - prolog_nt -> <kw_require> <string_const> start */                              
                                                        {.number_of_derivations=3, {{.isterminal=true,  .term=TYPE_KW_REQUIRE},             {.isterminal=true, .term=TYPE_STRING},                      {.isterminal=false, .nterm=NT_START}}},
  /*  1 - start_nt -> func_call_nt start_nt */          {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_START}}},
  /*  2 - start_nt -> func_dec_nt start_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_DEC},                {.isterminal=false, .nterm=NT_START}}},
  /*  3 - start_nt -> func_nt start_nt */               {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC},                    {.isterminal=false, .nterm=NT_START}}},
  /*  4 - start_nt -> end           */                  {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_END}}},
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
  /* 13 - if_nt -> <kw_if> expression_nt <kw_then> code_if_nt <kw_else> code_nt <kw_end> */
                                                        {.number_of_derivations=7, {{.isterminal=true, .term=TYPE_KW_IF},                   {.isterminal=false, .nterm=NT_EXPRESSION},                   {.isterminal=true, .term=TYPE_KW_THEN},                {.isterminal=false, .nterm=NT_CODE_IF},                           {.isterminal=true, .term=TYPE_KW_ELSE},                    {.isterminal=false, .nterm=NT_CODE},        {.isterminal=true, .term=TYPE_KW_END}}},
  /* 14 - func_dec -> <kw_global> <func_id> <:> <kw_function> <(> param_nt <)> double_dot_nt start*/
                                                        {.number_of_derivations=9, {{.isterminal=true, .term=TYPE_KW_GLOBAL},               {.isterminal=true,  .term=TYPE_IDENTIFICATOR_VARIABLE},      {.isterminal=true,  .term=TYPE_COLON},                 {.isterminal=true, .term=TYPE_KW_FUNCTION},                       {.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET},         {.isterminal=false, .nterm=NT_PARAM},      {.isterminal=true, .term=TYPE_RIGHT_ROUND_BRACKET},    {.isterminal=false, .nterm=NT_DOUBLE_DOT},     {.isterminal=false, .nterm=NT_START}}},
  /* 15 - double_dot_nt -> <:> datatype double_dots_nt*/{.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COLON},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_DOUBLE_DOTS}}},
  /*      double_dot_nt -> eps  */
  /* 16 - double_dots_nt -> , datatype double_dots_nt */{.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_DOUBLE_DOTS}}},                                                                                                 
  /* 17 - param_nt -> datatype params_nt */             {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_DATA_TYPE},               {.isterminal=false, .nterm=NT_PARAMS}}},
  /* 18 - params_nt -> , datatype params_nt */          {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_DATA_TYPE},                    {.isterminal=false, .nterm=NT_PARAMS}}},
  /* 19 - check_eof_nt -> end */                        {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_END}}},
  /* 20 - check_eof_nt -> start   */                    {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_START}}},
  /*A21 - func_nt -> <kw_function> <func_id> <(> arg_nt <)> double_dot_nt code_nt <kw_end> check_eof_nt */
                                                        {.number_of_derivations=9, {{.isterminal=true, .term=TYPE_KW_FUNCTION},             {.isterminal=true, .term=TYPE_IDENTIFICATOR_FUNCTION},       {.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET},     {.isterminal=false, .nterm=NT_ARG},                               {.isterminal=true, .term=TYPE_RIGHT_ROUND_BRACKET},     {.isterminal=false, .nterm=NT_DOUBLE_DOT},  {.isterminal=false, .nterm=NT_CODE},   {.isterminal=true, .term=TYPE_KW_END}, {.isterminal=false, .nterm=NT_CHECK_EOF}}},
  /*F22 - arg_nt -> <id> <:> datatype argument_nt  */   {.number_of_derivations=4, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=true, .term=TYPE_COLON},                        {.isterminal=false, .nterm=NT_DATA_TYPE},              {.isterminal=false, .nterm=NT_ARGUMENT}}},
  /*F23 - argument_nt -> , <id> <:> datatype argument_nt */  
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},       {.isterminal=true, .term=TYPE_COLON},                  {.isterminal=false, .nterm=NT_DATA_TYPE}, {.isterminal=false, .nterm=NT_ARGUMENT}}},  
  
  /*F24 - return_nt -> <KW_RETURN> check_ret_params_nt*/{.number_of_derivations=2, {{.isterminal=true, .term=TYPE_KW_RETURN},               {.isterminal=false, .nterm=NT_CHECK_RET_PARAMS}}}, 
  /*F25 - check_ret_params_nt -> value returns_nt */    {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_VALUE},                   {.isterminal=false, .nterm=NT_RETURNS}}},                      
  /*F26 - returns_nt -> , value returns_nt          */  {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_RETURNS}}},
  /* 27 - func_call_nt -> <func_id> <(> call_param_nt <)> check_eof_nt*/
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_FUNCTION},  {.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET},           {.isterminal=false, .nterm=NT_CALL_PARAM},             {.isterminal=true, .term=TYPE_RIGHT_ROUND_BRACKET},             {.isterminal=false, .nterm=NT_CHECK_EOF}}},
  /* 28 - call_param_nt -> value call_params_nt */      {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_VALUE},                   {.isterminal=false, .nterm=NT_CALL_PARAMS}}},
  /* 29 - call_params_nt -> , value call_params_nt */   {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_VALUE},                        {.isterminal=false, .nterm=NT_CALL_PARAMS}}},
  /* 30 - assign_existing_nt -> to_assign_nt <=> assign_value_nt */ 
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_TO_ASSIGN},               {.isterminal=true, .term=TYPE_ASSIGN},                          {.isterminal=false, .nterm=NT_ASSIGN_VALUE}}},                                             
  /* 31 - to_assign_nt -> <id> to_assign2_nt */         {.number_of_derivations=2, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=false, .nterm=NT_TO_ASSIGN2}}},
  /* 32 - to_assign2_nt -> , <id> to_assign2_nt */      {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},       {.isterminal=false, .nterm=NT_TO_ASSIGN2}}},
  /* 33 - assign_value_nt -> expression_nt assign_values_nt */  {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_EXPRESSION},              {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},  
  /*AAA   assign_value_nt -> value assign_values_nt REPLACED BY ABOVE */
  /* 34 - assign_value_nt -> func_call_nt assign_values_nt // a=foo(b) */
 
                                                        {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_ASSIGN_VALUE}}},
  /*F35 - assign_values_nt -> , assign_from*/           {.number_of_derivations=2, {{.isterminal=true, .term=TYPE_COMMA},                   {.isterminal=false, .nterm=NT_ASSIGN_FROM}}},                             
  /*F36 - assign_from -> value assign_values_nt */      {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_VALUE},                    {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},                                                   
  /*AAA   assign_from -> expression_nt assign_values_nt REPLACED BY ABOVE */
  /*F37 - assign_from -> func_call_nt assign_values_nt*/{.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},               {.isterminal=false, .nterm=NT_ASSIGN_VALUES}}},
  /* 38 - assign_new_nt -> <kw_local> <id> <:> datatype optional_ekv_nt */
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_KW_LOCAL},                {.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},       {.isterminal=true, .term=TYPE_COLON},                 {.isterminal=false, .nterm=NT_DATA_TYPE},                         {.isterminal=false, .nterm=NT_OPTIONAL_EKV}}}, 
  /* 39 - assign_nt -> expression_nt */                 {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_EXPRESSION}}}, 
  /*AA2 - assign_nt -> value MAYBE? REPLACED BY ABOVE*/
  /* 40 - assign_nt -> func_call_nt */                  {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_FUNC_CALL}}},
  /* VALUES, DATATYPES, ASSIGNING VALUES */
  /* 41 - value-> <int_const> */                        {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_INT_NUMBER}}},
  /* 42 - value-> <number_const> */                     {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_DOUBLE_NUMBER}}},
  /* 43 - value-> <string_const> */                     {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_STRING}}},
  /* 44 - value-> <id>  */                              {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},                                     
  /* 45 - assval_nt-> <int> */                          {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},
  /* 46 - assval_nt-> <number> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NUMBER}}},
  /* 47 - assval_nt-> <string> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_STRING}}},
  /* 48 - assval_nt-> <id> */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE}}},
  /* 49 - assval_nt-> <nil> */                          {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NIL}}},                                                        
  /* 50 - datatype->int */                              {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_INTEGER}}},
  /* 51 - datatype->number */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NUMBER}}},
  /* 52 - datatype->string */                           {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_STRING}}},
  /*E53 - end -> <token_eof_t> */                       {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_EOF}}},  
  /*T24 unknown rule*/                               /* {.number_of_derivations=5, {{.isterminal=true, .term=TYPE_IDENTIFICATOR_VARIABLE},  {.isterminal=true, .term=TYPE_COLON},                        {.isterminal=false, .nterm=NT_DATA_TYPE},              {.isterminal=true, .term=TYPE_COMMA},                             {.isterminal=false, .nterm=NT_ARGUMENT}}}*/
  /* EXPRESSIONS */ 
  /* 54 - expression_nt -> (expression_nt)*/            {.number_of_derivations=3, {{.isterminal=true, .term=TYPE_LEFT_ROUND_BRACKET}, {.isterminal=false, .nterm=NT_EXPRESSION}, {.nterm=true, .term=TYPE_RIGHT_ROUND_BRACKET}}},
  /* 55 - expression_nt -> value */                     {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_VALUE}}},
  /* 56 - expression_nt -> expression_nt + expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_PLUS}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 57 - expression_nt -> expression_nt - expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_MINUS}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 58 - expression_nt -> expression_nt * expression_nt */ 
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_MULTIPLICATE}, {.isterminal=false, .nterm=NT_EXPRESSION}}},            
  /* 59 - expression_nt -> expression_nt / expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_DIVIDE}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 60 - expression_nt -> expression_nt // expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_DIVIDE_INT}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 61 - expression_nt -> expression_nt .. expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_STRING_CONCAT}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 62 - expression_nt -> # expression_nt */           {.number_of_derivations=2, {{.isterminal=true, .term=TYPE_HASHTAG}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 63 - expression_nt -> expression_nt < expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_LTHEN}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 64 - expression_nt -> expression_nt <= expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_LEKV}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 65 - expression_nt -> expression_nt > expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_GTHEN}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 66 - expression_nt -> expression_nt >= expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_GEKV}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 67 - expression_nt -> expression_nt == expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_EKV}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
  /* 68 - expression_nt -> expression_nt ~= expression_nt */
                                                        {.number_of_derivations=3, {{.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=TYPE_NEKV}, {.isterminal=false, .nterm=NT_EXPRESSION}}},
 /* zatial iba pre RETURN, premysliet co doplnit */
 /* LAST ADDED 69 - check_eof_nt -> code_nt        */   {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_CODE}}}, 
 /* LAST ADDED 70 - value -> <nil>                */    {.number_of_derivations=1, {{.isterminal=true, .term=TYPE_KW_NIL}}},
 /* 71 - optional_ekv_nt -> <=> assign_nt */            {.number_of_derivations=2, {{.isterminal=true, .term=TYPE_ASSIGN},     {.isterminal=false, .nterm=NT_ASSIGN}}},   
 /* 72 - optional_ekv_nt -> code_nt */                  {.number_of_derivations=1, {{.isterminal=false, .nterm=NT_CODE}}},
};

int LLtable[NUMBER_OF_NTERMS][NUMBER_OF_TERMS]={
/*                      REQUIRE  DO  ELSE  END  FUNCTION  GLOBAL  IF  LOCAL  NIL  NUMBER  RETURN  THEN  WHILE  SEMICOLN  R_BRACKET L_BRACKET  COMMA  DOUBLEDOT  ASSIGN  EOF   ID  FUNC_ID  INT  STRING   STRING_CONST  INT_CONST  NUMBER_CONST    PLUS    MINUS    MULTIPLY  DIV  DOUBLEDIV   CONCAT   LESS   LE   GREATER   GE   NOTEQUAL  EQUAL $ */
/*prolog*/              {  0,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, //1  
/*value_nt*/            { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   44,    SE,    SE,   SE,        43,          41,         42,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assval_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   49,   46,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   48,    SE,    45,   47,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, 
/*datatype_nt*/         { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   51,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    50,   52,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*expression_nt*/       { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      54,       SE,      SE,      SE,   SE,   55,    SE,    SE,   SE,        55,          55,         55,          56,      57,       58,     59,    60,        61,     62,   63,     64,    65,     68,     67},
/*func_dec*/            { SE,    SE,  SE,   SE,    SE,      14,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*param_nt*/            { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   17,     SE,    SE,    SE,     SE,       EPS,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    17,   17,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE}, 
/*params_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       18,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*func_nt*/             { SE,    SE,  SE,   SE,    21,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*arg_nt*/              { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       SE,      SE,      SE,   SE,   22,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*argument_nt       */  { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       23,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*ret_arg_nt   VOID*/   { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*ret_args_nt  VOID*/   { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*code_nt*/             { SE,    SE, EPS,  EPS,    SE,      SE,    6,   10,   SE,   SE,      8,    SE,     5,     SE,        SE,      SE,       SE,      SE,      SE,   SE,    9,     7,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},       
/*return_nt add EPS*/   { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     24,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,         EPS,     EPS,      EPS,    EPS,   EPS,       EPS,    EPS,  EPS,    EPS,   EPS,     SE,     SE},
/*check_ret_params_ntE*/{ SE,    SE, EPS,  EPS,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,    SE,  25,    SE,    SE,   SE,        25,          25,         25,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*returns_nt   EPS?*/   { SE,    SE, EPS,  EPS,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       26,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*func_call_nt */       { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    27,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*call_param_nt*/       { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       SE,      SE,      SE,   SE,   28,    SE,    SE,   SE,        28,          28,         28,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*call_params_nt*/      { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,       EPS,      SE,       29,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assign_existing_nt*/  { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   30,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*to_assign_nt*/        { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   31,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assign_value_nt*/     { SE,    SE,  SE,  EPS,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   33,    34,    SE,   SE,        33,          33,         33,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assign_values_nt*/    { SE,   EPS,  SE,  EPS,    SE,      SE,  EPS,  EPS,   SE,   SE,     24,    SE,   EPS,     SE,        SE,      SE,       35,      SE,      SE,   SE,  EPS,   EPS,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assign_from_nt*/      { SE,    SE,  SE,  EPS,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,   EPS,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   36,    37,    SE,   SE,        36,          36,         36,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*to_assign2_nt*/       { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       32,      SE,     EPS,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,    EPS},
/*assign_new_nt*/       { SE,    SE,  SE,   SE,    SE,      SE,   SE,   38,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*assign_nt*/           { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   70,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   39,    40,    SE,   SE,        39,          39,         39,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*while_nt*/            { SE,    SE,  SE,   SE,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    12,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*if_nt*/               { SE,    SE,  SE,   SE,    SE,      SE,   13,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*start*/               { SE,    SE,  SE,    4,     3,       2,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,    4,   SE,     1,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*double_dot_nt E*/     { SE,   EPS,  SE,   SE,   EPS,     EPS,   SE,  EPS,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      15,      SE,  EPS,  EPS,   EPS,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*double_dots_nt*/      { SE,    SE,  SE,   SE,   EPS,     EPS,  EPS,  EPS,   SE,   SE,    EPS,    SE,    SE,     SE,        SE,      SE,       16,      SE,      SE,  EPS,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*check_eof_nt*/        { SE,    SE,  69,   19,    20,      20,   69,   69,   SE,   SE,     69,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   53,   30,    20,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*code_if_nt E*/        { SE,    SE, EPS,   SE,    SE,      SE,   11,   11,   SE,   SE,     11,    SE,    11,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   11,    11,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*end_nt*/              { SE,    SE,  SE,  EPS,    SE,      SE,   SE,   SE,   SE,   SE,     SE,    SE,    SE,     SE,        SE,      SE,       SE,      SE,      SE,   53,   SE,    SE,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     SE},
/*optinal_ekv_nt   */   { SE,    SE,  SE,  EPS,    SE,      SE,   72,   72,   70,   SE,     72,    SE,    72,     SE,        SE,      SE,       SE,      SE,      SE,   SE,   72,    72,    SE,   SE,        SE,          SE,         SE,          SE,      SE,       SE,     SE,    SE,        SE,     SE,   SE,     SE,    SE,     SE,     71},
};

int run=1;  
/*
void InitSyntacticData(syntactic_data_t *data){
    table_init(&data->global_table);
    table_init(&data->local_table);
    //token sa nemusi initovat
    data->type_of_symbol=TYPE_VARIABLE;
    data->info=IS_UNSET;
    //data->current_item=NULL;

    //najskor naplnim tuto struct 
    // if token==VARIABLE_ID 

    data->token=actualterm;
    data->type_of_symbol=TYPE_VARIABLE; //alebo type_function
    data->info=IS_DEFINED; //rozlisujem varaibles a functions
    //data->current_item=

*/
    /* POZNAMKY 
       na zaklade neterminalu budem vediet, co sa s variable deje, 
       pretoze potrebujem aj rozlisit, ci sa do premennej zapisuje, alebo z nej cita,
       a ci datovy typ kam sa zapisuje alebo cita sedi s typom premennej. 
    
       narazim na token, nie je definovany, definujem ho. Pokial zapisujem alebo citam z tokenu,
       pozrem sa ci bol definovany. Ak nie, chyba, ale pokracujem dalej.

       Generator:
       

       Global symtable bude pre funkcie,
       Lokal symtable bude pre premenne
    */

    //budem to volat takto ked mam celu struct naplnenu
/*    
    insert_symbol_variable(&data->local_table, &data->token.token_info.custom_string); //Prvotne vlozenie elementu
    set_symbol_variable_type(&data->local_table, &data->token.token_info.custom_string, TYPE_INT_NUMBER); //poslednz davam nacitany token 
    set_additional_info(&data->local_table, &data->token.token_info.custom_string, IS_LOCAL); 
    //data->current_item=search_item(&data->local_table, &data->token.token_info.custom_string);
*/
    /*ak budem potrebovat skontrolovat definiciu, alebo deklaraciu*/
    /*pristupujem cez getre*/
//}

void PrecStructInit(prec_struct_t *pointer_to_prec){
    pointer_to_prec->number_of_prec_ret_tokens=0;
    //token nema pointre, netreba initovat
}

int CheckGrammar(Stack_symbol_t stack){
    int can_get_token=1;
    prec_struct_t pointer_to_prec; //TODO treba inicializovat este, nezabudnut na free
    PrecStructInit(&pointer_to_prec);

    while(true){
        printf("##### RUN %d #####\n", run);
        run++;
        Token term;
        Token *actualterm = &term; //mozno bute treba malloc pri predavani

        Custom_string my_string;
        Custom_string *my_str = &my_string; //mozno bute treba malloc pri predavani
        
        custom_string_init(my_str);

        if(!Stack_Is_Empty(&stack)){
            if(stack.top->isterminal==false){ //na vrchu staku je neterminal
             if(can_get_token){
                 if(pointer_to_prec.number_of_prec_ret_tokens==0){ //kontola konce prebratych tokenov od precedencnej
                    generate_token(actualterm, my_str);//zoberiem token
                 }else{
                     pointer_to_prec.number_of_prec_ret_tokens--; //najskor treba odratat, aby som sa dostal na spravny index
                     actualterm=&pointer_to_prec.token[pointer_to_prec.number_of_prec_ret_tokens]; //vyberiem token od precedencnej
                     //moznost kolizie pri volani precedencnej pri druhom znaku pola
                 }
                 
                 printf("Prijaty terminal: %d \n", actualterm->type_of_token);  
                 
             }
              can_get_token=1;
              printf("Na vrchole stacku je neterminal\n");
              
               Token_type inputIndex=actualterm->type_of_token;//vezmem jeho index podla enumu
               int stackIndex=stack.top->nterm;//zoberem index ne(terminalu) na stacku
               printf("neterminal na vrchu stacku: %d\n", Stack_Top_NonTerminal(&stack));
               printf("stack index: %d input index :%d\n", stackIndex, inputIndex);
               int ruleNumber=LLtable[stackIndex][inputIndex]; //vyber pravidla
               printf("Rule number: %d\n", ruleNumber);

               if(ruleNumber==SE){
                   printf("Syntax error\n");
                   if(!Stack_Is_Empty(&stack)){
                       printf("Stack: %c\n", stack.top->nterm);
                   } 
                   custom_string_free_memory(my_str);
                   Stack_Free(&stack);
                   process_error(SYNTAX_ANALYSIS_FAIL);
               }else{
                   can_get_token=0;
                   printf("Cislo vybraneho pravidla %d \n",ruleNumber);
                   rule_t rule=RULES[ruleNumber]; //vybranie pravidla

                   //VOLANIE PRECEDENCNEJ NA ZAKLADE NETERMINALU
                   // expression_nt na stacku A ID na vstupe
                   if(stack.top->isterminal==false && stack.top->nterm==NT_EXPRESSION){
                      printf("---tu planujem volat precedencnu\n"); 
                    /*precedence_analysis(actualterm, &pointer_to_prec); //posielam terminal a structu, kde mi bude zapisovat precedencna
                      //funkcia mi vrati list tokenov s postfixom, musim ho vediet potom preposlat generatoru  
                      Stack_Pop(&stack); //popnem expression, mozno bude treba DVA popy s podmienkou, lebo bude treba popovat aj value_nt, pripadne nepushovat value nt ale rovno ID
                      continue;          //vratim sa na zaciatok whilu a idem kontrolovat od znova
                     */ 
                   }

                   Stack_Pop(&stack); //popnem neterminal z vrcholu stacku
                   for (int i=rule.number_of_derivations-1; i>=0; i--){  //rozvinute pravidla na stack pushujem reverzne
                       //printf("Pushujem na stack:  isterminal: %d rule term: %d rule nterm: %d\n",  rule.right_side_of_derivation[i].isterminal, rule.right_side_of_derivation[i].term, rule.right_side_of_derivation[i].nterm);
                        Stack_Push(&stack, rule.right_side_of_derivation[i].isterminal, rule.right_side_of_derivation[i].term, rule.right_side_of_derivation[i].nterm);                       
                        printf("Na stack sa pushlo: isterminal: %d stac term: %d stac nterm: %d\n", stack.top->isterminal, stack.top->term, stack.top->nterm);
                   }                
               }
            }else{ //na vrchole stacku je terminal 
                
                //printf("Prijaty terminal: %d \n", actualterm->type_of_token);
                printf("DOLE stack: %d, input: %d\n", stack.top->term, actualterm->type_of_token);
                if(actualterm->type_of_token==Stack_Top_Terminal(&stack)){ //na vrchole zasobika je terminal, na vstupe je rovnaky terminal
                    printf("na vstupe je rovnaky terminal ako na vrchole stacku, POP\n");
                    //tu sa vola semanticka a generator a posiela sa mu token a struct nasa nova                   
                    Stack_Pop(&stack); //popujem stack TODO tu mozno bude treba najskor overit ci mozem popovat 
                        if(pointer_to_prec.number_of_prec_ret_tokens==0){ //kontola konca prebratych tokenov od precedencnej
                            generate_token(actualterm, my_str);//zoberiem token
                        }else{
                            pointer_to_prec.number_of_prec_ret_tokens--; //najskor sa musim dostat na spravny index
                            actualterm=&pointer_to_prec.token[pointer_to_prec.number_of_prec_ret_tokens]; //vyberiem token od precedencnej
                            //moznost kolizie pri volani precedencnej pri druhom znaku pola
                        }
                    printf("Prijaty terminal: %d \n", actualterm->type_of_token);
                    
                    //generate_token(actualterm, my_str);//zoberiem token
                }else{
                    printf("Syntax error end\n");
                    custom_string_free_memory(my_str);
                    Stack_Free(&stack);
                    process_error(SYNTAX_ANALYSIS_FAIL);
                }
            }    
        }else{
            printf("Success\n");
            custom_string_free_memory(my_str);
            Stack_Free(&stack);
            return 0;
        }
         custom_string_free_memory(my_str);   
    }
      
}


