#ifndef ALIFE_CELL_ARRAY_DRAWER_H
#define ALIFE_CELL_ARRAY_DRAWER_H

#include "cell_array.h"
#include "window.h"

typedef struct {
    const int *r;
    const int *g;
    const int *b;

    const int cell_width;
    const bool is_grid_shown;
} CellArrayDrawer;

CellArrayDrawer *ca_drawer_create(const int *r, const int *g, const int *b, const int cell_width, bool is_grid_shown);

CellArrayDrawer *ca_drawer_draw(CellArrayDrawer *ca_drawer, CellArray *ca, Window *window);

#endif //ALIFE_CELL_ARRAY_DRAWER_H
