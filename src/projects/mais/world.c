#include <malloc.h>
#include "world.h"

WorldAgent* world_agent_new (){
    WorldAgent* agent = malloc(sizeof(WorldAgent));
    return agent;
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

int world_get_position(World *world, int index) {
    if(index < 0){
        return world_get_position(world, world->size + index);
    }
    if(index >= world->size){
        return world_get_position(world, index - world->size);
    }
    return index;
}

void world_add_food(World *world, int index) {
    int pos = world_get_position(world, index);
    world->positions[pos].n_foods++;
}

int world_add_agent(World *world, WorldAgent* agent, int index) {
    int pos = world_get_position(world, index);
    if (world->positions[pos].agent == NULL){
        world->positions[pos].agent = agent;
        return 1;
    }
    return 0;
}


void world_update(World *world) {


}