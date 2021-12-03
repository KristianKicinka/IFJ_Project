// tests for list of parameters in function


#include "../../lexical_analysis.h"
#include "../../function_data_list.h"
#include <stdio.h>
#include <stdlib.h>

void print_list_params(Data_list *list, int index);

int main(int argc, char const *argv[]){

    Data_list my_params_list;
    Data_list *my_list = &my_params_list;

    function_data_list_init(my_list);

    print_list_params(my_list,0);

    function_data_list_insert(my_list,TYPE_INT_NUMBER);

    function_data_list_insert(my_list,TYPE_STRING);
    
    //TODO
    print_list_params(my_list,0);

    function_data_list_free_memory(my_list);
    

    return 0;
}


void print_list_params(Data_list *list, int index){
    printf("######################################################\n");
    printf("Parameter ( %d ) VALUES \n",index);
    printf("Parameter_count : %d \n",list->items_count);
    printf("Items : ");
    for(int loop = 0; loop < list->items_count; loop++)
      printf("%d ",(int) list->items[loop]);
    printf("\n");
    printf("######################################################\n");
    
}