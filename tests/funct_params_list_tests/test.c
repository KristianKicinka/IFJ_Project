// tests for list of parameters in function


#include "../../scanner.h"
#include "../../funct_params_list.h"
#include <stdio.h>
#include <stdlib.h>

void print_list_params(Parameters_list *list, int index);

int main(int argc, char const *argv[]){

    Parameters_list my_params_list;
    Parameters_list *my_list = &my_params_list;
    init_function_parameters(my_list);

    print_list_params(my_list,0);

    int error_1 = function_parameters_insert(my_list,TYPE_INT_NUMBER);

    if (error_1 == false){
        return 1;
    }

    int error_2 = function_parameters_insert(my_list,TYPE_STRING);

    if (error_2 == false){
        return 1;
    }
    
    print_list_params(my_list,0);

    function_parameters_free_memory(my_list);
    

    return 0;
}


void print_list_params(Parameters_list *list, int index){
    printf("######################################################\n");
    printf("Parameter ( %d ) VALUES \n",index);
    printf("Parameter_count : %d \n",list->parameters_count);
    printf("Items : ");
    for(int loop = 0; loop < list->parameters_count; loop++)
      printf("%d ",(int) list->items[loop]);
    printf("\n");
    printf("######################################################\n");
    
}