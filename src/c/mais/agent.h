#ifndef ALIFE_AGENT_H
#define ALIFE_AGENT_H

typedef enum Action {
    ACTION_NONE, ACTION_TURN_LEFT, ACTION_TURN_RIGHT, ACTION_FORWARD
} Action ;

typedef enum Direction {
    DIRECTION_UP, DIRECTION_RIGHT, DIRECTION_DOWN, DIRECTION_LEFT
} Direction ;


typedef struct Agent{
    Action action;
    Direction direction;
    void (*think)(struct Agent* agent);

} Agent;

Agent* agent_new();

void agent_think(Agent* agent);

#endif //ALIFE_AGENT_H
