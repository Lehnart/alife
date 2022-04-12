#include <malloc.h>
#include "codon.h"
#include "../../tools/tools.h"

Codon* codon_new(float max_x, float max_y){

    Codon* codon = malloc(sizeof(Codon));

    int arm_count = 2;
    Arm **arms = malloc(arm_count*sizeof(Arm*));
    enum ARM_TYPE* arm_types = malloc(arm_count*sizeof(enum ARM_TYPE));
    float *arm_field_sizes = malloc(arm_count*sizeof(float));

    for(int i=0; i<arm_count;i++){
        Arm *arm = malloc(sizeof(Arm));
        arms[i] = arm;
        arms[i]->length = 0.f;
        arms[i]->angle = 0.f;
        arms[i]->bound = NULL;
        arms[i]->codon = codon;
    }

    arms[0]->length = 20.f;
    arms[0]->angle = 0.f;
    arms[0]->type = ARM_BLUE;
    arms[0]->radius = 10.f;

    arms[1]->length = 20.f;
    arms[1]->angle = PI;
    arms[1]->type = ARM_RED;
    arms[1]->radius = 10.f;

    //arms[2]->length = 5.f;
    //arms[2]->angle = PI/2.f;



    codon->arms = arms;
    codon->arm_count = arm_count;

    codon->x = (float) (rand_double()*max_x);
    codon->y = (float) (rand_double()*max_y);
    codon->theta = rand_double()*2.f*PI;

    codon->vx = 0.f;
    codon->vy = 0.f;
    codon->vtheta = 0.f;

    codon->ax = 0.f;
    codon->ay = 0.f;
    codon->atheta = 0.f;

    codon->center_field_radius = rand_double() > 0.5 ? 0.01f : 6.f;

    codon->splitting_state = 0;
    codon->strand_location_state = 0;

    return codon;
}

void codon_get_arm_position(Codon* codon, Arm* arm, float* x, float* y){
    *x = codon->x + (arm->length*cosf(arm->angle+codon->theta));
    *y = codon->y + (arm->length*sinf(arm->angle+codon->theta));
}

void codon_update_velocities(Codon* codon) {

    float LINEAR_VISCOSITY =  1.f - pow(1 - 0.2, TIMESTEP_DURATION);
    float ANGULAR_VISCOSITY = 1.f - pow(1 - 0.3, TIMESTEP_DURATION);

    codon->vtheta *= (1 - ANGULAR_VISCOSITY);
    codon->vx *= (1 - LINEAR_VISCOSITY);
    codon->vy *= (1 - LINEAR_VISCOSITY);

    codon->vx += TIMESTEP_DURATION * (rand_double() - 0.5) / 0.4f;
    codon->vy += TIMESTEP_DURATION * (rand_double() - 0.5) / 0.4f;
    codon->vtheta += TIMESTEP_DURATION * (rand_double() - 0.5) / 2.0f;


    codon->vtheta += codon->atheta * TIMESTEP_DURATION;
    codon->vx += codon->ax * TIMESTEP_DURATION;
    codon->vy += codon->ay * TIMESTEP_DURATION;

    if (codon->vtheta < -V_THETA_MAX) codon->vtheta = -V_THETA_MAX;
    if (codon->vtheta >  V_THETA_MAX) codon->vtheta =  V_THETA_MAX;

    if (codon->vx < -V_XY_MAX) codon->vx = -V_XY_MAX;
    if (codon->vx >  V_XY_MAX) codon->vx =  V_XY_MAX;

    if (codon->vy < -V_XY_MAX) codon->vy = -V_XY_MAX;
    if (codon->vy >  V_XY_MAX) codon->vy =  V_XY_MAX;

}

void codon_update_positions(Codon* codon, float max_x, float max_y) {

    codon->theta += codon->vtheta * TIMESTEP_DURATION;
    while (codon->theta > 2*PI) codon->theta -= 2*PI;
    while (codon->theta < 0.0f) codon->theta += 2*PI;

    codon->x += codon->vx * TIMESTEP_DURATION;
    if(codon->x < 0.f) codon->x = 0.f;
    if(codon->x > max_x) codon->x = max_x-0.01f;

    codon->y += codon->vy * TIMESTEP_DURATION;
    if(codon->y < 0.f) codon->y = 0.f;
    if(codon->y > max_y) codon->y = max_y-0.01f;

}

void codon_arm_interact(Codon* codon1, int arm_index1, Codon* codon2, int arm_index2){
    Arm *arm1 = codon1->arms[arm_index1];
    Arm *arm2 = codon2->arms[arm_index2];

    float x1, y1, x2, y2;
    codon_get_arm_position(codon1, arm1, &x1, &y1);
    codon_get_arm_position(codon2, arm2, &x2, &y2);
    float theta1 = codon1->theta;
    float theta2 = codon2->theta;

    if ( arm1->bound != NULL && arm1->bound == arm2 ){

        float dtheta = theta2 - theta1;
        while (dtheta > PI) dtheta -= 2*PI;
        while (dtheta < -PI) dtheta += 2*PI;

        codon1->atheta += dtheta*FORCE_ROTATION*TIMESTEP_DURATION;
        codon2->atheta -= dtheta*FORCE_ROTATION*TIMESTEP_DURATION;

        codon1->ax += (x2-x1)*FORCE_TRANSLATION*TIMESTEP_DURATION;
        codon2->ax -= (x2-x1)*FORCE_TRANSLATION*TIMESTEP_DURATION;

        codon1->ay += (y2-y1)*FORCE_TRANSLATION*TIMESTEP_DURATION;
        codon2->ay -= (y2-y1)*FORCE_TRANSLATION*TIMESTEP_DURATION;

        printf("ax = %f \n", (x2-x1)*FORCE_TRANSLATION*TIMESTEP_DURATION);
        printf("ay = %f \n",  (y2-y1)*FORCE_TRANSLATION*TIMESTEP_DURATION);

        return;
    }

    float r1 = arm1->radius;
    float r2 = arm2->radius;

    float arm_theta1 = codon1->arms[arm_index1]->angle;
    float arm_theta2 = codon2->arms[arm_index2]->angle;

    double d = sqrt(pow(x1 - x2,2.) + pow(y1 - y2,2.));

    double dangle = PI + (theta1 + arm_theta1) - (theta2 + arm_theta2);
    while (dangle > PI) dangle -= 2*PI;
    while (dangle < -PI) dangle += 2*PI;

    if (d < (r1+r2) ) {
        if (arm1->type != arm2->type && arm1->bound == NULL && arm2->bound == NULL ){
            arm1->bound = arm2;
            arm2->bound = arm1;
            printf("bound!\n");
            return;
        }
        else{
            codon1->atheta -= dangle*FORCE_ROTATION*TIMESTEP_DURATION;
            codon2->atheta += dangle*FORCE_ROTATION*TIMESTEP_DURATION;

            codon1->ax -= 1./(x2-x1)*FORCE_TRANSLATION*TIMESTEP_DURATION;
            codon2->ax += 1./(x2-x1)*FORCE_TRANSLATION*TIMESTEP_DURATION;

            codon1->ay -= 1./(y2-y1)*FORCE_TRANSLATION*TIMESTEP_DURATION;
            codon2->ay += 1./(y2-y1)*FORCE_TRANSLATION*TIMESTEP_DURATION;
        }
    }


}

void codon_interact(Codon* codon1, Codon* codon2){
    double d = sqrt(pow(codon1->x - codon2->x,2.) + pow(codon1->y - codon2->y,2.));

    //if (d>MAX_INTERACTION_DISTANCE) return;
    for(int i = 0; i<codon1->arm_count; i++){
        for(int j = 0; j < codon2->arm_count; j++){
            codon_arm_interact(codon1, i, codon2, j);
        }
    }
}

