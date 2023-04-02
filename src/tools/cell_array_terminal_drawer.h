#ifndef ALIFE_CELL_ARRAY_TERMINAL_DRAWER_H
#define ALIFE_CELL_ARRAY_TERMINAL_DRAWER_H

#include <ncurses.h>
#include "cell_array.h"
typedef struct{
    const short index;
    const short fg_color;
    const short bg_color;
} Pair;

typedef struct {
    const Pair *pairs;
    const char *chars;
    const int size;
} CellArrayTermDrawer;

CellArrayTermDrawer *ca_term_drawer_create(const Pair *pairs, const char *chars, int size);

void ca_term_drawer_draw(CellArrayTermDrawer *ca_drawer, CellArray *ca);

#endif //ALIFE_CELL_ARRAY_TERMINAL_DRAWER_H
