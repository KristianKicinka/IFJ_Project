// tests for symtable

#include "../../symtable.h"
#include <stdio.h>
#include <stdlib.h>

void print_symtable_items(symbol_table_t *table, char *key);

int main(int argc, char const *argv[]){

    symbol_table_t table;
    symbol_table_t *my_table = &table;

    char *variable_key = "andrej";
    char *function_key = "andrej_function";

    table_item_t current_function;
    table_item_t *curr_function = &current_function;

    table_item_t current_variable;
    table_item_t *curr_variable = &current_variable;

    table_init(my_table);

    // Working with variable
    curr_variable = insert_symbol_variable(my_table,variable_key);
    set_symbol_variable_type(my_table,curr_variable,TYPE_INT_NUMBER);
    print_symtable_items(my_table,variable_key);

    // Working with function

    curr_function = insert_symbol_function(my_table,function_key);
    //set_additional_info(my_table,curr_function,IS_DEFINED);
    insert_function_parameter(my_table,curr_function,TYPE_INT_NUMBER);
    insert_function_parameter(my_table,curr_function,TYPE_INT_NUMBER);
    insert_function_return_type(my_table,curr_function,TYPE_STRING);
    print_symtable_items(my_table,function_key);

    table_dispose(my_table);

    return 0;
}


void print_symtable_items(symbol_table_t *table, char *key){
    char *name = get_identificator(table,key);
    Symbol_type *symbol_type = get_symbol_type(table,key);
    //Additional_info *symbol_info = get_additional_info(table,key);

    printf("######################\n");
    printf("name is : %s \n",name);
    printf("Symbol type is : %d \n",(int)*symbol_type);

    if((*symbol_type) != TYPE_FUNCTION){
        Token_type *symbol_variable_type = get_symbol_variable_type(table,key);
        printf("Symbol var type is : %d \n",(int)*symbol_variable_type);
    }
    
    //printf("Symbol info is : %d \n",(int)*symbol_info);

    if((*symbol_type) == TYPE_FUNCTION){
        Data_list *parameters = get_parameters(table,key);
        Data_list *return_types = get_return_types(table,key);
        printf("parameters : ");
        for (int i = 0; i < parameters->items_count; i++){
            printf("%d ",parameters->items[i]);
        }
        printf("\nreturn types : ");
        for (int i = 0; i < return_types->items_count; i++){
            printf("%d ",return_types->items[i]);
        }
        printf("\n");
        
    }
    printf("######################\n");
}