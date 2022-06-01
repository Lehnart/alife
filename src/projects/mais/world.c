#include <malloc.h>
#include "world.h"
#include "../../tools/tools.h"


WorldAgent *world_agent_new() {
    WorldAgent *agent = malloc(sizeof(WorldAgent));
    return agent;
}

void world_agent_update(WorldAgent *agent, World *world, int pos) {

    int left_index = world_get_position(world, pos - 1);
    int mid_index = world_get_position(world, pos);
    int right_index = world_get_position(world, pos + 1);

    WorldPosition left_position = world->positions[left_index];
    WorldPosition mid_position = world->positions[mid_index];
    WorldPosition right_position = world->positions[right_index];

    int r = rand_int(3);
    agent->action = r;
}

void world_act_agent(World *world, WorldAgent *agent, int pos) {
    if(agent->action == ACTION_NONE) return;

    int agent_pos = world_get_position(world, pos);
    WorldAgent *agent_at_pos = world->positions[agent_pos].agent;
    Action move = agent->action;

    if (agent_at_pos == agent) {
        int next_pos;
        if (move == ACTION_MOVE_LEFT) next_pos = world_get_position(world, pos - 1);
        if (move == ACTION_MOVE_RIGHT) next_pos = world_get_position(world, pos + 1);

        WorldAgent *agent_next = world->positions[next_pos].agent;
        if (agent_next == NULL) {
            world->positions[pos].agent = NULL;
            world->positions[next_pos].agent = agent;
        }
    }

    agent->action = ACTION_NONE;
}

World *world_new(int size) {

    World *world = malloc(sizeof(World));
    WorldPosition *elements = malloc(sizeof(WorldPosition) * size);

    for (int i = 0; i < size; i++) {
        elements[i].agent = NULL;
        elements[i].n_foods = 0;
    }

    world->size = size;
    world->positions = elements;

    return world;
}

int world_get_position(const World *world, int index) {
    if (index < 0) {
        return world_get_position(world, world->size + index);
    }
    if (index >= world->size) {
        return world_get_position(world, index - world->size);
    }
    return index;
}

void world_add_food(World *world, int index) {
    int pos = world_get_position(world, index);
    world->positions[pos].n_foods++;
}

int world_add_agent(World *world, WorldAgent *agent, int index) {
    int pos = world_get_position(world, index);
    if (world->positions[pos].agent == NULL) {
        world->positions[pos].agent = agent;
        return 1;
    }
    return 0;
}


void world_update(World *world) {
    int size = world->size;

    for(int i =0; i<size; i++){
        WorldAgent * agent = world->positions[i].agent;
        if(agent != NULL) world_agent_update(agent, world, i);
    }

    for(int i =0; i<size; i++){
        WorldAgent * agent = world->positions[i].agent;
        if(agent != NULL) world_act_agent(world, agent, i);
    }
}