#include <malloc.h>
#include "world.h"
#include "agent.h"
#include "../tools.h"

World* world_new(unsigned int w, unsigned int h, unsigned int n_agents, unsigned int n_foods){
    World *world = malloc(sizeof(World));

    world->w = w;
    world->h = h;
    world->n_agents = n_agents;
    world->agents = malloc(n_agents*sizeof(WorldComponent*));
    for(int i=0; i <n_agents; i++){
        Agent* agent = agent_new();


        int x = rand_int((int) w);
        int y = rand_int((int) h);
        WorldComponent * component = malloc(sizeof(WorldComponent));
        component->x = x;
        component->y = y;
        component->data = agent;
        world->agents[i] = component;
    }

    world->n_foods = n_foods;
    world->foods = malloc(n_foods*sizeof(WorldComponent*));
    for(int i=0; i <n_foods; i++){
        int x = rand_int((int) w);
        int y = rand_int((int) h);
        WorldComponent * component = malloc(sizeof(WorldComponent));
        component->x = x;
        component->y = y;
        component->data = NULL;
        world->foods[i] = component;
    }

    return world;
}

void world_update(World* world){
    for(unsigned int i = 0; i<world->n_agents; i++) {
        WorldComponent * component = world->agents[i];
        Agent* agent = (Agent*) component->data;
        agent->think(agent);
    }

    for(unsigned int i = 0; i<world->n_agents; i++){
        WorldComponent * component = world->agents[i];
        Action action = ((Agent*) component->data)->action;
        Direction* direction = &((Agent*) component->data)->direction;
        if(action == ACTION_NONE){
            continue;
        }
        else if(action == ACTION_TURN_LEFT){
            if(*direction==DIRECTION_UP) *direction=DIRECTION_LEFT;
            else if(*direction==DIRECTION_LEFT) *direction=DIRECTION_DOWN;
            else if(*direction==DIRECTION_DOWN) *direction=DIRECTION_RIGHT;
            else if(*direction==DIRECTION_RIGHT) *direction=DIRECTION_UP;
        }
        else if(action == ACTION_TURN_RIGHT){
            if(*direction==DIRECTION_UP) *direction=DIRECTION_RIGHT;
            else if(*direction==DIRECTION_LEFT) *direction=DIRECTION_UP;
            else if(*direction==DIRECTION_DOWN) *direction=DIRECTION_LEFT;
            else if(*direction==DIRECTION_RIGHT) *direction=DIRECTION_DOWN;
        }
        else if(action == ACTION_FORWARD){
            if(*direction==DIRECTION_UP) component->y++;
            else if(*direction==DIRECTION_LEFT) component->x--;
            else if(*direction==DIRECTION_DOWN) component->y--;
            else if(*direction==DIRECTION_RIGHT) component->x++;

            if(component->y < 0) component->y = 0;
            if(component->x < 0) component->x = 0;
            if(component->y >= world->h) component->y = (int) world->h-1;
            if(component->x >= world->w) component->x = (int) world->w-1;

        }
    }

}