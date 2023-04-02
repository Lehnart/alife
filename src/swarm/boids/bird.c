#include "bird.h"
#include "math.h"
#include "../../tools/tools.h"

Bird *bird_new(float max_x, float max_y, float max_v) {

    Bird *bird = malloc(sizeof(Bird));

    bird->x = rand_float() * max_x;
    bird->y = rand_float() * max_y;

    float v = rand_float() * max_v;
    float theta = (rand_float() * 2.F * PI) - PI;
    bird->vx = v * cosf(theta);
    bird->vy = v * sinf(theta);

    return bird;
}

BirdInteraction bird_interact(Bird *bird, Bird **birds, int n_bird, int current_bird_index) {
    BirdInteraction interaction = {false, false, false};

    bird->ax = 0.F;
    bird->ay = 0.F;

    int cohesion_n = 0;
    float cx = 0.F;
    float cy = 0.F;

    int alignment_n = 0;
    float vx = 0.F;
    float vy = 0.F;

    int collision_n = 0;
    float xx = 0.F;
    float yy = 0.F;
    float dd = 0.F;

    for (int i = 0; i < n_bird; i++) {
        if (i == current_bird_index) continue;

        Bird *obird = birds[i];
        float d = sqrtf(powf(bird->x - obird->x, 2) + powf(bird->y - obird->y, 2));

        if (d < BIRD_COLLISION_RADIUS) {
            collision_n++;
            xx += (bird->x - obird->x) / d / d;
            yy += (bird->y - obird->y) / d / d;
        }
        if (d < BIRD_ALIGNMENT_RADIUS) {
            alignment_n++;
            vx += obird->vx;
            vy += obird->vy;
        }
        if (d < BIRD_COHESION_RADIUS) {
            cx += obird->x;
            cy += obird->y;
            cohesion_n++;
        }
    }
    if (collision_n != 0) {
        interaction.collision = true;

        xx /= (float) collision_n;
        yy /= (float) collision_n;

        float theta = atan2f(yy, xx);

        bird->ax += BIRD_COLLISION_ACCELERATION * cosf(theta);
        bird->ay += BIRD_COLLISION_ACCELERATION * sinf(theta);
    }
    if (alignment_n != 0) {
        interaction.alignment = true;

        vx /= (float) alignment_n;
        vy /= (float) alignment_n;

        float dx = vx - bird->vx;
        float dy = vy - bird->vy;
        float theta = atan2f(dy, dx);

        bird->ax += BIRD_ALIGNMENT_ACCELERATION * cosf(theta);
        bird->ay += BIRD_ALIGNMENT_ACCELERATION * sinf(theta);
    }
    if (cohesion_n != 0) {
        interaction.cohesion = true;
        cx /= (float) cohesion_n;
        cy /= (float) cohesion_n;

        float dx = cx - bird->x;
        float dy = cy - bird->y;
        float theta = atan2f(dy, dx);

        bird->ax += BIRD_COHESION_ACCELERATION * cosf(theta);
        bird->ay += BIRD_COHESION_ACCELERATION * sinf(theta);
    }


    return interaction;
}

void bird_update(Bird *bird, float dt, float min_x, float min_y, float max_x, float max_y) {
    bird->vx += bird->ax * dt;
    bird->vy += bird->ay * dt;

    bird->x += bird->vx * dt;
    bird->y += bird->vy * dt;

    if (bird->x < min_x) bird->x = bird->x - min_x + max_x;
    if (bird->y < min_y) bird->y = bird->y - min_y + max_y;
    if (bird->x > max_x) bird->x = bird->x - max_x + min_x;
    if (bird->y > max_y) bird->y = bird->y - max_y + min_x;

    float v = sqrtf(powf(bird->vx, 2) + powf(bird->vy, 2));

    float scale = BIRD_V_MAX / v;
    bird->vx *= scale;
    bird->vy *= scale;

}

Triangle bird_get_triangle(Bird *bird) {

    Triangle triangle;

    triangle.x1 = bird->x;
    triangle.y1 = bird->y;

    float theta = atan2f(-bird->vy, -bird->vx);
    float xb = bird->x + (BIRD_TRIANGLE_HEIGHT * cosf(theta));
    float yb = bird->y + (BIRD_TRIANGLE_HEIGHT * sinf(theta));
    float dx = (BIRD_TRIANGLE_WIDTH * cosf(theta + (PI / 2.F)));
    float dy = (BIRD_TRIANGLE_WIDTH * sinf(theta + (PI / 2.F)));

    triangle.x2 = xb + dx;
    triangle.y2 = yb + dy;

    triangle.x3 = xb - dx;
    triangle.y3 = yb - dy;

    return triangle;
}