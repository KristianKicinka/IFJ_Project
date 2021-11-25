/**
 * 
 * Project : Implementace překladače imperativního jazyka IFJ21.
 * 
 * @file symtable.c 
 * @author Kristián Kičinka (xkicin02)
 * @brief  Tybuľka symbolov (implementácia)
 * 
 */

#include "symtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = SYMBOL_TABLE_SIZE;

int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}





