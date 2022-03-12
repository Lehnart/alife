#include <limits.h>
#include "tools.h"

static unsigned long x=123456789, y=362436069, z=521288629;

double random(void) {
    return (double) randlong() / (double)ULONG_MAX;
}

unsigned long randlong(void) {
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

int get_pow(int value, int exponant){
    int result = 1;
    for(int i = 0; i < exponant; i++){
        result *= value;
    }
    return result;
}

