#include "generator.h"
#include <stdio.h>

/*
-    MOVE ⟨var⟩ ⟨symb⟩
-    CREATEFRAME
-    PUSHFRAME
-    POPFRAME
-    DEFVAR ⟨var⟩
-    CALL ⟨label⟩
-    RETURN

-    PUSHS ⟨symb⟩
-    POPS ⟨var⟩
-    CLEARS

-    ADD ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    SUB ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    MUL ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    DIV ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    IDIV ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
    ADDS/SUBS/MULS/DIVS/IDIVS
-    LT/GT/EQ ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
    LTS/GTS/EQS ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    AND/OR/NOT ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
    ANDS/ORS/NOTS ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    INT2FLOAT ⟨var⟩ ⟨symb⟩
-    FLOAT2INT ⟨var⟩ ⟨symb⟩
-    INT2CHAR ⟨var⟩ ⟨symb⟩
    INT2FLOATS/FLOAT2INTS/INT2CHARS/STRI2INTS

-    READ ⟨var⟩ ⟨type⟩
-    WRITE ⟨symb⟩

-    CONCAT ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    STRLEN ⟨var⟩ ⟨symb⟩
-    GETCHAR ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩
-    SETCHAR ⟨var⟩ ⟨symb1⟩ ⟨symb2⟩

-    TYPE ⟨var⟩ ⟨symb⟩

-    LABEL ⟨label⟩
-    JUMP ⟨label⟩ 
-    JUMPIFEQ ⟨label⟩ ⟨symb1⟩ ⟨symb2⟩
-    JUMPIFNEQ ⟨label⟩ ⟨symb1⟩ ⟨symb2⟩
    JUMPIFEQS/JUMPIFNEQS ⟨label⟩
-    EXIT ⟨symb⟩

-    BREAK
-    DPRINT ⟨symb⟩
*/

//Práca s rámci, volanie funkcií
void print_move(char *var, char *symb){
    printf("MOVE %s %s", var, par);
}

void print_create_frame(){
    printf("CREATEFRAME");
}

void print_push_frame(){
    printf("PUSHFRAME");
}

void print_pop_frame(){
    printf("POPFRAME");
}

void print_def_var(char*var){
    printf("DEFVAR %s", var);
}

void print_call(char *label){
    printf("CALL %s", label);
}

void print_return(){
    printf("RETURN");
}

//Práca s dátovým zásobníkom
void print_pushs(char*var){
    printf("PUSHS %s", var);
}

void print_pops(char *var){
    printf("POPS %s", var);
}

void print_clears(){
    printf("CLEARS");
}

//Aritmetické inštrukcie
void print_add(char *var, char *number0, char *number1){
    printf("ADD %s %s %s", var, number0, number1);
}

void print_sub(char *var, char *number0, char *number1){
    printf("SUB %s %s %s", var, number0, number1);
}

void print_mul(char *var, char *number0, char *number1){
    printf("MUL %s %s %s", var, number0, number1);
}

void print_div(char *var, char *number0, char *number1){
    printf("DIV %s %s %s", var, number0, number1);
}

void print_idiv(char *var, char *number0, char *number1){
    printf("IDIV %s %s %s", var, number0, number1);
}

//Relačné inštrukcie
void print_lt(char *var, char *number0, char *number1){
    printf("LT %s %s %s", var, number0, number1);
}

void print_gt(char *var, char *number0, char *number1){
    printf("GT %s %s %s", var, number0, number1);
}

void print_eq(char *var, char *number0, char *number1){
    printf("EQ %s %s %s", var, number0, number1);
}

//Boolovské inštrukcie
void print_and(char *var, char *number0, char *number1){
    printf("AND %s %s %s", var, number0, number1);
}

void print_or(char *var, char *number0, char *number1){
    printf("OR %s %s %s", var, number0, number1);
}

void print_not(char *var, char *number0, char *number1){
    printf("NOT %s %s %s", var, number0, number1);
}

//Konverzné inštrukcie
void print_int_2_float(char *var, char *number){
    printf("INT2FLOAT %s %s", var, number);
}

void print_float_2_int(char *var, char *number){
    printf("FLOAT2INT %s %s", var, number);
}

void print_int_2_char(char *var, char *number){
    printf("INT2CHAR %s %s", var, number);
}

void print_stri_2_int(char *var, char *number0, char *number1){
    printf("STRI2INT %s %s %s", var, number0, number1);
}

//Vstupno-výstupné inštrukcie
void print_read(char *var, char *type){
    printf("READ %s %s", var, type);
}

void print_write(char *symb){
    printf("WRITE %s", symb);
}

//Práca s reťazcami
void print_concat(char *var, char *symb0, char *symb1){
    printf("CONCAT %s %s %s", var, symb0, symb1);
}

void print_strlen(char *var, char *number){
    printf("STRLEN %s %s", var, number);
}

void print_get_char(char *var, char *string, char* index){
    printf("GETCHAR %s %s %s", var, string, index);
}

void print_set_char(char *var, char *index, char* string){
    printf("SETCHAR %s %s %s", var, index, string);
}

//Práca s typmi
void print_type(char *var, char *type){
    printf("TYPE %s %s", var, type);
}

//Inštrukcie pre riadenie toku programu
void print_label(char *label){
    printf("LABEL %s", label);
}

void print_jump(char *label){
    printf("JUMP %s", label);
}

void print_jumpifeq(char *label, char *symb0, char *symb1){
    printf("JUMPIFEQ %s %s %s", label, symb0, symb1);
}

void print_jumpifneq(char *label, char *symb0, char *symb1){
    printf("JUMPIFNEQ %s %s %s", label, symb0, symb1);
}

void print_exit(char *number){
    printf("EXIT %s", number);
}

//Ladiace funkcie
void print_break(){
    printf("BREAK");
}

void print_dprint(char *symb){
    printf("DPRINT %s", symb);
}