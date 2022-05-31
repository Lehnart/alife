#ifndef ALIFE_TOOLS_H
#define ALIFE_TOOLS_H

#include <SDL2/SDL.h>

#define PI 3.14159f

int get_pow(int value, int exponent);

void init_random();
void rand_seed(unsigned long x0, unsigned long y0, unsigned long z0);

float rand_float();
double rand_double();
unsigned long rand_long();
int rand_int(const int max);

SDL_Window* create_window(const char* title, int w, int h);
#endif //ALIFE_TOOLS_H
