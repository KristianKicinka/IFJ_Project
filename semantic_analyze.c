#include "semantic_analyze.h"


void process_semantic(Syntactic_data *data){

    switch (data->current_state)
    {
    case S_START:
        if(data->nterm == NT_FUNC_DEC)
            data->current_state = S_FUNCTION_DEC;
        break;
    case S_FUNCTION_DEC:
        if(data->token->type_of_token == TYPE_IDENTIFICATOR_FUNCTION){
            data->current_item = insert_symbol_function(data->global_table,data->token->token_info.custom_string);
            data->current_state = S_FUNCTION_PARAMETERS;
            break;
        }else{
            process_error(SEMANTIC_ANALYSIS_FAIL_OTHERS);
        }
            
        break;
    case S_FUNCTION_PARAMETERS:
        if(data->nterm == NT_PARAM){
            data->current_state = S_FUNCTION_PARAMETER_LOAD;
        }else{
            data->current_state = S_FUNCTION_RETURNS;
        }
        break;
    case S_FUNCTION_PARAMETER_LOAD:
        if(data->nterm == NT_PARAMS){
            data->current_state = S_FUNCTION_PARAMETERS_LOAD;
        }else if(data->token->type_of_token == TYPE_INT_NUMBER || 
            data->token->type_of_token == TYPE_STRING ||
            data->token->type_of_token == TYPE_DOUBLE_NUMBER ||
            data->token->type_of_token == TYPE_KW_NIL)
        {
            insert_function_parameter(data->global_table,data->current_item,data->token->type_of_token);
            data->current_state = S_FUNCTION_RETURNS;
        }else{
            data->current_state = S_FUNCTION_RETURNS;
        }
        break;
    case S_FUNCTION_PARAMETERS_LOAD:
        if(data->token->type_of_token == TYPE_INT_NUMBER || 
            data->token->type_of_token == TYPE_STRING ||
            data->token->type_of_token == TYPE_DOUBLE_NUMBER ||
            data->token->type_of_token == TYPE_KW_NIL)
        {
            insert_function_parameter(data->global_table,data->current_item,data->token->type_of_token);
            data->current_state = S_FUNCTION_PARAMETERS_LOAD;
        }else{
            data->current_state = S_FUNCTION_RETURNS;
        }
        break;
    case S_FUNCTION_RETURNS:
        if(data->nterm == NT_RETURN){

        }
        break;
    default:
        break;
    }
}