#include <limits.h>
#include "tools.h"

static unsigned long x=123456789, y=362436069, z=521288629;

double rand_double(void) {
    return (double) rand_long() / (double)ULONG_MAX;
}

unsigned long rand_long(void) {
    unsigned long t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;

    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

int get_pow(int value, int exponent){
    int result = 1;
    for(int i = 0; i < exponent; i++){
        result *= value;
    }
    return result;
}

SDL_Window* create_window(const char* title, int w, int h){

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr,"Failed to initialize the SDL2 library: %s\n",SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w, h,0);

    if(!window)
    {
        fprintf(stderr,"Failed to create window: %s\n",SDL_GetError());
        return NULL;
    }

    return window;
}