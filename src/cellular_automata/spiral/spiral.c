#include <time.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "../../tools/cell_array.h"
#include "spiral_rule.h"
#include "../../tools/tools.h"

#define W 800
#define H 800
#define STATE_COUNT 6
#define FRAME_DELAY_MS 50

int main() {
    srand(time(NULL));

    SDL_Window *p_window = create_window("Spiral", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    int states[STATE_COUNT] = {0, 1, 2, 3, 4, 5};
    double cumulative_probas[STATE_COUNT] = {0.9, 0.92, 0.94, 0.96, 0.98, 1.};

    CellArray *ca = random_cell_array(W, H, states, cumulative_probas);

    int r[STATE_COUNT] = {0, 192, 0, 0, 192, 192};
    int g[STATE_COUNT] = {0, 0, 192, 0, 0, 192};
    int b[STATE_COUNT] = {0, 0, 0, 192, 192, 0};

    int catalytic_states[STATE_COUNT] = {-1, 2, 3, 4, 5, 1};
    float probas[STATE_COUNT] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    SpiralRule rule = {
            0.10f,
            11.f,
            1.f,
            100.f,
            STATE_COUNT,
            catalytic_states,
            probas
    };

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


        evolve(ca, &rule);
        Uint32 *pixels;
        int i, j;

        SDL_LockSurface(p_surf);
        pixels = (Uint32 *) p_surf->pixels;
        for (i = 0; i < W; i++) {
            for (j = 0; j < H; j++) {

                int state_count[STATE_COUNT] = {0, 0, 0, 0, 0, 0};
                CellNeighborhood cn = ca_get_neighborhood(ca, i, j);
                for (int index = 0; index < 9; index++) {
                    int s = cn.states[index];
                    state_count[s]++;
                }
                int max = 0;
                int s_max = -1;

                for (int index = 0; index < STATE_COUNT; index++) {
                    if (state_count[index] > max) {

                        max = state_count[index];
                        s_max = index;
                    }
                }
                pixels[i + (j * W)] = SDL_MapRGBA(p_surf->format, r[s_max], g[s_max], b[s_max], 255);
            }
        }
        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);
        Uint32 delay = (SDL_GetTicks() - ticks);
        if (delay < FRAME_DELAY_MS) {
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();
    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}