#include <SDL2/SDL.h>
#include <math.h>

#include "../../tools/tools.h"
#include "codon.h"

#define WINDOW_W 640
#define WINDOW_H 480

#define FRAME_DELAY_MS 1
#define CODON_COUNT 100

void draw_circle(SDL_Renderer *renderer, int x, int y, float r, int n_step){

    float step = 2.f*PI/ (float)n_step;
    for(int i=0; i < n_step; i++){
        int ix = x + (int) (r*cosf(step*(float)i));
        int iy = y + (int) (r*sinf(step*(float)i));
        SDL_RenderDrawLine(renderer, x, y, ix, iy);
    }
}

int main() {
    rand_seed(1, 2, 3);

    SDL_SetHint (SDL_HINT_RENDER_DRIVER, "opengl") ;
    SDL_Window *p_window = create_window("JohnnyVon", WINDOW_W, WINDOW_H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);
    SDL_Renderer *renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);

    int r[ARM_TYPE_COUNT] = {255,   0, 255,   0, 255};
    int g[ARM_TYPE_COUNT] = {  0,   0,   0, 255, 255};
    int b[ARM_TYPE_COUNT] = {  0, 255, 255,   0,   0};

    if (p_window == NULL) { return 1; }

    Codon* codons[CODON_COUNT];
    for(int i =0; i < CODON_COUNT; i++) codons[i] = codon_new((float)WINDOW_W,(float)WINDOW_H,3);

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for(int i =0; i < CODON_COUNT; i++)
        {
            Codon *codon1 = codons[i];

            int cx = (int) codon1->x;
            int cy = (int) codon1->y;

            for(int j = 0 ; j < codon1->arm_count; j++){
                Arm* arm = codon1->arms[j];
                enum ARM_TYPE type = codon1->arm_types[j];

                int ix = cx + (int) (arm->length*cosf(arm->angle+codon1->theta));
                int iy = cy + (int) (arm->length*sinf(arm->angle+codon1->theta));
                SDL_SetRenderDrawColor(renderer, 255,255,255, 255);
                SDL_RenderDrawLine(renderer, cx, cy, ix, iy);
                SDL_SetRenderDrawColor(renderer, r[type],g[type],b[type],255);
                draw_circle(renderer, ix, iy, 3, 6);
            }

            SDL_SetRenderDrawColor(renderer, r[ARM_YELLOW],g[ARM_YELLOW],b[ARM_YELLOW],255);
            draw_circle(renderer, cx, cy, 3, 6);

        }
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(p_window);

        Uint32 delay =  (SDL_GetTicks() - ticks);
        if(delay < FRAME_DELAY_MS){
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();

        for(int i =0; i < CODON_COUNT; i++) {
            Codon *codon1 = codons[i];
            codon_update_velocities(codon1);
            codon_update_positions(codon1, (float) WINDOW_W, (float) WINDOW_H);
        }
    }

    SDL_DestroyWindow(p_window);
    SDL_Quit();

    return 0;
}