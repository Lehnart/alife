#include <malloc.h>
#include "agent.h"
#include "../tools.h"

Agent* agent_new(){
    Agent* agent = malloc(sizeof(Agent));
    agent->action = rand_int(5);
    agent->direction = rand_int(4);
    agent->think = agent_think;

    agent->n_actions = 0;
    agent->n_food_eaten = 0;

    return agent;
}

void agent_think(Agent* agent){
    double r = rand_double();
    int action = ACTION_NONE;
    if(r<0.0001){
        action = ACTION_NONE;
    }
    else if(r<0.05){
        action = ACTION_TURN_LEFT;
    }
    else if(r<0.1){
        action = ACTION_TURN_RIGHT;
    }
    else {
        action = ACTION_FORWARD;
    }
    agent->action = action;
}
