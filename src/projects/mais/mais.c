#include <sys/time.h>
#include "../../tools/tools.h"

#define W 800
#define H 800

#define FRAME_DELAY_MS 1


int main() {

    SDL_Window *window = create_window("Maïs", W, H);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) { return 1; }

    init_random();

    Uint32 ticks = SDL_GetTicks();
    int is_over = 1;

    while (is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);

        Uint32 delay = (SDL_GetTicks() - ticks);
        if (delay < FRAME_DELAY_MS) {
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}