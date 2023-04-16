#ifndef ALIFE_CELL_ARRAY_H
#define ALIFE_CELL_ARRAY_H

#include "cell_array_rule.h"

/**
 * The 8 cell states around a middle one.
 */
typedef struct {
    union {
        struct {
            int m;
            int t;
            int r;
            int b;
            int l;
            int tl;
            int tr;
            int br;
            int bl;
        };

        int states[9];
    };

} CellNeighborhood;

/**
 * A 2D grid of cells.
 */
typedef struct {
    int w;
    int h;
    int *array;
    int *temp_array;
} CellArray;

CellArray *random_cell_array(int w, int h, const int *states, const double *cumulative_prob);

CellArray *ca_create(int w, int h);

void ca_reset(CellArray *ca);

void ca_init_from_file(CellArray *ca, char *filename);

int ca_get_index(const CellArray *ca, int x, int y);

int ca_get(const CellArray *ca, int x, int y);

CellNeighborhood ca_get_neighborhood(const CellArray *ca, int x, int y);

void ca_set(CellArray *ca, int x, int y, int s);

void ca_evolve(CellArray *ca, CellArrayRule *ca_rule);

void ca_custom_evolve(CellArray *ca, int (*custom_rule)(CellNeighborhood));

#endif //ALIFE_CELL_ARRAY_H
