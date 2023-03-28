#include <malloc.h>
#include "cell_array_drawer.h"
#include "window.h"
#include "cell_array.h"
#include <SDL2/SDL.h>

void ca_drawer_draw_cell(CellArrayDrawer *ca_drawer, int cell_x, int cell_y, int cell_state, Window *window);

CellArrayDrawer *ca_drawer_create(const int *r, const int *g, const int *b, const int cell_width, bool is_grid_shown) {
    CellArrayDrawer init_ca_drawer = {r, g, b, cell_width, is_grid_shown};
    CellArrayDrawer *ca_drawer = malloc(sizeof(CellArrayDrawer));
    memcpy(ca_drawer, &init_ca_drawer, sizeof(CellArrayDrawer));
    return ca_drawer;
}

CellArrayDrawer *ca_drawer_draw(CellArrayDrawer *ca_drawer, CellArray *ca, Window *window) {
    SDL_LockSurface(window->sdl_surface);
    for (int i = 0; i < ca->w; i++) {
        for (int j = 0; j < ca->h; j++) {
            int s = ca_get(ca, i, j);
            ca_drawer_draw_cell(ca_drawer, i, j, s, window);
        }
    }
    SDL_UnlockSurface(window->sdl_surface);
}

void ca_drawer_draw_cell(CellArrayDrawer *ca_drawer, int cell_x, int cell_y, int cell_state, Window *window) {
    int w = window->width;
    Uint32 *pixels = (Uint32 *) window->sdl_surface->pixels;
    for (int i = cell_x * ca_drawer->cell_width; i < (cell_x + 1) * ca_drawer->cell_width; i++) {
        for (int j = cell_y * ca_drawer->cell_width; j < (cell_y + 1) * ca_drawer->cell_width; j++) {
            if (ca_drawer->is_grid_shown && (i == cell_x * ca_drawer->cell_width || j == cell_y * ca_drawer->cell_width)) {
                continue;
            }
            pixels[i + (j * w)] = SDL_MapRGBA(window->sdl_surface->format, ca_drawer->r[cell_state], ca_drawer->g[cell_state], ca_drawer->b[cell_state], 255);
        }
    }
}
