#define SE=-1;
#define EPS=-2;
#define NUMBER_OF_RULES=20;
#define NUMBER_OF_TERMS=21;
#define NUMBER_OF_NTERMS=28;
#define NUMBER_OF_RIGHT_SIDE_OF_DERIVATION=9;

typedef enum{
    //term keywords 0-19
    //scanner enum zdielanu s tymto enum
    //scanner odlisi ID FN, a ID
    T_KW_REQUIRE=0, 
    T_KW_DO=1,
    T_KW_ELSE=2,
    T_KW_END=3,
    T_KW_FUNCTION=4,
    T_KW_GLOBAL=5,
    T_KW_IF=6,
    T_KW_LOCAL=7,
    T_KW_NIL=8,
    T_TYPE_NUMBER=9,
    T_KW_RETURN=10,
    T_KW_THEN=11,
    T_KW_WHILE=12,

    T_TYPE_SEMICOLON=14,                  // [ ; ]
    T_TYPE_RIGHT_BRACKET=15,              // [ ) ]
    T_TYPE_LEFT_BRACKET=16,               // [ ( ]
    T_TYPE_COMMA=17,                      // [ , ]
    T_TYPE_DOUBLE_DOT=18,                 // [ : ]
    T_TYP_EQ=19,                          // [ = ]
    T_TOKEN_EOF=20

    //term types 
    T_TYPE_ID=21, //variable name
    T_TYPE_FUNC_ID=22, //function name  //+FUNC_ID
    T_TYPE_INT=23,              
    T_TYPE_STRING=24,
    //pridane
    T_STRING_CONST=25,
    T_INT_CONST=26,
    T_NUMBER_CONST=27
    //koniec pridanych

    //TODO pridat expression + - * / ,...
    //spolu 38 vraj upravit aj define pocet

}terms_type;

typedef enum{
    //neterminaly
    NT_PROLOG=0,
    NT_VALUE=1,
    NT_ASSVAL=2,
    NT_DATA_TYPE=3,
    NT_EXPRESSION=4,
    NT_FUNC_DEC=5,
    NT_PARAM=6,
    NT_PARAMS=7,
    NT_FUNC=8,
    NT_ARG=9,
    NT_ARGUMENT=10,
    NT_RET_ARG=11,
    NT_RET_ARGS=12,
    NT_CODE=13,
    NT_RETURN=14,
    NT_RETURNS=15,
    NT_VALUE=16,
    NT_FUNC_CALL=17,
    NT_CALL_PARAM=18,
    NT_CALL_PARAMS=19,
    NT_ASSIGN_EXISTING=20,
    NT_TO_ASSIGN=21,
    NT_ASSIGN_VALUE=22,
    NT_ASSIGN_VALUES=23,
    NT_TO_ASSIGN2=23,
    NT_ASSIGN_NEW=24,
    NT_ASSIGN=25,
    NT_WHILE=26,
    NT_IF=27,
    NT_START=28,
    NT_DOUBLE_DOT=29

}nterms_type;

typedef struct symbol_t {
    bool isterminal;
    terms_type term;
    nterms_type nterm;
}symbol_t;

typedef struct rules_t{
    unsigned number_of_derivations;
    struct symbol_t right_side_of_derivation[NUMBER_OF_RIGHT_SIDE_OF_DERIVATION];
}rule_t;



const rule_t RULES[NUMBER_OF_RULES]={
  /*  0 - prolog_nt -> */                               {.number_of_derivations=2, {{.isterminal=true, .term=T_KW_REQUIRE}}},
  /*  1 - start_nt -> func_call_nt start_nt */          {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},           {.isterminal=false, .nterm=NT_START}}},
  /*  2 - start_nt -> func_dec_nt start_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_DEC},            {.isterminal=false, .nterm=NT_START}}},
  /*  3 - start_nt -> func_nt start_nt */               {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC},                {.isterminal=false, .nterm=NT_START}}},
  /*  code_nt -> eps */             
  /*  4 - code_nt -> while_nt code_nt */                {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_WHILE},               {.isterminal=false, .nterm=NT_CODE}}},
  /*  5 - code_nt -> if_nt code_nt */                   {.number_of_derivations=2, {{.isterminal=false, .nterm=IF_NT},                  {.isterminal=false, .nterm=NT_CODE}}},    
  /*  6 - code_nt -> func_call_nt code_nt */            {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_FUNC_CALL},           {.isterminal=false, .nterm=NT_CODE}}},
  /*  7 - code_nt -> return_nt code_nt */               {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_RETURN},              {.isterminal=false, .nterm=NT_CODE}}},
  /*  8 - code_nt -> assign_existing_nt code_nt */      {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_ASSIGN_EXISTING},     {.isterminal=false, .nterm=NT_CODE}}},
  /*  9 - code_nt -> assign_new_nt code_nt */           {.number_of_derivations=2, {{.isterminal=false, .nterm=NT_ASSIGN_NEW},          {.isterminal=false, .nterm=NT_CODE}}},
  /* 10 - while_nt -> <kw_while> expression_nt <kw_do> code_nt <kw_end> */  
                                                        {.number_of_derivations=5, {{.isterminal=true, .term=T_KW_WHILE},               {.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=T_KW_DO},              {.isterminal=false, .nterm=NT_CODE}, {.isterminal=true, .term=T_KW_END}}},
  /* 11 - if_nt -> <kw_if> expression_nt <kw_then> code_nt <kw_else> code_nt <kw_end> */
                                                        {.number_of_derivations=7, {{.isterminal=true, .term=KW_THEN},                  {.isterminal=false, .nterm=NT_EXPRESSION}, {.isterminal=true, .term=T_KW_THEN},            {.isterminal=false, .nterm=NT_CODE}, {.isterminal=true, .term=T_KW_ELSE},               {.isterminal=false, .nterm=NT_CODE},        {.isterminal=true, .term=T_KW_END}}},
  /* 12 - func_dec -> <kw_global> <func_id> <:> <kw_function> <(> param_nt <)> double_dot_nt */
                                                        {.number_of_derivations=8, {{.isterminal=true, .term=KW_GLOBAL},                {.isterminal=true,  .term=T_TYPE_FUNC_ID},  {.isterminal=true,  .term=T_TYPE_LEFT_BRACKET},  {.isterminal=false, .nterm=NT_ARG},  {.isterminal=true, .nterm=T_TYPE_RIGHT_BRACKET},   {.isterminal=false, .nterm=NT_DOUBLE_DOT},  {.isterminal=false, .nterm=NT_CODE},    {.isterminal=true, .term=T_KW_END}}},
  /* 13 - double_dot_nt -> <:> datatype double_dots_nt*/{.number_of_derivations=3, {{.isterminal=true, .term=T_TYPE_DOUBLE_DOT},        {.isterminal=false, .nterm=NT_DATA_TYPE},   {.isterminal=false, .netrm=NT_DOUBLE_DOT}}},
  /*      */                                                                                                  


}table_of_rules_t;

int LLtable[NUMBER_OF_NTERMS][NUMBER_OF_TERMS]{
/*                      REQUIRE  DO  ELSE  END  FUNCTION  GLOBAL  IF  LOCAL  NIL  NUMBER  RETURN  THEN  WHILE  SEMICOLN  R_BRACKET L_BRACKET  COMMA  DOUBLEDOT  EQ  EOF  ID  FUNC_ID  INT  STRING   STRING_CONST  INT_CONST  NUMBER_CONST $ */
/*prolog*/              {  0     SE   SE   SE      SE       SE    SE   SE    SE     SE      SE     SE     SE     SE    SE      SE         SE           SE               SE           SE     SE}, //1     
/*value_nt*/           
/*assval_nt*/           
/*datatype_nt*/         
/*expression_nt*/       
/*func_dec*/            
/*param_nt*/            
/*params_nt*/           
/*func_nt*/             
/*arg_nt*/
/*argument_nt*/
/*ret_arg_nt*/
/*ret_args_nt*/
/*code_nt*/             { SE,    SE,  SE,  EPS/*end*/,                    5/*if*/ 9/*local*/                7/*return*/ 4/*while*/                                                        8/*id*/ 6/*func_id*/                     }
/*return_nt*/
/*returns_nt*/
/*value*/
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
};
