#include <malloc.h>
#include "world.h"
#include "../../tools/tools.h"


WorldAgent *world_agent_new(int hp, int hp_max) {
    WorldAgent *agent = malloc(sizeof(WorldAgent));
    agent->action = ACTION_NONE;
    agent->hp = hp;
    agent->hp_max = hp_max;
    agent->pos = 1;

    size_t n = sizeof(agent->transition_rules) / sizeof(agent->transition_rules[0]);
    SensorResult r;
    for (int i = 0; i < n; i++) {
        r.result = i;
        for (int j = 0; j < 64; j++) agent->transition_rules[j] = rand_int(ACTION_COUNT);
    }
    return agent;
}

void world_agent_decrease_hp(WorldAgent *agent, World *world, int amount) {
    agent->hp -= amount;
    world->free_energy += amount;
}

void world_agent_increase_hp(WorldAgent *agent, World *world, int amount) {
    agent->hp += amount;
    world->free_energy -= amount;
}

SensorResult world_agent_sense(WorldAgent *agent, World *world) {

    SensorResult r;
    r.result = 0;

    int pos = agent->pos;
    int left_index = world_get_position(world, pos - 1);
    int mid_index = world_get_position(world, pos);
    int right_index = world_get_position(world, pos + 1);

    WorldPosition left_position = world->positions[left_index];
    WorldPosition mid_position = world->positions[mid_index];
    WorldPosition right_position = world->positions[right_index];

    r.is_agent_at_left = left_position.agent == NULL ? 0 : 1;
    r.is_agent_at_mid = 1;
    r.is_agent_at_right = right_position.agent == NULL ? 0 : 1;

    r.is_food_at_left = left_position.n_foods > 0 ? 1 : 0;
    r.is_food_at_mid = mid_position.n_foods > 0 ? 1 : 0;
    r.is_food_at_right = right_position.n_foods > 0 ? 1 : 0;

    return r;
}

void world_agent_update(WorldAgent *agent, World *world) {
    SensorResult r = world_agent_sense(agent, world);
    agent->action = agent->transition_rules[r.result];
}

void world_act_agent(World *world, WorldAgent *agent) {
    if (agent->action == ACTION_NONE) return;

    int agent_pos = agent->pos;
    WorldAgent *agent_at_pos = world->positions[agent_pos].agent;
    Action move = agent->action;

    if (agent_at_pos == agent) {
        int next_pos = agent_pos;
        if (move == ACTION_MOVE_LEFT) next_pos = world_get_position(world, agent_pos - 1);
        if (move == ACTION_MOVE_RIGHT) next_pos = world_get_position(world, agent_pos + 1);

        WorldAgent *agent_next = world->positions[next_pos].agent;
        if (agent_next == NULL) {
            world->positions[agent_pos].agent = NULL;
            world->positions[next_pos].agent = agent;
            agent->pos = next_pos;
        }
    }

    agent->action = ACTION_NONE;
    world_agent_decrease_hp(agent, world, 1);
}

World *world_new(int size, int food_energy, int agent_count_max, int agent_hp_max) {

    World *world = malloc(sizeof(World));
    WorldPosition *elements = malloc(sizeof(WorldPosition) * size);

    for (int i = 0; i < size; i++) {
        elements[i].agent = NULL;
        elements[i].n_foods = 0;
    }

    world->size = size;
    world->positions = elements;
    world->food_energy = food_energy;
    world->free_energy = 0;

    world->agents = malloc(sizeof(WorldAgent *) * agent_count_max);
    world->n_agents_max = agent_count_max;
    world->agent_hp_max = agent_hp_max;
    for (int i = 0; i < world->n_agents_max; i++) world->agents[i] = NULL;
    world->n_agents = 0;


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

    if (world->n_agents_max == world->n_agents) {
        return 0;
    }

    int pos = world_get_position(world, index);
    if (world->positions[pos].agent == NULL) {

        for (int i = 0; i < world->n_agents_max; i++) {
            if (world->agents[i] == NULL) {
                world->agents[i] = agent;
                break;
            }
        }

        world->positions[pos].agent = agent;
        agent->pos = pos;
        world->n_agents++;

        return 1;
    }
    return 0;
}


void world_update(World *world) {

    while(world->free_energy > world->food_energy){
        world->free_energy -= world->food_energy;
        world_add_food(world, rand_int(world->size));
    }

    for(int i = 0; i < world->size; i++){
        WorldPosition position = world->positions[i];
        if(position.agent != NULL) continue;

        if(position.n_foods*world->food_energy >= world->agent_hp_max){
            position.n_foods -= world->agent_hp_max/world->food_energy;
            WorldAgent *new_agent = world_agent_new( world->agent_hp_max,  world->agent_hp_max);
            world_add_agent(world, new_agent, i);
        }
    }

    for (int i = 0; i < world->n_agents_max; i++) {
        WorldAgent *agent = world->agents[i];
        if (agent != NULL) world_agent_update(agent, world);
    }

    for (int i = 0; i < world->n_agents_max; i++) {
        WorldAgent *agent = world->agents[i];
        if (agent != NULL) {
            world_act_agent(world, agent);
            world_agent_decrease_hp(agent, world, 1);
        }
    }

    for (int i = 0; i < world->n_agents_max; i++) {
        WorldAgent *agent = world->agents[i];
        if (agent != NULL) {
            if (agent->hp <= 0) {
                world->positions[agent->pos].agent = NULL;
                world->agents[i] = NULL;
                free(agent);
                world->n_agents--;
            }
        }
    }

    for (int i = 0; i < world->n_agents_max; i++) {
        WorldAgent *agent = world->agents[i];
        if (agent != NULL) {
            int agent_pos = agent->pos;
            int *food_count = &world->positions[agent_pos].n_foods;
            if (*food_count > 0) {
                (*food_count)--;
                world_agent_increase_hp(agent, world, world->food_energy);
            }
        }
    }

    for (int i = 0; i < world->n_agents_max; i++) {
        WorldAgent *agent = world->agents[i];
        if (agent != NULL && agent->hp > agent->hp_max) {
            int agent_pos = agent->pos;
            int left_pos = world_get_position(world, agent_pos - 1);
            int right_pos = world_get_position(world, agent_pos + 1);

            if (world->positions[left_pos].agent != NULL) continue;
            if (world->positions[right_pos].agent != NULL) continue;

            int total_hp = agent->hp;
            world->positions[left_pos].agent = agent;

            agent->hp = total_hp / 2;
            agent->action = ACTION_NONE;
            agent->pos = left_pos;

            world->positions[agent_pos].agent = NULL;

            WorldAgent *new_agent = world_agent_new(total_hp - agent->hp, agent->hp_max);
            world_add_agent(world, new_agent, right_pos);
        }
    }
}