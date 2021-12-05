#ifndef CODE_GENERATOR
#define  CODE_GENERATOR

#include "recursive_syntactic.h"

void genertaor_start();

// Create functions
void create_main();
void create_function_label(char *label);
void create_function_call(char *label);
void create_function_return(int return_id, char *return_value);
void create_function_end(char *label);
void create_function_parameter(int param_id, char *parameter);
void create_write(int var_type, Token *token);

//Práca s rámci, volanie funkcií
void print_move(char* var_type, char *var, char*symb_type, char *symb);
void print_create_frame();
void print_push_frame();
void print_pop_frame();
void print_def_var(char *type,char*var);
void print_call(char *label);
void print_return();

//Práca s dátovým zásobníkom
void print_pushs(char*var);
void print_pops(char *var);
void print_clears();

//Aritmetické inštrukcie
void print_add(char *var, char *number0, char *number1);
void print_sub(char *var, char *number0, char *number1);
void print_mul(char *var, char *number0, char *number1);
void print_div(char *var, char *number0, char *number1);
void print_idiv(char *var, char *number0, char *number1);

//Relačné inštrukcie
void print_lt(char *var, char *number0, char *number1);
void print_gt(char *var, char *number0, char *number1);
void print_eq(char *var, char *number0, char *number1);

//Boolovské inštrukcie
void print_and(char *var, char *number0, char *number1);
void print_or(char *var, char *number0, char *number1);
void print_not(char *var, char *number0, char *number1);

//Konverzné inštrukcie
void print_int_2_float(char *var, char *number);
void print_float_2_int(char *var, char *number);
void print_int_2_char(char *var, char *number);
void print_stri_2_int(char *var, char *number0, char *number1);

//Vstupno-výstupné inštrukcie
void print_read(char *var, char *type);
void print_write(char *symb);

//Práca s reťazcami
void print_concat(char *var, char *symb0, char *symb1);
void print_strlen(char *var, char *number);
void print_get_char(char *var, char *string, char* index);
void print_set_char(char *var, char *index, char* string);

//Práca s typmi
void print_type(char *var, char *type);

//Inštrukcie pre riadenie toku programu
void print_label(char *label);
void print_jump(char *label);
void print_jumpifeq(char *label, char *symb0, char *symb1);
void print_jumpifneq(char *label, char *symb0, char *symb1);
void print_exit(char *number);

//Ladiace funkcie
void print_break();
void print_dprint(char *symb);

#endif // !CODE_GENERATOR 
