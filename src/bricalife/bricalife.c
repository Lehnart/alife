#include <sys/time.h>
#include "../tools/tools.h"
#include "../tools/cell_array.h"
#include "atom.h"

#define ATOM_COUNT 1000
#define ATOM_SIZE 8

#define W 800
#define H 800

#define FRAME_DELAY_MS 1


int main() {

    SDL_Window *window = create_window("Bricalife", W, H);
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) { return 1; }

    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long m1 = te.tv_usec/1000;
    gettimeofday(&te, NULL); // get current time
    long long m2 = te.tv_usec/1000;
    gettimeofday(&te, NULL); // get current time
    long long m3 = te.tv_usec/1000;
    rand_seed(m1,m2,m3);

    World *world = world_new(W/ATOM_SIZE,H/ATOM_SIZE);
    Atom atoms[ATOM_COUNT];
    for(int i = 0; i < ATOM_COUNT; i++){
        atoms[i].x = W/ATOM_SIZE/2;
        atoms[i].y = H/ATOM_SIZE/2;
        atoms[i].type = ATOM_CARBON;
    }

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

        SDL_Rect rect;
        int carbon_count;
        int color;
        for(int i =0 ; i < world->width; i++){
            for(int j=0; j < world->height; j++){
                carbon_count = world_get(world,i,j,ATOM_CARBON);
                if(carbon_count>0){
                    carbon_count = carbon_count>8 ? 8: carbon_count;
                    color = (32*carbon_count)-1;
                    rect.x = i*ATOM_SIZE;
                    rect.y = j*ATOM_SIZE;
                    rect.w = ATOM_SIZE;
                    rect.h = ATOM_SIZE;
                    SDL_SetRenderDrawColor(renderer, 255, color, color, 255);
                    SDL_RenderFillRect(renderer, &rect);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);

        world_reset(world);
        for(int i = 0; i <ATOM_COUNT; i++) atom_update(&atoms[i], world);

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