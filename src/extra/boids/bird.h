#ifndef ALIFE_BIRD_H
#define ALIFE_BIRD_H

#include <stdbool.h>

#define BIRD_TRIANGLE_HEIGHT 10.F
#define BIRD_TRIANGLE_WIDTH 2.F

#define BIRD_V_MAX 25.f

#define BIRD_COLLISION_RADIUS 10
#define BIRD_COLLISION_ACCELERATION 30.f

#define BIRD_ALIGNMENT_RADIUS 50
#define BIRD_ALIGNMENT_ACCELERATION 10.f

#define BIRD_COHESION_RADIUS 200
#define BIRD_COHESION_ACCELERATION 10.f



typedef struct Triangle{
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
} Triangle;

typedef struct Bird {
    float x;
    float y;
    float vx;
    float vy;

    float ax;
    float ay;

} Bird;

typedef struct BirdInteraction{
    bool cohesion;
    bool alignment;
    bool collision;
} BirdInteraction;

Bird*                   bird_new(float max_x, float max_y, float max_v);
void                    bird_update(Bird* bird, float dt, float min_x, float min_y, float max_x, float max_y);
BirdInteraction         bird_interact(Bird* bird, Bird** birds, int n_bird, int current_bird_index);
Triangle                bird_get_triangle(Bird* bird);

#endif //ALIFE_BIRD_H
