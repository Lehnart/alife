#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../tools/cell_array.h"
#include "../../tools/tools.h"

#define W 120
#define H 120
#define STATE_COUNT 6
#define FRAME_DELAY_MS 1

void evolve(CellArray* pCA, const int* rule) {

    int *intermediate_array = malloc( pCA->w*pCA->h*sizeof(int));

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            CellNeighborhood cn = get_neighborhood(pCA, x, y);
            int s = 0;
            s += cn.m*10000;
            s += cn.t*1000;
            s += cn.r*100;
            s += cn.b*10;
            s += cn.l*1;

            intermediate_array[x + (pCA->w * y)] = rule[s];
        }
    }

    for (int y = 0; y < pCA->h; y++) {
        for (int x = 0; x < pCA->w; x++) {
            pCA->array[x + (pCA->w * y)] = intermediate_array[x + (pCA->w * y)];
        }
    }
    free(intermediate_array);
}


int main() {

    SDL_Window *p_window = create_window("Byl", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    CellArray *ca = cell_array(W, H);
    FILE* array_file = fopen("res/byl_array.txt", "r");
    int index = 0;
    int c;
    c = fgetc(array_file);
    while(c != '\0' && c != -1 ){

        if(c >= '0' && c <= '9'){
            ca->array[index]=(c-'0');
            index++;
        }
        c = fgetc(array_file);
    }
    fclose(array_file);

    int r[STATE_COUNT] = {  0,192,  0,  0,192,192};
    int g[STATE_COUNT] = {  0,  0,192,  0,  0,192};
    int b[STATE_COUNT] = {  0,  0,  0,192,192,  0};

    int rule[100000]= {0};
    FILE* file = fopen("res/byl_rule.txt", "r");

    char buffer[7]= {0};
    fgets(buffer,10,file);

    while(buffer[0] >= '0' && buffer[0] <= '9'){
        int s = 0;
        s += (buffer[0]-'0')*10000;
        s += (buffer[1]-'0')*1000;
        s += (buffer[2]-'0')*100;
        s += (buffer[3]-'0')*10;
        s += (buffer[4]-'0')*1;
        rule[s] = buffer[5]-'0';

        s = 0;
        s += (buffer[0]-'0')*10000;
        s += (buffer[4]-'0')*1000;
        s += (buffer[1]-'0')*100;
        s += (buffer[2]-'0')*10;
        s += (buffer[3]-'0')*1;
        rule[s] = buffer[5]-'0';

        s = 0;
        s += (buffer[0]-'0')*10000;
        s += (buffer[3]-'0')*1000;
        s += (buffer[4]-'0')*100;
        s += (buffer[1]-'0')*10;
        s += (buffer[2]-'0')*1;
        rule[s] = buffer[5]-'0';


        s = 0;
        s += (buffer[0]-'0')*10000;
        s += (buffer[2]-'0')*1000;
        s += (buffer[3]-'0')*100;
        s += (buffer[4]-'0')*10;
        s += (buffer[1]-'0')*1;
        rule[s] = buffer[5]-'0';

        printf("buffer %s \n", buffer);
        printf("s = %i, rule[s] = %i\n", s, rule[s]);

        buffer[0] = '\0';
        fgets(buffer,10,file);
    }
    fclose(file);

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

        evolve(ca, rule);
    }

    SDL_DestroyWindow(p_window);
    SDL_Quit();

    return 0;
}