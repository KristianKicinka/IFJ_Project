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


table_item_t *search_item(symbol_table_t *table, char *key){

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

void insert_symbol_variable(symbol_table_t *table, char *key){

  table_item_t *new_item = malloc(sizeof(table_item_t));
  if(new_item == NULL)
    return;

  new_item->key = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->key == NULL)
    return;
  
  new_item->data.identificator = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->data.identificator == NULL)
    return;
  
  int new_index = get_hash(key);
  table_item_t *found_item = search_item(table,key);
  
  strcpy(new_item->key,key);
  strcpy(new_item->data.identificator,key);

  new_item->data.symbol_info = IS_UNSET;
  new_item->data.symbol_variable_type = TYPE_UNSET;
  new_item->data.symbol_type = TYPE_VARIABLE;
  

  // Nemalo by nastat
  if(found_item != NULL){

    free(new_item->data.identificator);
    free(new_item->key);
    free(new_item);
    return;

  }else{
    new_item->next = (*table)[new_index];
    (*table)[new_index] = new_item;
  }
}

void insert_symbol_function(symbol_table_t *table, char *key){

  table_item_t *new_item = malloc(sizeof(table_item_t));
  if(new_item == NULL)
    return;

  new_item->key = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->key == NULL)
    return;

  new_item->data.identificator = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->data.identificator == NULL)
    return;
  
  int new_index = get_hash(key);
  table_item_t *found_item = search_item(table,key);
  
  strcpy(new_item->key,key);
  strcpy(new_item->data.identificator,key);

  new_item->data.symbol_info = IS_UNSET;
  //new_item->data.type_of_symbol = TYPE_UNSET;         nepoužíva sa 
  new_item->data.symbol_type = TYPE_FUNCTION;

  new_item->data.list_of_parameters = (Data_list*) malloc(sizeof(Data_list));
  if(new_item->data.list_of_parameters == NULL)
    return;

  function_data_list_init(new_item->data.list_of_parameters);       // hadze segfault

  new_item->data.list_of_return_types = (Data_list*) malloc(sizeof(Data_list));
  if(new_item->data.list_of_return_types == NULL)
    return;

  function_data_list_init(new_item->data.list_of_return_types);
  
  // Nemalo by nastat
  if(found_item != NULL){
    
    free(new_item->data.identificator);
    free(new_item->key);
    free(new_item);
    return;

  }else{
    new_item->next = (*table)[new_index];
    (*table)[new_index] = new_item;
  }

}

void insert_function_parameter(symbol_table_t *table, char *key, Token_type parameter){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL){
    bool err = function_data_list_insert(found_item->data.list_of_parameters,parameter);
    if(err == false){
      return;
    }
  }

}

void insert_function_return_type(symbol_table_t *table, char *key, Token_type return_type){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL){
    bool err = function_data_list_insert(found_item->data.list_of_return_types,return_type);
    if(err == false){
      return;
    }
  }

}

void set_symbol_variable_type(symbol_table_t *table, char *key, Token_type type){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL){
    found_item->data.symbol_variable_type = type;
  }
  
}

void set_additional_info(symbol_table_t *table, char *key, Additional_info info){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL){
    found_item->data.symbol_info = info;
  }

}

char *get_identificator(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.identificator;
  else
    return NULL;
}

Symbol_type *get_symbol_type(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.symbol_type);
  else
    return NULL;
}

Token_type *get_symbol_variable_type(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.symbol_variable_type);
  else
    return NULL;
}

Additional_info *get_additional_info(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.symbol_info);
  else
    return NULL;
}

Data_list *get_parameters(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.list_of_parameters;
  else
    return NULL;
}

Data_list *get_return_types(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.list_of_return_types;
  else
    return NULL;
}

void table_dispose(symbol_table_t *table){

  for (int index = 0; index < HT_SIZE; index ++){

    while ((*table)[index] != NULL){

      table_item_t *temp_item = (*table)[index];
      (*table)[index] = temp_item->next;

      if(temp_item->data.list_of_parameters != NULL){
        function_data_list_free_memory(temp_item->data.list_of_parameters);
        free(temp_item->data.list_of_parameters);
      }

      if(temp_item->data.list_of_return_types != NULL){
        function_data_list_free_memory(temp_item->data.list_of_return_types);
        free(temp_item->data.list_of_return_types);
      }

      free(temp_item->data.identificator);
      free(temp_item->key);
      free(temp_item);
    }
  }

}





