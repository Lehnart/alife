#include <malloc.h>
#include "agent.h"
#include "../tools.h"

Agent* agent_new(){
    Agent* agent = malloc(sizeof(Agent));
    agent->action = rand_int(5);
    agent->direction = rand_int(4);
    agent->think = agent_think;

    return agent;
}

void agent_think(Agent* agent){
    agent->action = rand_int(5);
}
