//#include "syntactic_analyze.c"
//#include "../../syntactic_analyze.h"
//#include "../../LL_table.c"
#include "../../recursive_syntactic.h"


int main(){

    int err=0;
    

    while(!feof(stdin) && err==0){
        analyze();
    }
    
    return 0;
}   