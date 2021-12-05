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

#define MAIN_LABEL "$$main"
#define DEF_VAR_LF "LF"
#define DEF_VAR_GF "GF"
#define DEF_VAR_TF "TF"    

void genertaor_start(){
    printf (".IFJcode21");
    print_jump(MAIN_LABEL);
}

void create_main(){
    print_jump(MAIN_LABEL);
    print_create_frame();
    print_push_frame();
}

void create_function_label(char *label){
    print_label(label);
    print_push_frame();
}

void create_function_call(char *label){
    print_call(label);
}

void create_function_return(int return_id, char *return_value){
    printf("\nDEFVAR LF@\%retva%d",return_id);
    printf("\nMOVE LF@\%retval%d",return_id);
}

void create_function_end(char *label){
    print_pop_frame();
    print_return();
}

void create_function_parameter(int param_id, char *parameter){
    print_def_var(DEF_VAR_LF,parameter);
    printf("\nMOVE LF@\%param%d LF@\%%d",param_id,param_id);
}





//Práca s rámci, volanie funkcií
void print_move(char* var_type, char *var, char*symb_type, char *symb){
    printf("\nMOVE %s@%s %s@%s", var_type,var,symb_type,symb);
}

void print_create_frame(){
    printf("\nCREATEFRAME");
}

void print_push_frame(){
    printf("\nPUSHFRAME");
}

void print_pop_frame(){
    printf("\nPOPFRAME");
}

void print_def_var(char *type,char*var){
    printf("\nDEFVAR %S@ %s", type,var);
}

void print_call(char *label){
    printf("\nCALL %s", label);
}

void print_return(){
    printf("\nRETURN");
}

//Práca s dátovým zásobníkom
void print_pushs(char*var){
    printf("\nPUSHS %s", var);
}

void print_pops(char *var){
    printf("\nPOPS %s", var);
}

void print_clears(){
    printf("\nCLEARS");
}

//Aritmetické inštrukcie
void print_add(char *var, char *number0, char *number1){
    printf("\nADD %s %s %s", var, number0, number1);
}

void print_sub(char *var, char *number0, char *number1){
    printf("\nSUB %s %s %s", var, number0, number1);
}

void print_mul(char *var, char *number0, char *number1){
    printf("\nMUL %s %s %s", var, number0, number1);
}

void print_div(char *var, char *number0, char *number1){
    printf("\nDIV %s %s %s", var, number0, number1);
}

void print_idiv(char *var, char *number0, char *number1){
    printf("\nIDIV %s %s %s", var, number0, number1);
}

//Relačné inštrukcie
void print_lt(char *var, char *number0, char *number1){
    printf("\nLT %s %s %s", var, number0, number1);
}

void print_gt(char *var, char *number0, char *number1){
    printf("\nGT %s %s %s", var, number0, number1);
}

void print_eq(char *var, char *number0, char *number1){
    printf("\nEQ %s %s %s", var, number0, number1);
}

//Boolovské inštrukcie
void print_and(char *var, char *number0, char *number1){
    printf("\nAND %s %s %s", var, number0, number1);
}

void print_or(char *var, char *number0, char *number1){
    printf("\nOR %s %s %s", var, number0, number1);
}

void print_not(char *var, char *number0, char *number1){
    printf("\nNOT %s %s %s", var, number0, number1);
}

//Konverzné inštrukcie
void print_int_2_float(char *var, char *number){
    printf("\nINT2FLOAT %s %s", var, number);
}

void print_float_2_int(char *var, char *number){
    printf("\nFLOAT2INT %s %s", var, number);
}

void print_int_2_char(char *var, char *number){
    printf("\nINT2CHAR %s %s", var, number);
}

void print_stri_2_int(char *var, char *number0, char *number1){
    printf("\nSTRI2INT %s %s %s", var, number0, number1);
}

//Vstupno-výstupné inštrukcie
void print_read(char *var, char *type){
    printf("\nREAD %s %s", var, type);
}

void print_write(char *symb){
    printf("\nWRITE %s", symb);
}

//Práca s reťazcami
void print_concat(char *var, char *symb0, char *symb1){
    printf("\nCONCAT %s %s %s", var, symb0, symb1);
}

void print_strlen(char *var, char *number){
    printf("\nSTRLEN %s %s", var, number);
}

void print_get_char(char *var, char *string, char* index){
    printf("\nGETCHAR %s %s %s", var, string, index);
}

void print_set_char(char *var, char *index, char* string){
    printf("\nSETCHAR %s %s %s", var, index, string);
}

//Práca s typmi
void print_type(char *var, char *type){
    printf("\nTYPE %s %s", var, type);
}

//Inštrukcie pre riadenie toku programu
void print_label(char *label){
    printf("\nLABEL %s", label);
}

void print_jump(char *label){
    printf("\nJUMP %s", label);
}

void print_jumpifeq(char *label, char *symb0, char *symb1){
    printf("\nJUMPIFEQ %s %s %s", label, symb0, symb1);
}

void print_jumpifneq(char *label, char *symb0, char *symb1){
    printf("\nJUMPIFNEQ %s %s %s", label, symb0, symb1);
}

void print_exit(char *number){
    printf("\nEXIT %s", number);
}

//Ladiace funkcie
void print_break(){
    printf("\nBREAK");
}

void print_dprint(char *symb){
    printf("\nDPRINT %s", symb);
}