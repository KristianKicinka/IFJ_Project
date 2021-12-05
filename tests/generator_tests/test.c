/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file test.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Testovací skript generátora
 * 
 */


#include "../../generator.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]){

    genertaor_start();
    printf("\n<Functions dec>\n");
    create_main();
    printf("\n<Main body>\n");
    printf("\n");
    

    return 0;
}

