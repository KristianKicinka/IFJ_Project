// tests for list of parameters in function


#include "../../symtable.h"
#include "../../table_item_list.h"
#include <stdio.h>
#include <stdlib.h>

void print_list_items(Table_list *list, int index);


int main(int argc, char const *argv[]){

    Table_list my_items_list;
    Table_list *my_list = &my_items_list;

    table_item_t frst_el;
    table_item_t *first = &frst_el;

    first->key = "ahoj";
    first->next = NULL;
    first->data.identificator = "ahoj";
    first->data.symbol_type = TYPE_VARIABLE;
    first->data.symbol_variable_type = TYPE_INT_NUMBER;
    first->data.symbol_info = IS_LOCAL;

    table_item_t sec_el;
    table_item_t *second = &sec_el;

    second->key = "nebarz";
    second->next = NULL;
    second->data.identificator = "nebarz";
    second->data.symbol_type = TYPE_VARIABLE;
    second->data.symbol_variable_type = TYPE_STRING;
    second->data.symbol_info = IS_LOCAL;

    table_item_list_init(my_list);

    print_list_items(my_list,0);

    table_item_list_insert(my_list,first);

    table_item_list_insert(my_list,second);
    
    //TODO
    print_list_items(my_list,1);

    table_item_list_free_memory(my_list);
    

    return 0;
}


void print_list_items(Table_list *list, int index){
    printf("######################################################\n");
    printf("Items ( %d ) VALUES \n",index);
    printf("Items_count : %d \n",list->items_count);
    printf("Items : ");
    for(int loop = 0; loop < list->items_count; loop++){
      printf("%s ",list->items[loop]->key);
    }
     
    printf("\n");
    printf("######################################################\n");
    
}