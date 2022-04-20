
#include "ant.h"
#include "../../tools/tools.h"

Ant* ant_new(float max_x, float max_y){

    Ant* ant = malloc(sizeof(Ant));
    ant->x = rand_float()*max_x;
    ant->y = rand_float()*max_y;

    float angle = (rand_float()*2.F*PI) - PI;
    ant->vx = ANT_V_MAX*cosf(angle);
    ant->vy = ANT_V_MAX*sinf(angle);

    return ant;

}

float ant_angle(Ant* ant){
    return atan2f(ant->vy, ant->vx);
}

AntInteraction ant_interact(Ant* ant, Ant** ants, int n_ant, int current_ant_index){
    AntInteraction interaction = {false,false,false};
    ant->ax = 0.F;
    ant->ay = 0.F;

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

    for(int i=0; i<n_ant; i++){
        if(i == current_ant_index) continue;

        Ant* oant = ants[i];
        float d = sqrtf( powf(ant->x - oant->x, 2) + powf(ant->y - oant->y, 2));

        if(d < ANT_COLLISION_RADIUS){
            collision_n++;
            xx += (ant->x - oant->x)/d/d;
            yy += (ant->y - oant->y)/d/d;
        }
        if(d < ANT_ALIGNMENT_RADIUS){
            alignment_n++;
            vx += oant->vx;
            vy += oant->vy;
        }
        if(d < ANT_COHESION_RADIUS){
            cx += oant->x;
            cy += oant->y;
            cohesion_n++;
        }
    }
    if(collision_n != 0) {
        interaction.collision = true;

        xx /= (float) collision_n;
        yy /= (float) collision_n;

        float theta = atan2f(yy, xx);

        ant->ax += ANT_COLLISION_ACCELERATION * cosf(theta);
        ant->ay += ANT_COLLISION_ACCELERATION * sinf(theta);
    }
    if(alignment_n != 0) {
        interaction.alignment = true;

        vx /= (float) alignment_n;
        vy /= (float) alignment_n;

        float dx = vx - ant->vx;
        float dy = vy - ant->vy;
        float theta = atan2f(dy, dx);

        ant->ax += ANT_ALIGNMENT_ACCELERATION * cosf(theta);
        ant->ay += ANT_ALIGNMENT_ACCELERATION * sinf(theta);
    }
    if(cohesion_n != 0) {
        interaction.cohesion = true;
        cx /= (float) cohesion_n;
        cy /= (float) cohesion_n;

        float dx = cx - ant->x;
        float dy = cy - ant->y;
        float theta = atan2f(dy, dx);

        ant->ax += ANT_COHESION_ACCELERATION * cosf(theta);
        ant->ay += ANT_COHESION_ACCELERATION * sinf(theta);
    }

    return interaction;
}

void ant_update(Ant* ant, float dt, float min_x, float min_y, float max_x, float max_y){
    ant->vx += ant->ax*dt;
    ant->vy += ant->ay*dt;

    ant->x += dt * ant->vx;
    ant->y += dt * ant->vy;

    if(ant->x < min_x) ant->x = ant->x - min_x + max_x;
    if(ant->y < min_y) ant->y = ant->y - min_y + max_y;
    if(ant->x > max_x) ant->x = ant->x - max_x + min_x;
    if(ant->y > max_y) ant->y = ant->y - max_y + min_x;

    float v = sqrtf(powf(ant->vx,2) + powf(ant->vy, 2));

    float scale = ANT_V_MAX/v;
    ant->vx *= scale;
    ant->vy *= scale;
}