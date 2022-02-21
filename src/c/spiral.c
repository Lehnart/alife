#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include "cell_array.h"

#define W 300
#define H 300
#define STATE_COUNT 6

SDL_Window* create_window(char* title, int w, int h){

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

    printf("Hello World!");

    SDL_Window *p_window = create_window("Test", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    int states[STATE_COUNT] = {0, 1, 2, 3, 4, 5};
    double cumulative_probas[STATE_COUNT] = {0.9, 0.92, 0.94, 0.96, 0.98, 1.};

    CellArray *ca = random_cell_array(W, H, states, cumulative_probas);

    int r[STATE_COUNT] = {0,192,0,0,192,192};
    int g[STATE_COUNT] = {0,0,192,0,0,192};
    int b[STATE_COUNT] = {0,0,0,192,192,0};

    int catalytic_states[STATE_COUNT] = {-1,2,3,4,5,1};
    float probas[STATE_COUNT] = {0.f,0.f,0.f,0.f,0.f,0.f};
    SpiralRule rule = {
            0.15f,
            11.f,
            1.f,
            100.f,
            STATE_COUNT,
            catalytic_states,
            probas
    };

    int ticks = SDL_GetTicks();

    while(1){
        evolve(ca, &rule);
        Uint32 *pixels;
        size_t i, j;

        SDL_LockSurface(p_surf);
        pixels = p_surf->pixels;
        for(i = 0; i < W; i++)
        {
            for(j = 0; j < H; j++) {
                int s = ca->array[i + (j * W)];
                pixels[i + (j * W)] = SDL_MapRGBA(p_surf->format, r[s], g[s], b[s], 255);
            }
        }
        SDL_UnlockSurface(p_surf);
        SDL_Delay(50 - (SDL_GetTicks() - ticks));
        ticks = SDL_GetTicks();
        SDL_UpdateWindowSurface(p_window);
    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}