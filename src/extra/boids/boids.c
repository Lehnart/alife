#include "../../tools/tools.h"
#include "bird.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <sys/time.h>

#define W 800
#define H 600

#define BIRD_COUNT 200

#define FRAME_DELAY_MS 0


int main() {

    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long time = 1000000 * tv.tv_sec + tv.tv_usec;
    rand_seed(time, time + 1, time + 2);

    SDL_SetHint (SDL_HINT_RENDER_DRIVER, "opengl") ;
    SDL_Window *p_window = create_window("BOIDS", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);
    SDL_Renderer *p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

    Bird* birds[BIRD_COUNT];
    for(int i =0;i<BIRD_COUNT;i++) birds[i] = bird_new(W,H, BIRD_V_MAX/2.F);

    if (p_window == NULL) { return 1; }
    Uint32 ticks = SDL_GetTicks();
    int is_over = 0;
    while(!is_over){

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 1;
            }
        }

        SDL_SetRenderDrawColor(p_renderer, 32, 32, 32, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(p_renderer);

        Triangle t;
        BirdInteraction interact = {false,false,false};
        int rs[4] = {255, 0,  0,255};
        int gs[4] = {255, 255,  0,0};
        int bs[4] = {255, 0,  255,0};
        int c_index=0;

        for(int i =0;i<BIRD_COUNT;i++){
            Bird* bird = birds[i];
            t = bird_get_triangle(bird);

            interact = bird_interact(bird, birds, BIRD_COUNT, i);

            if(interact.collision) c_index=3;
            else if(interact.alignment) c_index=2;
            else if(interact.cohesion) c_index=1;
            else c_index=0;



            filledTrigonRGBA (p_renderer, (short)t.x1, (short)t.y1, (short)t.x2, (short)t.y2, (short)t.x3, (short)t.y3, rs[c_index], gs[c_index], bs[c_index], 255);
//            circleRGBA	(p_renderer, (short)t.x1, (short)t.y1, BIRD_COLLISION_RADIUS, 0, 255, 0, 255);
//            circleRGBA	(p_renderer, (short)t.x1, (short)t.y1, BIRD_ALIGNMENT_RADIUS, 0, 255, 255, 255);
//            circleRGBA	(p_renderer, (short)t.x1, (short)t.y1, BIRD_COHESION_RADIUS, 0, 0, 255, 255);


            bird_update(bird, 0.01F, -BIRD_TRIANGLE_HEIGHT, -BIRD_TRIANGLE_HEIGHT, W+BIRD_TRIANGLE_HEIGHT, H+BIRD_TRIANGLE_HEIGHT);
        }

        SDL_RenderPresent(p_renderer);
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