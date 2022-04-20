#ifndef ALIFE_ANT_H
#define ALIFE_ANT_H

#include <stdbool.h>

#define ANT_V_MAX 1000.F

#define ANT_COLLISION_RADIUS 20
#define ANT_COLLISION_ACCELERATION 30000.f

#define ANT_ALIGNMENT_RADIUS 50
#define ANT_ALIGNMENT_ACCELERATION 10000.f

#define ANT_COHESION_RADIUS 250
#define ANT_COHESION_ACCELERATION 10000.f

typedef struct Ant{
    float x;
    float y;

    float vx;
    float vy;

    float ax;
    float ay;
} Ant;

typedef struct AntInteraction{
    bool cohesion;
    bool alignment;
    bool collision;
} AntInteraction;

Ant* ant_new(float max_x, float max_y);

float ant_angle(Ant* ant);

void ant_update(Ant* ant, float dt, float min_x, float min_y, float max_x, float max_y);
AntInteraction ant_interact(Ant* ant, Ant** ants, int n_ant, int current_ant_index);

#endif //ALIFE_ANT_H
