#include "atom.h"
#include "../../tools/tools.h"

Atom* atom_new(int x, int y, AtomType type){
    Atom * atom = malloc(sizeof(Atom));
    atom->x = x;
    atom->y = y;
    atom->type = type;
    return atom;
}
void atom_update(Atom* atom, World* world){

    int max_x = world->width;
    int max_y = world->height;

    int rand = rand_int(5);
    if (rand == 0){
        atom->x++;
    }
    else if (rand == 1){
        atom->x--;
    }
    else if (rand == 2){
        atom->y++;
    }
    else if (rand == 3){
        atom->y--;
    }

    if( atom->x < 0) atom->x += max_x;
    if( atom->x >= max_x ) atom->x -= max_x;
    if( atom->y < 0) atom->y += max_y;
    if( atom->y >= max_y ) atom->y -= max_y;

    world_add(world, atom);
}


World *world_new(int width, int height) {
    int **world_array = malloc(sizeof(int *) * width * height);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            world_array[i + (j * width)] = malloc(sizeof(int) * ATOM_TYPE_COUNT);
            for (int k = 0; k < ATOM_TYPE_COUNT; k++) world_array[i + (j * width)][k] = 0;
        }
    }

    World *world = malloc(sizeof(World));
    world->atom_count_array = world_array;
    world->width = width;
    world->height = height;
    return world;
}

void world_reset(World *world) {
    for (int i = 0; i < world->width; i++) {
        for (int j = 0; j < world->height; j++) {
            for (int k = 0; k < ATOM_TYPE_COUNT; k++) world->atom_count_array[i + (j * world->width)][k] = 0;
        }
    }
}

void world_add(World *world, const Atom *atom) {
    world->atom_count_array[atom->x + (atom->y * world->width)][atom->type]++;
}

int world_get(World *world, int x, int y, AtomType type){
    return world->atom_count_array[x + (y * world->width)][type];
}

void world_update(World *world, Atom** atoms, int n_atoms){
    for (int i = 0; i < world->width; i++) {
        for (int j = 0; j < world->height; j++) {


            if (world->atom_count_array[i + (j * world->width)][ATOM_CARBON] == 2){
                if (rand_float() <0.99) continue;
                int index= 0;
                for(int ai=0;ai < n_atoms; ai++){
                    Atom* atom = atoms[ai];
                    if(atom->x == i && atom->y ==j && index == 0 && atom->type==ATOM_CARBON){
                        atom->type = ATOM_DICARBON;
                        index++;
                    }
                    if(atom->x == i && atom->y ==j && index == 1 && atom->type==ATOM_CARBON){
                        atom->type = ATOM_ENERGY;
                        index++;
                    }
                }
            }


            if (world->atom_count_array[i + (j * world->width)][ATOM_DICARBON] == 1
            &&  world->atom_count_array[i + (j * world->width)][ATOM_ENERGY] == 1){
                for(int ai=0;ai < n_atoms; ai++){
                    Atom* atom = atoms[ai];
                    if(atom->x == i && atom->y ==j && atom->type==ATOM_DICARBON){
                        atom->type = ATOM_CARBON;
                    }
                    if(atom->x == i && atom->y ==j && atom->type==ATOM_ENERGY){
                        atom->type = ATOM_CARBON;
                    }
                }
            }
        }
    }
}