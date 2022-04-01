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
    unsigned int component : 4;
    unsigned int special : 2;
    unsigned int growth : 1;
    unsigned int bound : 1;
} State;

#endif //ALIFE_STATE_H
