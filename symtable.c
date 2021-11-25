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


void table_init(symbol_table_t *table){

  for (int index = 0; index < HT_SIZE; index++ ){
      (*table)[index] = NULL;
    }
}


table_item_t *search(table_symbol_t *table, char *key){

  int hash_index = get_hash(key);                                              
  table_item_t *temp_item = (*table)[hash_index];                                

  while (temp_item != NULL){                                                   

    if(strcmp(temp_item->key,key) == 0){
      return temp_item;  
    }else{
      temp_item = temp_item->next;
    }
                       
  }

  return NULL;
}

void insert_symbol_variable(symbol_table_t *table, char *key , char *id, Symbol_type type, Additional_info *info){

  table_item_t *new_item = malloc(sizeof(table_item_t));
  if(new_item == NULL)
    return;

  new_item->key = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->key == NULL)
    return;
  
  int new_index = get_hash(key);
  table_item_t *found_item = ht_search(table,key);
  
  strcpy(new_item->key,key);

  //TODO
  
  if(found_item != NULL){
    found_item->value = value;
    free(new_item->key);
    free(new_item);

  }else{
    new_item->next = (*table)[new_index];
    (*table)[new_index] = new_item;
  }

}





