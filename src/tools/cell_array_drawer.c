#include <malloc.h>
#include "cell_array_drawer.h"
#include "window.h"
#include "cell_array.h"
#include <SDL2/SDL.h>

CellArrayDrawer *ca_drawer_create(const int *r, const int *g, const int *b) {
    CellArrayDrawer *ca_drawer = malloc(sizeof(CellArrayDrawer));
    ca_drawer->r = r;
    ca_drawer->g = g;
    ca_drawer->b = b;
    return ca_drawer;
}

CellArrayDrawer *ca_drawer_draw(CellArrayDrawer *ca_drawer, CellArray *ca, Window *window) {
    Uint32 *pixels;
    int i, j;
    int w = window->width;
    int h = window->height;

    SDL_LockSurface(window->sdl_surface);
    pixels = (Uint32 *) window->sdl_surface->pixels;
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int s = ca_get(ca, i, j);
            pixels[i + (j * w)] = SDL_MapRGBA(window->sdl_surface->format, ca_drawer->r[s], ca_drawer->g[s], ca_drawer->b[s], 255);
        }
    }
    SDL_UnlockSurface(window->sdl_surface);
}
