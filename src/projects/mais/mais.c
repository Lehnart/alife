#include "../../tools/tools.h"
#include "world.h"

#define WORLD_SIZE 2500

#define FOOD_COUNT 1000
#define FOOD_ENERGY 10

#define AGENT_COUNT 100
#define AGENT_MAX_COUNT 100
#define AGENT_HP 20

#define GRID_WIDTH 50
#define GRID_HEIGHT 50

#define W 800
#define H 800

#define FRAME_DELAY_MS 100


int main() {

    SDL_Window *window = create_window("Maïs", W, H);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL) { return 1; }

    init_random();

    Uint32 ticks = SDL_GetTicks();
    int is_over = 1;

    SDL_Surface* apple_image = SDL_LoadBMP("res/apple.bmp");
    SDL_Texture * apple_texture = SDL_CreateTextureFromSurface(renderer, apple_image);
    int apple_texture_w, apple_texture_h;
    SDL_QueryTexture(apple_texture, NULL, NULL, &apple_texture_w, &apple_texture_h);

    SDL_Surface* hero_image = SDL_LoadBMP("res/hero.bmp");
    SDL_Texture * hero_texture = SDL_CreateTextureFromSurface(renderer, hero_image);
    int hero_texture_w, hero_texture_h;
    SDL_QueryTexture(hero_texture, NULL, NULL, &hero_texture_w, &hero_texture_h);

    World* world = world_new(WORLD_SIZE, FOOD_ENERGY, AGENT_MAX_COUNT);
    for (int i = 0; i<FOOD_COUNT; i++) world_add_food(world, rand_int(WORLD_SIZE));
    for (int i = 0; i<AGENT_COUNT; i++){
        WorldAgent* agent = world_agent_new(AGENT_HP);
        world_add_agent(world, agent, rand_int(WORLD_SIZE));
    }

    while (is_over) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 0;
            }
        }

        world_update(world);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for(int i = 0; i < world->size; i++){

            if(world->positions[i].n_foods != 0) {
                int x = i % GRID_WIDTH * (W / GRID_WIDTH);
                int y = i / GRID_HEIGHT * (H / GRID_HEIGHT);
                SDL_Rect rect = {x, y, apple_texture_w, apple_texture_h};
                SDL_RenderCopy(renderer, apple_texture, NULL, &rect);
            }

            if(world->positions[i].agent != NULL){
                int x = (i % GRID_WIDTH) * (W / GRID_WIDTH);
                int y = (i / GRID_HEIGHT) * (H / GRID_HEIGHT);
                SDL_Rect rect = {x, y, hero_texture_w, hero_texture_h};
                SDL_RenderCopy(renderer, hero_texture, NULL, &rect);
            }
        }


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