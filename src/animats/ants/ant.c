
#include "ant.h"
#include "../../tools/tools.h"

Ant *ant_new(float max_x, float max_y) {

    Ant *ant = malloc(sizeof(Ant));
    ant->x = rand_float() * max_x;
    ant->y = rand_float() * max_y;

    float angle = (rand_float() * 2.F * PI) - PI;
    ant->vx = ANT_V_MAX * cosf(angle);
    ant->vy = ANT_V_MAX * sinf(angle);

    ant->is_carrying = false;

    return ant;

}

float ant_angle(Ant *ant) {
    return atan2f(ant->vy, ant->vx);
}

bool ant_seek(Ant *ant) {

    float dx;
    float dy;

    float d = sqrtf(powf(ant->x - TARGET_POS_X, 2) + powf(ant->y - TARGET_POS_Y, 2));
    if (ant->is_carrying == false && d < ANT_SEEK_RADIUS) {
        dx = TARGET_POS_X - ant->x;
        dy = TARGET_POS_Y - ant->y;

        float theta = atan2f(dy, dx);
        ant->ax += ANT_SEEK_ACCELERATION * cosf(theta);
        ant->ay += ANT_SEEK_ACCELERATION * sinf(theta);

        return true;
    }

    if (ant->is_carrying == true) {
        dx = HOME_POS_X - ant->x;
        dy = HOME_POS_Y - ant->y;

        float theta = atan2f(dy, dx);
        ant->ax += ANT_SEEK_ACCELERATION * cosf(theta);
        ant->ay += ANT_SEEK_ACCELERATION * sinf(theta);

        return true;
    }
    return false;
}

bool ant_cohesion(Ant *ant, Ant **ants, int n_ant, int current_ant_index) {
    int cohesion_n = 0;
    float cx = 0.F;
    float cy = 0.F;

    for (int i = 0; i < n_ant; i++) {
        if (i == current_ant_index) continue;

        Ant *oant = ants[i];
        float d = sqrtf(powf(ant->x - oant->x, 2) + powf(ant->y - oant->y, 2));
        if (d < ANT_COHESION_RADIUS) {
            cx += oant->x;
            cy += oant->y;
            cohesion_n++;
        }
    }
    if (cohesion_n != 0) {

        cx /= (float) cohesion_n;
        cy /= (float) cohesion_n;

        float dx = cx - ant->x;
        float dy = cy - ant->y;
        float theta = atan2f(dy, dx);

        ant->ax += ANT_COHESION_ACCELERATION * cosf(theta);
        ant->ay += ANT_COHESION_ACCELERATION * sinf(theta);
        return true;
    }

    return false;
}

bool ant_collision(Ant *ant, Ant **ants, int n_ant, int current_ant_index) {
    int collision_n = 0;
    float xx = 0.F;
    float yy = 0.F;

    for (int i = 0; i < n_ant; i++) {
        if (i == current_ant_index) continue;

        Ant *oant = ants[i];
        float d = sqrtf(powf(ant->x - oant->x, 2) + powf(ant->y - oant->y, 2));
        if (d < ANT_COLLISION_RADIUS) {
            collision_n++;
            xx += (ant->x - oant->x) / d / d;
            yy += (ant->y - oant->y) / d / d;
        }
    }
    if (collision_n != 0) {
        xx /= (float) collision_n;
        yy /= (float) collision_n;

        float theta = atan2f(yy, xx);

        ant->ax += ANT_COLLISION_ACCELERATION * cosf(theta);
        ant->ay += ANT_COLLISION_ACCELERATION * sinf(theta);
        return true;
    }

    return false;
}

bool ant_separation(Ant *ant, Ant **ants, int n_ant, int current_ant_index) {

    int alignment_n = 0;
    float vx = 0.F;
    float vy = 0.F;

    for (int i = 0; i < n_ant; i++) {
        if (i == current_ant_index) continue;

        Ant *oant = ants[i];
        float d = sqrtf(powf(ant->x - oant->x, 2) + powf(ant->y - oant->y, 2));
        if (d < ANT_SEPARATION_RADIUS) {
            alignment_n++;
            vx += oant->vx;
            vy += oant->vy;
        }
    }
    if (alignment_n != 0) {
        vx /= (float) alignment_n;
        vy /= (float) alignment_n;

        float dx = ant->vx - vx;
        float dy = ant->vy - vy;
        float theta = atan2f(dy, dx);

        ant->ax += ANT_SEPARATION_ACCELERATION * cosf(theta);
        ant->ay += ANT_SEPARATION_ACCELERATION * sinf(theta);
        return true;
    }

    return false;
}

AntInteraction ant_interact(Ant *ant, Ant **ants, int n_ant, int current_ant_index) {
    AntInteraction interaction = {false, false, false};
    ant->ax = 0.F;
    ant->ay = 0.F;

    interaction.alignment = ant_separation(ant, ants, n_ant, current_ant_index);
    interaction.cohesion = ant_cohesion(ant, ants, n_ant, current_ant_index);
    interaction.collision = ant_collision(ant, ants, n_ant, current_ant_index);
    interaction.seek = ant_seek(ant);
    return interaction;
}

void ant_update(Ant *ant, float dt, float min_x, float min_y, float max_x, float max_y) {

    ant->vx += ant->ax * dt;
    ant->vy += ant->ay * dt;

    if (ant->x < min_x) ant->x = ant->x - min_x + max_x;
    if (ant->y < min_y) ant->y = ant->y - min_y + max_y;
    if (ant->x > max_x) ant->x = ant->x - max_x + min_x;
    if (ant->y > max_y) ant->y = ant->y - max_y + min_x;

    float v = sqrtf(powf(ant->vx, 2) + powf(ant->vy, 2));

    float scale = ANT_V_MAX / v;
    ant->vx *= scale;
    ant->vy *= scale;

    ant->x += dt * ant->vx;
    ant->y += dt * ant->vy;

    float d = sqrtf(powf(ant->x - TARGET_POS_X, 2) + powf(ant->y - TARGET_POS_Y, 2));
    if (d < 10.F) {
        ant->is_carrying = true;
    }

    d = sqrtf(powf(ant->x - HOME_POS_X, 2) + powf(ant->y - HOME_POS_Y, 2));
    if (d < 10.F) {
        ant->is_carrying = false;
    }

}