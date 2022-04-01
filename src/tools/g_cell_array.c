#include "g_cell_array.h"

#include <stdlib.h>
#include "g_cell_array.h"

/**
 * Create a new 2D grid array of cells with each state initialized at 0.
 * @param w width of the grid
 * @param h height of the grid
 * @return the newly created array
 */
CellArray *ca_create(int w, int h, void* (*create_state)()) {

    void **p_array =  malloc(sizeof(void *) * (w * h));

    CellArray *p_cell_array = (CellArray *) malloc(sizeof(CellArray));
    p_cell_array->w = w;
    p_cell_array->h = h;
    p_cell_array->array = p_array;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            p_array[x + (w * y)] = create_state();
        }
    }

    return p_cell_array;
}

/**
 * Given a position in grid, return the corresponding index in the array.
 * @param ca 2D grid of cells
 * @param x
 * @param y
 * @return index in array
 */
int ca_get_index(const CellArray *ca, int x, int y) {
    if (x < 0) x = ca->w + x;
    if (x >= ca->w) x = x - ca->w;
    if (y < 0) y = ca->h + y;
    if (y >= ca->h) y = y - ca->h;
    return x + (ca->w * y);
}

/**
 * Get the state of the cell at the given position.
 * @param ca
 * @param x
 * @param y
 * @return cell state at (x,y)
 */
void* ca_get(const CellArray *ca, int x, int y) {
    int index = ca_get_index(ca, x, y);
    return ca->array[index];
}

/**
 * Set the state value at a given position
 * @param ca
 * @param x
 * @param y
 * @param s new state of cell
 */
void ca_set(CellArray *ca, int x, int y, void* s) {
    if (x < 0) return;
    if (x >= ca->w) return;
    if (y < 0) return;
    if (y >= ca->h) return;
    ca->array[x + (ca->w * y)] = s;
}

/**
 * Get the neighborhood of a cell.
 * @param ca
 * @param x
 * @param y
 * @return Neighborhood of 8 cells around (x,y)
 */
CellNeighborhood ca_get_neighborhood(const CellArray *ca, int x, int y) {
    CellNeighborhood cn;
    cn.m = ca_get(ca, x, y);
    cn.t = ca_get(ca, x, y - 1);
    cn.b = ca_get(ca, x, y + 1);
    cn.r = ca_get(ca, x + 1, y);
    cn.l = ca_get(ca, x - 1, y);
    cn.tl = ca_get(ca, x - 1, y - 1);
    cn.tr = ca_get(ca, x + 1, y - 1);
    cn.bl = ca_get(ca, x - 1, y + 1);
    cn.br = ca_get(ca, x + 1, y + 1);

    return cn;
}
