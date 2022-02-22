#ifndef ALIFE_CELL_ARRAY_H
#define ALIFE_CELL_ARRAY_H

#include "spiral_rule.h"

typedef struct {
    int     w;
    int     h;
    int*    array;
    int*    iarray;

} CellArray;

int get(const CellArray* ca, int x, int y);
CellNeighborhood get_neighborhood(CellArray* pCA, int x, int y);
CellArray * random_cell_array(int w, int h, const int * states, const double * cumulative_prob);
CellArray * cell_array(int w, int h);

void evolve(CellArray* pCA, const SpiralRule* pRule);

#endif //ALIFE_CELL_ARRAY_H
