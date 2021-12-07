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



/**
 * @brief Funkcia slúži na vytvorenie hashu
 * 
 * @param key Reťazec s hashovacím kľúčom
 * @return int Hash v tabuľke symbolov
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}


/**
 * @brief Funkcia slúži na inicializáciu tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 */
void table_init(symbol_table_t *table){

  for (int index = 0; index < HT_SIZE; index++ ){
      (*table)[index] = NULL;
    }
}


/**
 * @brief Funkcia slúži na vyhľadanie položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na nájdenú položku v tabuľke (v prípade neúspechu hodnota NULL)
 */
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


/**
 * @brief Funkcia slúži na vloženie novej premennej do tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na aktuálnu položku
 */
table_item_t *insert_symbol_variable(symbol_table_t *table, char *key){

  table_item_t *new_item = malloc(sizeof(table_item_t));
  if(new_item == NULL)
    process_error(INTERNAL_FAILATURE);

  new_item->key = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->key == NULL)
    process_error(INTERNAL_FAILATURE);
  
  new_item->data.identificator = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->data.identificator == NULL)
    process_error(INTERNAL_FAILATURE);
  
  int new_index = get_hash(key);
  table_item_t *found_item = search_item(table,key);
  
  strcpy(new_item->key,key);
  strcpy(new_item->data.identificator,key);

  new_item->data.is_defined = true;
  
  //new_item->data.symbol_info = IS_UNSET;
  new_item->data.symbol_variable_type = TYPE_UNSET;
  new_item->data.symbol_type = TYPE_VARIABLE;
  

  // Nemalo by nastat
  if(found_item != NULL){

    free(new_item->data.identificator);
    free(new_item->key);
    free(new_item);

    return new_item;

  }else{
    new_item->next = (*table)[new_index];
    (*table)[new_index] = new_item;
  }

  return new_item;

}


/**
 * @brief Funkcia slúži na vloženie novej funkcie do tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return table_item_t* Ukazateľ na aktuálnu položku
 */
table_item_t *insert_symbol_function(symbol_table_t *table, char *key){

  table_item_t *new_item = malloc(sizeof(table_item_t));
  if(new_item == NULL)
    process_error(INTERNAL_FAILATURE);

  new_item->key = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->key == NULL)
    process_error(INTERNAL_FAILATURE);

  new_item->data.identificator = malloc(sizeof(char)*(strlen(key)+1));
  if(new_item->data.identificator == NULL)
    process_error(INTERNAL_FAILATURE);
  
  int new_index = get_hash(key);
  table_item_t *found_item = search_item(table,key);
  
  strcpy(new_item->key,key);
  strcpy(new_item->data.identificator,key);

  //new_item->data.symbol_info = IS_UNSET;
  new_item->data.symbol_type = TYPE_FUNCTION;
  new_item->data.is_defined = false;
  new_item->data.is_declared = false;

  new_item->data.list_of_parameters = (Data_list*) malloc(sizeof(Data_list));
  if(new_item->data.list_of_parameters == NULL)
    process_error(INTERNAL_FAILATURE);

  function_data_list_init(new_item->data.list_of_parameters);       // hadze segfault

  new_item->data.list_of_return_types = (Data_list*) malloc(sizeof(Data_list));
  if(new_item->data.list_of_return_types == NULL)
    process_error(INTERNAL_FAILATURE);

  function_data_list_init(new_item->data.list_of_return_types);
  
  // Nemalo by nastat
  if(found_item != NULL){
    
    free(new_item->data.identificator);
    free(new_item->key);
    free(new_item);
    return new_item;

  }else{
    new_item->next = (*table)[new_index];
    (*table)[new_index] = new_item;
  }

  return new_item;

}


/**
 * @brief Funkcia slúži na vloženie nového parametra do zoznamu parametrov definovanej funkcie
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param parameter Parameter, ktorý sa vloží do zoznamu
 */
void insert_function_parameter(symbol_table_t *table, table_item_t *item, Token_type parameter){

  if(item != NULL){
    function_data_list_insert(item->data.list_of_parameters,parameter);
  }

}


/**
 * @brief Funkcia slúži na vloženie nového návratového do zoznamu parametrov definovanej funkcie
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param parameter Návratový typ, ktorý sa vloží do zoznamu
 */
void insert_function_return_type(symbol_table_t *table, table_item_t *item, Token_type return_type){

  if(item != NULL){
    function_data_list_insert(item->data.list_of_return_types,return_type);
  }

}


/**
 * @brief Funkcia slúži na nastavenie typu premennej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param item Ukazateľ na aktuálnu položku
 * @param type Typ premennej, ktorý sa nastaví položke v tabuľke symbolov
 */
void set_symbol_variable_type(symbol_table_t *table, table_item_t *item, Token_type type){

  if(item != NULL){
    item->data.symbol_variable_type = type;
  }
  
}

void set_is_declared(symbol_table_t *table, table_item_t *item, bool value){
  if(item != NULL){
    item->data.is_declared = value;
  }
}

void set_is_defined(symbol_table_t *table, table_item_t *item, bool value){
  if(item != NULL){
    item->data.is_defined = value;
  }
}


/**
 * @brief Funkcia slúži na získanie identifikátora položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return char* Identifikátor položky v tabuľke
 */
char *get_identificator(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.identificator;
  else
    return NULL;
}


/**
 * @brief Funkcia slúži na získanie typu položky v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Symbol_type* Typ položky v tabuľke symbolov
 */
Symbol_type *get_symbol_type(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.symbol_type);
  else
    return NULL;
}


/**
 * @brief Funkcia slúži na získanie typu premennej z tabuľky symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Token_type* Typ premennej uloženej v tabuľke symbolov
 */
Token_type *get_symbol_variable_type(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.symbol_variable_type);
  else
    return NULL;
}



bool *get_is_defined(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.is_defined);
  else
    return NULL;
}

bool *get_is_declared(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return &(found_item->data.is_declared);
  else
    return NULL;
}


/**
 * @brief Funkcia slúži na získanie parametrov z funkcie uloženej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Data_list* Zoznam parametrov uloženej funkcie
 */
Data_list *get_parameters(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.list_of_parameters;
  else
    return NULL;
}


/**
 * @brief Funkcia slúži na získanie návratových typov funkcie uloženej v tabuľke symbolov
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 * @param key Reťazec s hashovacím kľúčom
 * @return Data_list* Zoznam návratových typov uloženej funkcie
 */
Data_list *get_return_types(symbol_table_t *table, char *key){

  table_item_t *found_item = search_item(table,key);

  if(found_item != NULL)
    return found_item->data.list_of_return_types;
  else
    return NULL;
}


/**
 * @brief Funkcia slúži na vymazanie tabuľky symbolov a uvoľnenie pamäti
 * 
 * @param table Ukazateľ na štruktúru tabuľky symbolov
 */
void table_dispose(symbol_table_t *table){

  for (int index = 0; index < HT_SIZE; index ++){

    while ((*table)[index] != NULL){

      table_item_t *temp_item = (*table)[index];
      (*table)[index] = temp_item->next;

      if(temp_item->data.symbol_type == TYPE_FUNCTION && temp_item->data.list_of_parameters != NULL){
        function_data_list_free_memory(temp_item->data.list_of_parameters);
        free(temp_item->data.list_of_parameters);
      }

      if(temp_item->data.symbol_type == TYPE_FUNCTION && temp_item->data.list_of_return_types != NULL){
        function_data_list_free_memory(temp_item->data.list_of_return_types);
        free(temp_item->data.list_of_return_types);
      }

      free(temp_item->data.identificator);
      free(temp_item->key);
      free(temp_item);
    }
  }

}





