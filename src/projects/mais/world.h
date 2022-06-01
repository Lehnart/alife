#ifndef ALIFE_WORLD_H
#define ALIFE_WORLD_H

typedef enum Action{
    ACTION_NONE,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT
} Action;

typedef struct WorldAgent{
    Action action;
} WorldAgent;

typedef struct WorldPosition{
    int n_foods;
    WorldAgent* agent;
} WorldPosition;

typedef struct World{
    WorldPosition* positions;
    int size;
} World;



WorldAgent* world_agent_new     ();
void        world_agent_update  (WorldAgent* agent, World* world, int pos);

World*  world_new           (int size);
void    world_update        (World* world);
void    world_add_food      (World *world, int index);
int     world_add_agent     (World *world, WorldAgent* agent, int index);
int     world_get_position  (const World *world, int index);
void    world_act_agent    (World *world, WorldAgent* agent, int pos);

#endif //ALIFE_WORLD_H
