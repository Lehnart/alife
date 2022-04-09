#ifndef ALIFE_CODON_H
#define ALIFE_CODON_H

#include <stdbool.h>
#define TIMESTEP_DURATION 0.05f

enum ARM_TYPE {
    ARM_RED, ARM_BLUE, ARM_PURPLE, ARM_GREEN, ARM_YELLOW, ARM_TYPE_COUNT
} ;

typedef struct Arm{
    float length;
    float angle;
} Arm;

typedef struct Codon{
    float x;
    float y;
    float theta;

    float vx;
    float vy;
    float vtheta;

    bool left_arm_field_size;
    bool right_arm_field_size;
    bool top_arm_field_size;
    bool center_arm_field_size;

    void* left_arm_neighbor;
    void* right_arm_neighbor;
    void* top_arm_neighbor;

    int strand_location_state;
    int splitting_state;

    Arm **arms;
    enum ARM_TYPE *arm_types;
    int arm_count;

} Codon;

Codon* codon_new(float max_x, float max_y, int arm_count);
void codon_update_velocities(Codon* codon);
void codon_update_positions(Codon* codon, float max_x, float max_y);

#endif //ALIFE_CODON_H
