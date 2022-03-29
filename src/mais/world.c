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
        WorldComponent * agent_component = world->agents[i];
        Agent* agent = (Agent*) agent_component->data;
        Action action = ((Agent*) agent_component->data)->action;
        Direction* direction = &((Agent*) agent_component->data)->direction;
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
            if(*direction==DIRECTION_UP) agent_component->y++;
            else if(*direction==DIRECTION_LEFT) agent_component->x--;
            else if(*direction==DIRECTION_DOWN) agent_component->y--;
            else if(*direction==DIRECTION_RIGHT) agent_component->x++;

            if(agent_component->y < 0) agent_component->y = 0;
            if(agent_component->x < 0) agent_component->x = 0;
            if(agent_component->y >= world->h) agent_component->y = (int) world->h - 1;
            if(agent_component->x >= world->w) agent_component->x = (int) world->w - 1;

        }

        for(int food_index = 0; food_index < world->n_foods; food_index++){
            WorldComponent* food_component = world->foods[food_index];
            if(food_component == NULL){
                continue;
            }
            if(agent_component->x == food_component->x && agent_component->y == food_component->y){
                world->foods[food_index] = NULL;
                agent->n_food_eaten++;
                break;
            }
        }

        agent->n_actions++;
    }

}