#include <malloc.h>
#include "world.h"
#include "../../tools/tools.h"


WorldAgent *world_agent_new(int hp) {
    WorldAgent *agent = malloc(sizeof(WorldAgent));
    agent->action = ACTION_NONE;
    agent->hp = hp;

    size_t n = sizeof(agent->transition_rules)/sizeof(agent->transition_rules[0]);
    SensorResult r;
    for(int i = 0; i < n; i++){
        r.result = i;
        if(r.is_food_at_mid) agent->transition_rules[i] = ACTION_EAT;
        else agent->transition_rules[i] = ACTION_MOVE_RIGHT;
    }
    return agent;
}

void world_agent_delete(WorldAgent * agent) {
    free(agent);
}

SensorResult world_agent_sense(WorldAgent *agent, World *world, int pos) {

    SensorResult r;

    int left_index = world_get_position(world, pos - 1);
    int mid_index = world_get_position(world, pos);
    int right_index = world_get_position(world, pos + 1);

    WorldPosition left_position = world->positions[left_index];
    WorldPosition mid_position = world->positions[mid_index];
    WorldPosition right_position = world->positions[right_index];

    r.is_agent_at_left  = left_position.agent == NULL ? 0 : 1;
    r.is_agent_at_mid   = 1;
    r.is_agent_at_right = right_position.agent == NULL ? 0 : 1;

    r.is_food_at_left  = left_position.n_foods > 0 ? 1 : 0;
    r.is_food_at_mid   = mid_position.n_foods > 0 ? 1 : 0;
    r.is_food_at_right = right_position.n_foods > 0 ? 1 : 0;

    return r;
}

void world_agent_update(WorldAgent *agent, World *world, int pos) {
    SensorResult r = world_agent_sense(agent, world, pos);
    agent->action = agent->transition_rules[r.result];
}

void world_act_agent(World *world, WorldAgent *agent, int pos) {
    if(agent->action == ACTION_NONE) return;

    int agent_pos = world_get_position(world, pos);
    int *food_count = &world->positions[agent_pos].n_foods;
    WorldAgent *agent_at_pos = world->positions[agent_pos].agent;
    Action move = agent->action;

    if (agent_at_pos == agent) {
        int next_pos = agent_pos;
        if (move == ACTION_MOVE_LEFT) next_pos = world_get_position(world, pos - 1);
        if (move == ACTION_MOVE_RIGHT) next_pos = world_get_position(world, pos + 1);

        if (move == ACTION_EAT && *food_count > 0){
            (*food_count)--;
            agent->hp++;
        }

        WorldAgent *agent_next = world->positions[next_pos].agent;
        if (agent_next == NULL) {
            world->positions[pos].agent = NULL;
            world->positions[next_pos].agent = agent;
        }
    }

    agent->action = ACTION_NONE;
    agent->hp--;
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
        if(agent != NULL){
            world_act_agent(world, agent, i);
            if (agent->hp <= 0){
                world->positions[i].agent= NULL;
            }
        }
    }
}