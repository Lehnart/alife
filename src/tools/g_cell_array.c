#include "g_cell_array.h"

#include <stdlib.h>
#include "g_cell_array.h"

/**
 * Create a new 2D grid array of cells with each state initialized at 0.
 * @param w width of the grid
 * @param h height of the grid
 * @return the newly created array
 */
CellArray *cell_array(int w, int h) {

    void **p_array =  malloc(sizeof(void *) * (w * h));

    CellArray *p_cell_array = (CellArray *) malloc(sizeof(CellArray));
    p_cell_array->w = w;
    p_cell_array->h = h;
    p_cell_array->array = p_array;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            p_array[x + (w * y)] = 0;
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
int get_index(const CellArray *ca, int x, int y) {
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
void* get(const CellArray *ca, int x, int y) {
    int index = get_index(ca, x, y);
    return ca->array[index];
}

/**
 * Set the state value at a given position
 * @param ca
 * @param x
 * @param y
 * @param s new state of cell
 */
void set(CellArray *ca, int x, int y, void* s) {
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
CellNeighborhood get_neighborhood(const CellArray *ca, int x, int y) {
    CellNeighborhood cn;
    cn.m = get(ca, x, y);
    cn.t = get(ca, x, y - 1);
    cn.b = get(ca, x, y + 1);
    cn.r = get(ca, x + 1, y);
    cn.l = get(ca, x - 1, y);
    cn.tl = get(ca, x - 1, y - 1);
    cn.tr = get(ca, x + 1, y - 1);
    cn.bl = get(ca, x - 1, y + 1);
    cn.br = get(ca, x + 1, y + 1);

    return cn;
}
