#include <malloc.h>
#include "world.h"
#include "agent.h"
#include "../tools.h"

World* world_new(unsigned int w, unsigned int h, unsigned int n_agents, unsigned int n_foods){
    World *world = malloc(sizeof(World));

    world->w = w;
    world->h = h;
    world->agents = malloc(n_agents*sizeof(WorldComponent*));
    for(int i=0; i <n_agents; i++){
        Agent* agent = agent_new();

        int x = rand_int();
        int y = rand_int();
        WorldComponent * component = malloc(sizeof(WorldComponent));
        component->x = x;
        component->y = y;
        component->data = agent;
        world->agents[i] = component;
    }

    world->foods = malloc(n_foods*sizeof(WorldComponent*));
    for(int i=0; i <n_agents; i++){
        int x = rand_int();
        int y = rand_int();
        WorldComponent * component = malloc(sizeof(WorldComponent));
        component->x = x;
        component->y = y;
        component->data = NULL;
        world->agents[i] = component;
    }

    return world;
}