#include <time.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "../../tools/g_cell_array.h"
#include "../../tools/tools.h"

#define W 640
#define H 480
#define STATE_COUNT 6
#define FRAME_DELAY_MS 1

int main() {

    SDL_Window *window = create_window("Reggia", W, H);
    SDL_Surface *surf = SDL_GetWindowSurface(window);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (window == NULL) { return 1; }

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,  SDL_TEXTUREACCESS_STREAMING,3,3);
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    void* temp;
    int pitch;
    Uint32* pixels;
    SDL_LockTexture(texture, NULL, &temp, &pitch);
    pixels = temp;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
            pixels[i * 3 + j] = SDL_MapRGBA(format, 64*(i+1),  64*(j+1), 0, (Uint8) 255);
    }
    SDL_FreeFormat(format);
    SDL_UnlockTexture(texture);


    CellArray *ca = cell_array(W, H);

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
                SDL_RenderCopy(renderer, texture, NULL, &rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
        Uint32 delay =  (SDL_GetTicks() - ticks);
        if(delay < FRAME_DELAY_MS){
            SDL_Delay(FRAME_DELAY_MS - delay);
        }
        ticks = SDL_GetTicks();
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

