#ifndef ALIFE_WORLD_H
#define ALIFE_WORLD_H

typedef struct WorldComponent{
    int x;
    int y;
    void* data;
}WorldComponent;


typedef struct World{
        unsigned int w;
        unsigned int h;
    unsigned int n_agents;
    WorldComponent **agents;

    unsigned int n_foods;
    WorldComponent **foods;

} World;

World* world_new(unsigned int w, unsigned int h, unsigned int n_agents, unsigned int n_foods);
void world_update(World* world);

#endif //ALIFE_WORLD_H
