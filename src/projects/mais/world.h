#ifndef ALIFE_WORLD_H
#define ALIFE_WORLD_H

typedef enum Action{
    ACTION_NONE,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_EAT,
    ACTION_COUNT
} Action;

typedef struct SensorResult{
    union{
        struct{
            unsigned int is_agent_at_left : 1;
            unsigned int is_agent_at_mid : 1;
            unsigned int is_agent_at_right : 1;

            unsigned int is_food_at_left : 1;
            unsigned int is_food_at_mid : 1;
            unsigned int is_food_at_right : 1;

        };
        unsigned int result;
    };

} SensorResult;

typedef struct WorldAgent{
    Action action;
    int hp;
    int pos;
    Action transition_rules[256];
} WorldAgent;

typedef struct WorldPosition{
    int n_foods;
    WorldAgent* agent;
} WorldPosition;

typedef struct World{
    WorldPosition* positions;
    int size;

    WorldAgent** agents;
    int n_agents;
    int n_agents_max;

    int food_energy;
} World;



WorldAgent* world_agent_new     (int hp);
void        world_agent_delete  (WorldAgent * agent);
void        world_agent_update  (WorldAgent* agent, World* world);
void        world_act_agent     (World *world, WorldAgent* agent);

World*  world_new           (int size, int food_energy, int agent_count_max);
void    world_update        (World* world);
void    world_add_food      (World *world, int index);
int     world_add_agent     (World *world, WorldAgent* agent, int index);
int     world_get_position  (const World *world, int index);


#endif //ALIFE_WORLD_H
