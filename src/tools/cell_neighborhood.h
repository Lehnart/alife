#ifndef ALIFE_CELL_NEIGHBORHOOD_H
#define ALIFE_CELL_NEIGHBORHOOD_H

typedef struct{
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

#endif //ALIFE_CELL_NEIGHBORHOOD_H
