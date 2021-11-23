
#include "../custom_string.h"
#include <stdio.h>

void print_string(Custom_string *str);

int main(int argc, char const *argv[])
{
    printf("Custom string test \n");

    Custom_string my_string;
    Custom_string *my_str = &my_string;
    Custom_string my_sec_string;
    Custom_string *my_sec_str = &my_sec_string;
    char char_at = 'a';
    char *string_at = "Bashka is here";

    custom_string_init(my_str);
    custom_string_init(my_sec_str);

    printf("String 1 after init \n");
    print_string(my_str);
    printf("String 2 after init \n");
    print_string(my_sec_str);

    printf("add 5 chars to string 1 \n");
    for (int i = 0; i < 5; i++){
        custom_string_add_character(my_str,char_at);
    }
    print_string(my_str);

    printf("add 20 chars to string 2 \n");
    for (int i = 0; i < 20; i++){
        custom_string_add_character(my_sec_str,char_at);
    }
    print_string(my_sec_str);

    printf("free string 1 new init and add string to it  \n");
    custom_string_free_memory(my_str);
    custom_string_init(my_str);
    custom_string_add_another_string(my_str,string_at);
    print_string(my_str);

    printf("copy string 1 to string 2  \n");
    custom_string_copy_string(my_str,my_sec_str);
    print_string(my_str);
    print_string(my_sec_str);

    printf("compare string 1 with string 2 \n");
    int value = custom_string_compare_with_basic_string(my_str,my_sec_str->string_value);
    if(value == 0){
        printf("Lists are same \n");
    }else{
        printf("Lists are not same \n");
    }

    custom_string_free_memory(my_str);
    custom_string_free_memory(my_sec_str);


    

    return 0;
}


void print_string(Custom_string *str){
    printf("######################################################\n");
    printf("STRING VALUES \n");
    printf("Length of string is : %d \n",str->length);
    printf("Value of string is : %s \n",str->string_value);
    printf("Allocated memory size is : %d \n",str->size_of_allocated_memory);
    printf("######################################################\n");
    
}