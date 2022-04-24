#ifndef ALIFE_ATOM_H
#define ALIFE_ATOM_H

typedef enum AtomType {
    ATOM_CARBON,
    ATOM_ENERGY,
    ATOM_TYPE_COUNT
} AtomType;

typedef struct Atom{
    int x;
    int y;
    enum AtomType type;
} Atom;

typedef struct World{
    int **atom_count_array;
    int width;
    int height;
} World;


void atom_update(Atom* atom, World* world);

World* world_new(int width, int height);
void world_reset(World *world);
void world_add(World *world, const Atom *atom);
int world_get(World *world, int x, int y, AtomType type);


#endif //ALIFE_ATOM_H
