#ifndef ALIFE_STATE_H
#define ALIFE_STATE_H

enum ComponentEnum {
    COMP_QUIESCENT,
    COMP_O,
    COMP_RIGHT,
    COMP_DOWN,
    COMP_LEFT,
    COMP_UP,
    COMP_BIRTH,
    COMP_LEFT_TURN,
    COMP_CORNER,
    COMP_E,
    COMP_F,
    COMP_D,
};

enum SpecialEnum {
    SPECIAL_NONE,
    SPECIAL_BRANCH,
    SPECIAL_DELETE,
    SPECIAL_BOUND
};


typedef struct State{
    int component : 4;
    int special : 2;
    int growth : 1;
    int bound : 1;
} State;

State* state_create();

#endif //ALIFE_STATE_H
