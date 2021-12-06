/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file ifjcode21_compiler.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Code compiler (implementácia)
 * 
 */

#include "recursive_syntactic.h"

int main(int argc, char const *argv[]){

    while(!feof(stdin)){
        analyze();
    }

    return 0;
}
