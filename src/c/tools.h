#ifndef ALIFE_TOOLS_H
#define ALIFE_TOOLS_H

#include <SDL2/SDL.h>

int get_pow(int value, int exponent);

double rand_double(void);
unsigned long rand_long(void);

SDL_Window* create_window(const char* title, int w, int h);
#endif //ALIFE_TOOLS_H
