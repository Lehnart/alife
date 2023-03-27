#ifndef ALIFE_WORLD_H
#define ALIFE_WORLD_H

typedef enum Action {
    ACTION_NONE,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_COUNT
} Action;

typedef struct SensorResult {
    union {
        struct {
            unsigned int is_agent_at_left: 1;
            unsigned int is_agent_at_mid: 1;
            unsigned int is_agent_at_right: 1;

            unsigned int is_food_at_left: 1;
            unsigned int is_food_at_mid: 1;
            unsigned int is_food_at_right: 1;
        };
        unsigned int result;
    };

} SensorResult;

typedef struct WorldAgent {
    Action action;
    int hp;
    int hp_max;
    int pos;
    Action transition_rules[64];
} WorldAgent;

typedef struct WorldPosition {
    int n_foods;
    WorldAgent *agent;
} WorldPosition;

typedef struct World {
    WorldPosition *positions;
    int size;

    WorldAgent **agents;
    int n_agents;
    int n_agents_max;
    int agent_hp_max;

    int free_energy;
    int food_energy;

    double agent_emergence_probability;
} World;


WorldAgent *world_agent_new(int hp, int hp_max);

void world_agent_update(WorldAgent *agent, World *world);

void world_agent_decrease_hp(WorldAgent *agent, World *world, int amount);

void world_agent_increase_hp(WorldAgent *agent, World *world, int amount);

void world_act_agent(World *world, WorldAgent *agent);

World *world_new(int size, int food_energy, int agent_count_max, int agent_hp_max, double agent_emergence_proba);

void world_update(World *world);

void world_add_food(World *world, int index);

int world_add_agent(World *world, WorldAgent *agent, int index);

int world_get_position(const World *world, int index);


#endif //ALIFE_WORLD_H
