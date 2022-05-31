#ifndef ALIFE_IPD_RULE_H
#define ALIFE_IPD_RULE_H

#include "../../tools/cell_array.h"
#include "ipd_state.h"

typedef struct{
    float error_proba;
    float mut_proba;

    float R;
    float P;
    float S;
    float T;

    int try_count;
    int memory_size;
    int state_count;

} IPDRule;


typedef struct{
    const IPDRule* pRule;
    IPDStateCodes* pCodes;
    int *p1_memory;
    int *p2_memory;
} IPDGame;

void evolve(CellArray* pCA, const IPDRule* pRule);

#endif //ALIFE_IPD_RULE_H
