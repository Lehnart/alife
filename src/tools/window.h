#ifndef ALIFE_WINDOW_H
#define ALIFE_WINDOW_H

#include "SDL2/SDL.h"
#include <stdbool.h>

typedef struct {
    const int width;
    const int height;
    const int frame_delay_ms;

    Uint32 ticks;
    SDL_Window *sdl_window;
    SDL_Surface *sdl_surface;
} Window;

Window *window_create(const char *title, int w, int h, int frame_delay_ms);

bool window_handle_events(Window *window);

void window_update(Window *window);

void window_destroy(Window *window);

#endif //ALIFE_WINDOW_H
