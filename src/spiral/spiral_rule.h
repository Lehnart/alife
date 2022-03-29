#ifndef ALIFE_SPIRAL_RULE_H
#define ALIFE_SPIRAL_RULE_H

#include "../cell_neighborhood.h"
#include "../cell_array.h"

typedef struct{
    float decay_proba;
    float claim_empty;
    float claim_cell;
    float claim_hyper;

    int   state_count;
    int*  catalytic_states;

    float*  catalytic_probas;
} SpiralRule;


int apply(const SpiralRule * pRule, const CellNeighborhood *pN);
void evolve(CellArray* pCA, const SpiralRule* pRule);

#endif //ALIFE_SPIRAL_RULE_H
