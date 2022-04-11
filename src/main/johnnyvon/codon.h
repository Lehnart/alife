#ifndef ALIFE_CODON_H
#define ALIFE_CODON_H

#include <stdbool.h>

#define TIMESTEP_DURATION 0.05f

#define FORCE_ROTATION 0.10f
#define FORCE_TRANSLATION 1.f

#define V_XY_MAX 2.f
#define V_THETA_MAX 2.f

#define MAX_INTERACTION_DISTANCE 20.f

enum ARM_TYPE {
    ARM_RED, ARM_BLUE, ARM_PURPLE, ARM_GREEN, ARM_YELLOW, ARM_TYPE_COUNT
} ;

typedef struct Arm{
    float length;
    float angle;
    float radius;

    struct Arm* bound;
    enum ARM_TYPE type;
} Arm;

typedef struct Codon{
    float x;
    float y;
    float theta;

    float vx;
    float vy;
    float vtheta;

    float ax;
    float ay;
    float atheta;

    float center_field_radius;
    int strand_location_state;
    int splitting_state;

    int arm_count;
    Arm **arms;

} Codon;

Codon* codon_new(float max_x, float max_y);
void codon_update_velocities(Codon* codon);
void codon_update_positions(Codon* codon, float max_x, float max_y);
void codon_interact(Codon* codon1, Codon* codon2);

void codon_get_arm_position(Codon* codon, Arm* arm, float* x, float* y);

#endif //ALIFE_CODON_H
