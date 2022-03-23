#include <malloc.h>
#include "agent.h"

Agent* agent_new(){
    Agent* agent = malloc(sizeof(Agent));
    return agent;
}