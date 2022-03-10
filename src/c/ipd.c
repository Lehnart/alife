#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "cell_array.h"
#include "ipd_rule.h"

#define W 400
#define H 400
#define STATE_COUNT 2
#define FRAME_DELAY_MS 50

SDL_Window* create_window(const char* title, int w, int h){

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,"Failed to initialize the SDL2 library: %s\n",SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w, h,0);

    if(!window)
    {
        fprintf(stderr,"Failed to create window: %s\n",SDL_GetError());
        return NULL;
    }

    return window;
}

int main() {
    srand(time(NULL));

    SDL_Window *p_window = create_window("IPD", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    int states[STATE_COUNT] = {0, 1};
    double cumulative_probas[STATE_COUNT] = {0.5, 1.};
    CellArray *ca = random_cell_array(W, H, states, cumulative_probas);

    int r[STATE_COUNT] = {0,192};
    int g[STATE_COUNT] = {0,192};
    int b[STATE_COUNT] = {0,192};
    IPDRule rule = {
        0.5f,
        0.5f,
        0.5f,
        0.5f,

        1.f,
        0.333f,
        0.f,
        1.666f,

        10
    };

    Uint32 ticks = SDL_GetTicks();
    int is_over = 1;

    while(is_over){

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
        pixels = (Uint32*) p_surf->pixels;
        for(i = 0; i < W; i++)
        {
            for(j = 0; j < H; j++) {
                int s = get(ca, i, j);
                pixels[i + (j * W)] = SDL_MapRGBA(p_surf->format, r[s], g[s], b[s], 255);
            }
        }
        SDL_UnlockSurface(p_surf);
        SDL_UpdateWindowSurface(p_window);
        Uint32 delay =  (SDL_GetTicks() - ticks);
        if(delay < FRAME_DELAY_MS){
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();
    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}