
#include "../array.h"
#include "../graph.h"
#include "../neural_network.h"
#include "world.h"
#include "../tools.h"
#include <SDL2/SDL.h>

#define W 640
#define H 480
#define FRAME_DELAY_MS 50

int main() {
    int layers[3] = {3, 3, 3};
    NeuralNetwork *nn = neural_network_new(layers, 3);

    Array *inputs = array_new(3);

    double input_doubles[3] = {1., 2., 3.};

    array_set(inputs, 0, &input_doubles[0]);
    array_set(inputs, 1, &input_doubles[1]);
    array_set(inputs, 2, &input_doubles[2]);

    neural_network_evaluate(nn, inputs);

    World* world = world_new(640,480,1000,1000);

    SDL_Window *p_window = create_window("MAIS", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);


    if (p_window == NULL) { return 1; }
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

        world_update(world);
        SDL_FillRect(p_surf, NULL, 0x000000);
        Uint32 *pixels;
        SDL_LockSurface(p_surf);
        pixels = (Uint32*) p_surf->pixels;

        for(unsigned int i = 0; i<world->n_agents; i++){
            WorldComponent * component = world->agents[i];
            int x = component->x;
            int y = component->y;
            pixels[x + (y * W)] = SDL_MapRGBA(p_surf->format, 0, 255, 0, 255);
        }

        for(unsigned int i = 0; i<world->n_foods; i++){
            WorldComponent * component = world->foods[i];
            int x = component->x;
            int y = component->y;
            pixels[x + (y * W)] = SDL_MapRGBA(p_surf->format, 255, 0, 0, 255);
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