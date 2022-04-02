#include <SDL2/SDL.h>
#include <malloc.h>
#include "../../tools/cell_array.h"
#include "../../tools/tools.h"

#define W 640
#define H 480
#define STATE_COUNT 9
#define FRAME_DELAY_MS 0

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

            if(cn.m == 8) intermediate_array[x + (pCA->w * y)] = 0;
            else if(cn.t == 8 || cn.b == 8 || cn.l == 8 || cn.r == 8){
                if(cn.m == 0 || cn.m == 1){
                    if(
                        (cn.t >= 2 && cn.t <= 7) ||
                        (cn.r >= 2 && cn.r <= 7) ||
                        (cn.b >= 2 && cn.b <= 7) ||
                        (cn.l >= 2 && cn.l <= 7)
                    )    intermediate_array[x + (pCA->w * y)] = 8;
                    else intermediate_array[x + (pCA->w * y)] = cn.m;
                }

                else if (cn.m == 2 || cn.m == 3 || cn.m == 5) intermediate_array[x + (pCA->w * y)] = 0;
                else if (cn.m == 4 || cn.m == 6 || cn.m == 7) intermediate_array[x + (pCA->w * y)] = 1;
            }
            else intermediate_array[x + (pCA->w * y)] = rule[s];
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

    SDL_Window *p_window = create_window("Evoloop", W, H);
    SDL_Surface *p_surf = SDL_GetWindowSurface(p_window);

    if (p_window == NULL) { return 1; }

    CellArray *ca = ca_create(W, H);
    FILE* array_file = fopen("res/evoloop_array.txt", "r");
    int index = 0;
    int c;
    c = fgetc(array_file);
    while(c != '\0' && c != -1 ){
        if(c >= '0' && c <= '9'){
            ca->array[index]=(c-'0');
            index++;
        }
        else if (c=='\n'){
            index += W - 219;
        }
        c = fgetc(array_file);
    }
    fclose(array_file);

    int r[STATE_COUNT] = {  0,192,  0,  0,192,192,  0,192,256};
    int g[STATE_COUNT] = {  0,  0,192,  0,  0,192,192,192,256};
    int b[STATE_COUNT] = {  0,  0,  0,192,192,  0,192,192,256};

    int rule[100000]= {0};
    for (int i = 0 ; i < 100000; i++) {if (i > 9999) rule[i] = 8;}
    FILE* file = fopen("res/evoloop_rule.txt", "r");

    char buffer[10]= {0};
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