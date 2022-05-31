#ifndef ALIFE_WORLD_H
#define ALIFE_WORLD_H

typedef struct WorldAgent{
    void* data;
} WorldAgent;

typedef struct WorldPosition{
    int n_foods;
    WorldAgent* agent;
} WorldPosition;

typedef struct World{
    WorldPosition* positions;
    int size;
} World;

WorldAgent* world_agent_new ();

World*  world_new           (int size);
void    world_update        (World* world);
void    world_add_food      (World *world, int index);
int     world_add_agent     (World *world, WorldAgent* agent, int index);

#endif //ALIFE_WORLD_H
