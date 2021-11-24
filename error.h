#ifndef ERROR_H
#define ERROR_H

typedef enum {
    SCANNER_ANALYSIS_FAIL,                                                     // 1
    SCANNER_ANALYSIS_SUCCESS,                                                  // 0
    SYNTAX_ANALYSIS_FAIL,                                                      // 2
    SYNTAX_ANALYSIS_SUCCESS,                                                   // 0
    SEMANTIC_ANALYSIS_UNDEF_VAR,                                               // 3
    SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ASSIGN,                               // 4
    SEMANTIC_ANALYSIS_BAD_COUNT_PARAMETERS,                                    // 5
    SEMANTIC_ANALYSIS_UNCOMPATIBILE_TYPE_ARITMETIC,                            // 6                   
    SEMANTIC_ANALYSIS_FAIL_OTHERS,                                             // 7
    RUNTIME_ERROR_WITH_NIL,                                                    // 8
    RUNTIME_ERROR_DIVIDING_BY_ZERO,                                            // 9
    INTERNAL_FAILATURE,                                                        // 99

}Error_type;

int process_error(Error_type err_type);

#endif // !ERROR_H