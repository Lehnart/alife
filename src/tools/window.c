#include <stdbool.h>
#include "window.h"
#include "SDL2/SDL.h"

Window *window_create(const char *title, const int w, const int h, const int frame_delay_ms) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize the SDL2 library: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window *sdl_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);

    if (!sdl_window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface *sdl_surf = SDL_GetWindowSurface(sdl_window);

    Window init_window = {w, h, frame_delay_ms, 0, sdl_window, sdl_surf};
    Window *window = malloc(sizeof(Window));
    memcpy(window, &init_window, sizeof(Window));
    return window;
}

bool window_handle_events(Window *window) {
    bool should_exit = false;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            should_exit = true;
        }
    }
    return should_exit;
}

void window_update(Window *window) {
    Uint32 delay = (SDL_GetTicks() - window->ticks);
    if (delay < window->frame_delay_ms) {
        SDL_Delay(window->frame_delay_ms - delay);
    }
    window->ticks = SDL_GetTicks();
    SDL_UpdateWindowSurface(window->sdl_window);
}
