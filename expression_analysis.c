#include "expression_analysis.h"

int PSA_table[TABLE][TABLE] =
{
//             | + | - | * | / | // | .. | # | < | <= | > | >= | == | ~= | ID | ( | ) | $$ |
/*|  + |*/     { R , R, PA , PA, PA , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R },
/*|  - |*/     { R , R, PA , PA, PA , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R },
/*|  * |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*|  / |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*| // |*/     { R , R , R , R , R  , E , PA , R , R  , R , R  , R  , R  , PA , PA, R , R }, 
/*| .. |*/     { E , E , E , E , E  , R , E  , E , E  , E , E  , E  , E  , PA , PA, R , R },
/*|  # |*/     { R , R , R , R , R  , E , E  , R , R  , R , R  , R  , R  , PA , PA, R , R },  
/*|  < |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| <= |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*|  > |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| >= |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| == |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| ~= |*/     { PA, PA, PA, PA, PA , E , PA , E , E  , E , E  , E  , E  , PA , PA, E , R },
/*| ID |*/     { R , R , R , R , R  , R , E  , R , R  , R , R  , R  , R  , E  , E , R , R },
/*|  ( |*/     { PA, PA, PA, PA, PA , PA, PA , E , E  , E , E  , E  , E  , PA , PA, P , E },
/*|  ) |*/     { R , R , R , R , R  , R , E  , R , R  , R , R  , R  , R  , E  , E , R , R },
/*| $$ |*/     { PA, PA, PA, PA, PA , PA, PA , PA, PA , PA, PA , PA , PA , PA , PA, E , U }
};

