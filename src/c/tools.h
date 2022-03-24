#ifndef ALIFE_TOOLS_H
#define ALIFE_TOOLS_H

#include <SDL2/SDL.h>

int get_pow(int value, int exponent);

double rand_double();
unsigned long rand_long();
int rand_int(const int max);

SDL_Window* create_window(const char* title, int w, int h);
#endif //ALIFE_TOOLS_H
