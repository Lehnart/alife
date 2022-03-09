#ifndef ALIFE_CELL_ARRAY_H
#define ALIFE_CELL_ARRAY_H

#include "cell_neighborhood.h"

typedef struct {
    int     w;
    int     h;
    int*    array;
} CellArray;

int get(const CellArray* ca, int x, int y);
void set(CellArray* ca, int x, int y, int s);

CellNeighborhood get_neighborhood(CellArray* pCA, int x, int y);
CellArray * random_cell_array(int w, int h, const int * states, const double * cumulative_prob);
CellArray * cell_array(int w, int h);


#endif //ALIFE_CELL_ARRAY_H
