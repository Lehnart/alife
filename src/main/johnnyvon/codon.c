#include <malloc.h>
#include "codon.h"
#include "../../tools/tools.h"



Codon* codon_new(float max_x, float max_y, int arm_count){

    Arm **arms = malloc(arm_count*sizeof(Arm*));
    enum ARM_TYPE* arm_types = malloc(arm_count*sizeof(enum ARM_TYPE));

    for(int i=0; i<arm_count;i++){
        Arm *arm = malloc(sizeof(Arm));
        arms[i] = arm;
        arms[i]->length = 0.f;
        arms[i]->angle = 0.f;
        arm_types[i] = rand_int(ARM_TYPE_COUNT);
    }

    arms[0]->length = 10.f;
    arms[0]->angle = 0.f;

    arms[1]->length = 10.f;
    arms[1]->angle = PI;

    arms[2]->length = 5.f;
    arms[2]->angle = PI/2.f;

    Codon* codon = malloc(sizeof(Codon));

    codon->arms = arms;
    codon->arm_count = arm_count;
    codon->arm_types = arm_types;

    codon->x = (float) (rand_double()*max_x);
    codon->y = (float) (rand_double()*max_y);
    codon->theta = 0.f;

    codon->vx = 0.f;
    codon->vy = 0.f;
    codon->vtheta = 0.f;

    codon->center_arm_field_size = rand_double() > 0.5 ? false : true;
    codon->right_arm_field_size = rand_double() > 0.5 ? false : true;
    codon->left_arm_field_size = rand_double() > 0.5 ? false : true;
    codon->top_arm_field_size = rand_double() > 0.5 ? false : true;

    codon->right_arm_neighbor = NULL;
    codon->left_arm_neighbor = NULL;
    codon->top_arm_neighbor = NULL;

    codon->splitting_state = 0;
    codon->strand_location_state = 0;

    return codon;
}

void codon_update_velocities(Codon* codon) {

    float LINEAR_VISCOSITY =  1.f - pow(1 - 0.10, TIMESTEP_DURATION);
    float ANGULAR_VISCOSITY = 1.f - pow(1 - 0.05, TIMESTEP_DURATION);

    codon->vtheta *= (1 - ANGULAR_VISCOSITY);
    codon->vx *= (1 - LINEAR_VISCOSITY);
    codon->vy *= (1 - LINEAR_VISCOSITY);

    codon->vx += TIMESTEP_DURATION * (rand_double() - 0.5) / 2.0;
    codon->vy += TIMESTEP_DURATION * (rand_double() - 0.5) / 2.0;
    codon->vtheta += TIMESTEP_DURATION * (rand_double() - 0.5) / 10.0;

}


void codon_update_positions(Codon* codon, float max_x, float max_y) {

    codon->theta += codon->vtheta * TIMESTEP_DURATION;
    while (codon->theta > 2*PI) codon->theta -= 2*PI;
    while (codon->theta < 0.0f) codon->theta += 2*PI;

    codon->x += codon->vx * TIMESTEP_DURATION;
    if(codon->x < 0.f) codon->x = max_x + codon->x;
    if(codon->x > max_x) codon->x = codon->x - max_x;

    codon->y += codon->vy * TIMESTEP_DURATION;
    if(codon->y < 0.f) codon->y = max_y + codon->y;
    if(codon->y > max_y) codon->y = codon->y - max_y;

}