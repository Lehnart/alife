#ifndef ALIFE_IPD_RULE_H
#define ALIFE_IPD_RULE_H

#include "cell_array.h"

typedef struct{
    float error_proba;
    float mut_proba;
    float dupl_proba;
    float split_proba;

    float R;
    float P;
    float S;
    float T;
} IPDRule;

int apply(const IPDRule * pRule, const CellNeighborhood *pN);
void evolve(CellArray* pCA, const IPDRule* pRule);

#endif //ALIFE_IPD_RULE_H
