#include <time.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../../tools/g_cell_array.h"
#include "../../tools/tools.h"
#include "state.h"
#include "texture.h"

#define W 600
#define H 450

#define STATE_COUNT 6
#define FRAME_DELAY_MS 1000

static State intermediate_array [W*H];

void evolve(CellArray* ca) {
    State *ns;

    for (int y = 0; y < ca->h; y++) {
        for (int x = 0; x < ca->w; x++) {
            CellNeighborhood cn = ca_get_neighborhood(ca, x, y);
            State *m = cn.m;
            State *l = cn.l;

            ns = &intermediate_array[x + (ca->w * y)];
            *ns = *m;

            if (m->component == COMP_O && l->component == COMP_RIGHT ) {
                ns->component = COMP_RIGHT;
            }
            else if (m->component == COMP_RIGHT && l->component == COMP_LEFT_TURN) {
                ns->component = COMP_LEFT_TURN;
            }
            else if (m->component == COMP_RIGHT && l->component == COMP_RIGHT) {
                ns->component = COMP_RIGHT;
            }
            else if (m->component == COMP_LEFT_TURN){
                ns->component = COMP_O;
            }
        }
    }

    State *s;
    for (int y = 0; y < ca->h; y++) {
        for (int x = 0; x < ca->w; x++) {
            s = ca->array[x + (ca->w * y)];
            *s = intermediate_array[x + (ca->w * y)];
        }
    }
}


int main() {

    SDL_Window *window = create_window("Reggia", W, H);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == NULL) { return 1; }

    CellArray *ca = ca_create(W, H, (void* (*)())state_create);
    State* s;
    s = (State *)ca_get(ca,200/2,150/2);
    s->component = COMP_LEFT_TURN;
    s = (State *)ca_get(ca,200/2+1,150/2);
    s->component = COMP_RIGHT;
    s = (State *)ca_get(ca,200/2+2,150/2);
    s->component = COMP_RIGHT;
    s = (State *)ca_get(ca,200/2+3,150/2);
    s->component = COMP_O;
    s = (State *)ca_get(ca,200/2+4,150/2);
    s->component = COMP_O;

    s = (State *)ca_get(ca,200/2,150/2-1);
    s->component = COMP_O;
    s = (State *)ca_get(ca,200/2+2,150/2-1);
    s->component = COMP_O;

    s = (State *)ca_get(ca,200/2,150/2-2);
    s->component = COMP_O;
    s = (State *)ca_get(ca,200/2+1,150/2-2);
    s->component = COMP_O;
    s = (State *)ca_get(ca,200/2+2,150/2-2);
    s->component = COMP_O;

    SDL_Texture* textureO = texture_o(renderer);
    SDL_Texture* textureRight = texture_right(renderer);
    SDL_Texture* textureLeftTurn = texture_left_turn(renderer);



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

        SDL_Rect rect = {0,0,0,0};
        for(int i = 0 ; i < W; i+=3){
            for(int j = 0; j < H; j+=3){
                rect.x = i;
                rect.y = j;
                rect.w = 3;
                rect.h = 3;

                void* d = ca_get(ca, i / 3, j / 3);
                State* s= d;
                SDL_Texture * texture = NULL;
                if(s->component==COMP_O) texture = textureO;
                else if(s->component==COMP_RIGHT) texture = textureRight;
                else if(s->component==COMP_LEFT_TURN) texture = textureLeftTurn;
                if(texture != NULL) SDL_RenderCopy(renderer, texture, NULL, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
        Uint32 delay =  (SDL_GetTicks() - ticks);
        if(delay < FRAME_DELAY_MS){
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();

        evolve(ca);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

