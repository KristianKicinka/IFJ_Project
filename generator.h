/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file generator.c 
 * @author Lukáš Skopár (xskopa16)
 * @author Kristián Kičinka (xkicin02)
 * @brief  Spracovávanie generovania výstupného kódu (rozhranie)
 * 
 */


#ifndef CODE_GENERATOR_H
#define  CODE_GENERATOR_H

#include "recursive_syntactic.h"

void genertaor_start();

// Create functions
void create_main();
void create_function_label(char *label);
void create_function_call(char *label);
void create_function_return(int return_id, char *return_value);
void create_function_end(char *label);
void create_function_parameter(int param_id, char *parameter);
void create_read(int var_type);
void create_write(int var_type, Token *token);
void create_declaration_variable(char *var);

//if 
void create_if_start(int label);
void create_skip_else(int label);
void create_else(int label);
void create_if_end(int label);

//while
void create_while_start(int label);
void create_while_jump(int label);
void create_while_end(int label);

//compare
void create_lt(int label);
void create_gt(int label);
void create_EQ(int label);

//aritmeric instrucions
void create_add(int label);
void create_sub(int label);
void create_mul(int label);
void create_div(int label);
void create_idiv(int label);

//logical instructions
void create_and(int label);
void create_or(int label);
void create_not(int label);

//Práca s rámci, volanie funkcií
void print_move(char* var_type, char *var, char*symb_type, char *symb);
void print_create_frame();
void print_push_frame();
void print_pop_frame();
void print_def_var(char *type,char*var);
void print_call(char *label);
void print_return();

//instructions frame version
void create_frame_version_inst(int frame_inst);

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

#endif // !CODE_GENERATOR_H 
