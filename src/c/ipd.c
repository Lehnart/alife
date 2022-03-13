#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "cell_array.h"
#include "ipd_rule.h"
#include "tools.h"

#define WINDOW_W 400
#define WINDOW_H 300

#define GRID_W 300
#define GRID_H 300

#define LEGEND_X_OFFSET 10
#define LEGEND_Y_OFFSET 6
#define LEGEND_RECT_H 12
#define LEGEND_RECT_W 25

#define CHAR_W 4
#define CHAR_X_OFFSET 2
#define CHAR_Y_OFFSET 2
#define CHAR_H 8

#define BAR_MAX_W 50
#define BAR_H 3

#define STATE_COUNT 16
#define FRAME_DELAY_MS 50

int one_array[CHAR_H][CHAR_W] = {
        { 0,  0,  1,  1},
        { 0,  1,  0,  1},
        { 1,  0,  0,  1},
        { 0,  0,  0,  1},
        { 0,  0,  0,  1},
        { 0,  0,  0,  1},
        { 0,  0,  0,  1},
        { 0,  0,  0,  1},
};

int zero_array[CHAR_H][CHAR_W] = {
        { 0,  1,  1,  0},
        { 1,  0,  0,  1},
        { 1,  0,  0,  1},
        { 1,  0,  0,  1},
        { 1,  0,  0,  1},
        { 1,  0,  0,  1},
        { 1,  0,  0,  1},
        { 0,  1,  1,  0},
};

void draw_char(Uint32 *pixels, SDL_PixelFormat *format, int x0, int y0, int is_one){
    for (int x = x0; x < x0+CHAR_W; x++) {
        for (int y = y0; y < y0+CHAR_H; y++){
            int w = zero_array[y-y0][x-x0];
            if (is_one){
                w=one_array[y-y0][x-x0];
            }
            pixels[x + (y * WINDOW_W)] = SDL_MapRGBA(format, 128*w, 128*w, 128*w, 255);
        }
    }
}

void draw_bar(Uint32 *pixels, SDL_PixelFormat *format, int x0, int y0, long sum, long total){

    double length = (double) sum / (double) total;
    int length_int = (int) (length*BAR_MAX_W);

    for (int x = x0; x < x0+BAR_MAX_W; x++) {
        for (int y = y0; y < y0+BAR_H; y++){
            if ((x-x0) < length_int) pixels[x + (y * WINDOW_W)] = SDL_MapRGBA(format, 128, 128, 128, 255);
            else pixels[x + (y * WINDOW_W)] = SDL_MapRGBA(format, 0, 0, 0, 255);
        }
    }
}

void draw_legend(const CellArray* pCA, SDL_Surface *p_surf, const int *r, const int *g, const int *b) {

    long state_count[STATE_COUNT];
    for(int i=0; i<STATE_COUNT; i++) state_count[i]=0;
    for (int i = 0; i < GRID_W; i++) {
        for (int j = 0; j < GRID_H; j++) {
            int s = get(pCA, i, j);
            state_count[s]++;
        }
    }


    SDL_LockSurface(p_surf);
    Uint32 *pixels = (Uint32 *) p_surf->pixels;

    for (int i = 0; i < STATE_COUNT; i++) {
        for (int x = GRID_W+LEGEND_X_OFFSET; x < GRID_W+LEGEND_X_OFFSET+LEGEND_RECT_W; x++) {
            for (int y = i*(LEGEND_RECT_H+LEGEND_Y_OFFSET)+LEGEND_Y_OFFSET; y < (i*(LEGEND_RECT_H+LEGEND_Y_OFFSET))+ LEGEND_Y_OFFSET + LEGEND_RECT_H; y++){
                pixels[x + (y * WINDOW_W)] = SDL_MapRGBA(p_surf->format, r[i], g[i], b[i], 255);
            }
        }

        int x0 = GRID_W+LEGEND_X_OFFSET+LEGEND_RECT_W;
        int y0 =  i*(LEGEND_RECT_H+LEGEND_Y_OFFSET)+LEGEND_Y_OFFSET + CHAR_Y_OFFSET;


        draw_char(pixels, p_surf->format, x0 + CHAR_X_OFFSET, y0, i & 8);
        draw_char(pixels, p_surf->format, x0 + (CHAR_X_OFFSET * 2) + CHAR_W, y0, i & 4);
        draw_char(pixels, p_surf->format, x0 + (CHAR_X_OFFSET * 3) + (CHAR_W * 2), y0, i & 2);
        draw_char(pixels, p_surf->format, x0 + (CHAR_X_OFFSET * 4) + (CHAR_W * 3), y0, i & 1);

        draw_bar(pixels, p_surf->format, GRID_W+LEGEND_X_OFFSET,  (i*(LEGEND_RECT_H+LEGEND_Y_OFFSET))+ LEGEND_Y_OFFSET + LEGEND_RECT_H, state_count[i], GRID_W*GRID_W);

    }
    SDL_UnlockSurface(p_surf);
}

int main() {
    srand(time(NULL));

    SDL_Window *p_window = create_window("IPD", WINDOW_W, WINDOW_H);
    SDL_Renderer *p_renderer = SDL_CreateRenderer(p_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    int states[STATE_COUNT];
    double cumulative_probas[STATE_COUNT];//= {0.25,0.5,0.75,1.,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,1.0};
    for (int i = 0; i < STATE_COUNT; i++) {
        cumulative_probas[i] = (double) (i + 1) / (double) STATE_COUNT;
        states[i] = i;
    }
    CellArray *ca = random_cell_array(GRID_W, GRID_H, states, cumulative_probas);

    int r[STATE_COUNT] = {32, 31, 255, 44, 214, 148, 140, 227, 127, 188, 23, 174, 255, 152, 255, 192};
    int g[STATE_COUNT] = {32, 119, 127, 160, 39, 103, 86, 119, 127, 189, 190, 199, 187, 223, 152, 192};
    int b[STATE_COUNT] = {32, 180, 14, 44, 40, 149, 75, 194, 127, 34, 207, 232, 120, 138, 150, 192};
    IPDRule rule = {
            0.10f,
            0.02f,

            1.f,
            0.333f,
            0.f,
            1.666f,

            25,
            2,
            STATE_COUNT
    };

    Uint32 ticks = SDL_GetTicks();
    int is_over = 1;
    int generation = 0;
    while (is_over) {

        printf("Generation %i\n", generation);
        generation += 1;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT) {
                is_over = 0;
            }
        }

        Uint32 *pixels;
        int i, j;

        SDL_LockSurface(p_surf);
        pixels = (Uint32 *) p_surf->pixels;
        for (i = 0; i < GRID_W; i++) {
            for (j = 0; j < GRID_H; j++) {
                int s = get(ca, i, j);
                pixels[i + (j * WINDOW_W)] = SDL_MapRGBA(p_surf->format, r[s], g[s], b[s], 255);
            }
        }
        SDL_UnlockSurface(p_surf);

        draw_legend(ca, p_surf, r, g, b);
        SDL_UpdateWindowSurface(p_window);

        Uint32 delay = (SDL_GetTicks() - ticks);
        if (delay < FRAME_DELAY_MS) {
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();


        evolve(ca, &rule);
    }

    SDL_DestroyWindow(p_window);

    SDL_Quit();
    return 0;
}